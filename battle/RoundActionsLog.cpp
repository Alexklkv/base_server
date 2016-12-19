#include "RoundActionsLog.h"

#include "ActiveCombos.h"
#include "DataPacker.h"
#include "Enum.h"
#include "Exception.h"
#include "NoneContext.h"
#include "Summoner.h"

#include "ability/effects/basic/BattleEffect.h"
#include "ability/spells/Spell.h"
#include "server/Group.h"

void RoundActionsLog::card_added(const GameObject *card, uint8_t slot)
{
	BattleAction action(BattleAction::CATEGORY_MOVE, BattleAction::CARD_ADD, NoneContext::NONE_ID, 0);
	action.targets.emplace_back(card, slot);
	this->actions.push_back(std::move(action));
}

void RoundActionsLog::card_moved(const GameObject *card, uint8_t target_slot)
{
	BattleAction action(BattleAction::CATEGORY_MOVE, BattleAction::CARD_MOVE, NoneContext::NONE_ID, 0);
	action.targets.emplace_back(card, target_slot);
	this->actions.push_back(std::move(action));
}

void RoundActionsLog::attack(BattleAction::AttackType type, const GameObject *attacker, const GameObject *target, uint32_t damage)
{
	this->actions.emplace_back(BattleAction::CATEGORY_ATTACK, type, attacker->object_id(), 0);
	this->actions.back().targets.push_back({target, damage});
}

void RoundActionsLog::spell(const GameObject *caster, const GameObject *target, const Spell *spell, uint64_t data)
{
	this->actions.emplace_back(BattleAction::CATEGORY_ABILITY, ability::Category::SPELL, caster->object_id(), spell->spell);
	this->actions.back().targets.emplace_back(target, data);
}

void RoundActionsLog::spell(const GameObject *caster, const Spell *spell, BattleAction::targets_t &&targets)
{
	this->actions.emplace_back(BattleAction::CATEGORY_ABILITY, ability::Category::SPELL, caster->object_id(), spell->spell);
	this->actions.back().targets = std::move(targets);
}

void RoundActionsLog::effect(BattleAction::sources_t &&sources, BattleAction::targets_t &&targets, ability::Type type)
{
	this->actions.emplace_back(BattleAction::CATEGORY_EFFECT, ability::Category::CARD, std::move(sources), type);
	this->actions.back().targets = std::move(targets);
}

void RoundActionsLog::effect(const GameObject *source, const GameObject *target, const BattleEffect *effect, uint64_t data)
{
	this->effect(source, effect);
	this->actions.back().targets.emplace_back(target, data);
}

void RoundActionsLog::effect(const GameObject* source, const BattleEffect* effect)
{
	this->actions.emplace_back(BattleAction::CATEGORY_EFFECT, ability::Category::CARD, source->object_id(), effect->get_ability());
}

void RoundActionsLog::effect_remove(const GameObject* owner, ability::Type type, ability::Modifier modifier)
{
	this->actions.emplace_back(BattleAction::CATEGORY_EFFECT_REMOVE, 0, owner->object_id(), ((uint64_t)modifier << 16) | (uint64_t)type);
}

void RoundActionsLog::effects_remove(const GameObject *owner, const removed_effects_list &removed)
{
	for (auto &effect : removed)
		this->effect_remove(owner, effect.type, effect.modifier);
}

void RoundActionsLog::mana_used(const GameObject *card, uint8_t mana)
{
	this->actions.emplace_back(BattleAction::CATEGORY_DECREASE_MANA, 0, card->object_id(), mana);
}

void RoundActionsLog::ability_effect(const GameObject *source, const GameObject *target, const BattleEffect *effect, BattleAction::targets_t &log)
{
	uint64_t data = DataPacker().pack(ability::Action::ADD_EFFECT, effect->get_effect(), (uint16_t)0, ability::Duration::TEMPORARY);
	log.push_front({target, data});

	this->actions.emplace_back(BattleAction::CATEGORY_ABILITY, ability::Category::CARD, source->object_id(), effect->get_ability());
	this->actions.back().targets = std::move(log);
}

static uint64_t pack_combo(ComboID id, ability::Type type)
{
	return bitwise_pack<uint64_t>(id.id, type, 16);
}

void RoundActionsLog::combo_effect(const GameObject *summoner, const BattleEffect *effect, BattleAction::targets_t &&log)
{
	this->actions.emplace_back(BattleAction::CATEGORY_ABILITY, ability::Category::COMBO, summoner->object_id(), effect->get_ability());
	this->actions.back().targets = std::move(log);
}

static void write_combo(RoundActionsLog::actions_t &out, const GameObject *summoner, ComboID id, ability::Type type, BattleAction::targets_t &&targets, BattleAction::ComboAction action)
{
	out.emplace_back(BattleAction::CATEGORY_COMBO, action, summoner->object_id(), pack_combo(id, type));
	out.back().targets = std::move(targets);
}

static BattleAction::targets_t combo_targets(const ComboTargeting::targets_t &targets)
{
	BattleAction::targets_t result;
	for (const combatant_ptr_t &card : targets)
		result.emplace_back(card.get(), 0);
	return result;
}

static BattleAction::targets_t combo_targets(const ActiveCombos::ids_t &targets)
{
	BattleAction::targets_t result;
	for (const GameObject::Id &id : targets)
		result.emplace_back(id, 0);
	return result;
}

void RoundActionsLog::combo_applied(const GameObject *summoner, ComboID id, ability::Type type, const ComboTargeting::targets_t &targets)
{
	write_combo(this->actions, summoner, id, type, combo_targets(targets), BattleAction::ComboAction::COMBO_ADD_CREATOR);
}

void RoundActionsLog::combo_removed(const GameObject* summoner, ComboID id, ability::Type type, const ActiveCombos::ids_t &targets)
{
	write_combo(this->actions, summoner, id, type, combo_targets(targets), BattleAction::ComboAction::COMBO_REMOVE_CREATOR);
}

void RoundActionsLog::clear()
{
	this->actions.clear();
}

bool RoundActionsLog::empty() const
{
	return this->actions.empty();
}

void RoundActionsLog::write(server::Writer *writer) const
{
	server::Group actions_group;
	for (auto &action : this->actions)
	{
		#ifdef DEBUG
			//action.debug_print();
		#endif

		server::Group sources;
		for (auto &source : action.sources)
		{
			sources.add(source.summoner_id);
			sources.add(source.card_id);
			sources.next();
		}

		server::Group targets;
		for (auto &target : action.targets)
		{
			targets.add(target.id.summoner_id);
			targets.add(target.id.card_id);
			targets.add(target.data);
			targets.next();
		}

		actions_group.add(enum_unwrap(action.category));
		actions_group.add(action.type);
		actions_group.add(&sources);
		actions_group.add(action.data);
		actions_group.add(&targets);

		actions_group.next();
	}
	writer->add(&actions_group);
}