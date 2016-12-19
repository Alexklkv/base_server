#include "EnabledComboManager.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Exception.h"
#include "Summoner.h"

#include "ability/combo/Combo.h"
#include "ability/combo/ComboID.h"
#include "ability/combo/ComboParams.h"
#include "ability/combo/ComboTargeting.h"
#include "battle/ActiveCombos.h"
#include "battle/ActiveEffects.h"
#include "battle/RoundActionsLog.h"
#include "Log.h"

EnabledComboManager::EnabledComboManager(BattleField *owner, const ComboParams *combos):
	field(owner), params(combos)
{}

static void remove_effects(RoundActionsLog *log, ComboID id, ability::Type ability, const combatant_ptr_t &owner, BattleField *field)
{
	const auto to_remove = owner->get_card()->active_combos->targets(id);
	for (const GameObject::Id &to_remove_id : to_remove)
	{
		combatant_ptr_t to_remove = field->get(to_remove_id);
		if (!to_remove)
			continue;

		if (!to_remove->is_card())
			throw Exception("Not card in combo removal");

		to_remove->get_card()->active_combos->remove(id);
		auto removed = to_remove->get_card()->active_effects->on_combo_remove(to_remove, field, id);
		log->effects_remove(to_remove.get(), removed);
	}

	log->combo_removed(owner->get_summoner(), id, ability, to_remove);
}

static void clear_all(RoundActionsLog *log, ability::Type type, const ComboTargeting::targets_t &targets, BattleField *field)
{
	for (const combatant_ptr_t &target : targets)
	{
		if (!target->is_card())
			continue;

		ComboID id = target->get_card()->active_combos->get_id(type);
		if (!id.valid())
			continue;

		remove_effects(log, id, type, target, field);
	}
}

static void clear_all_predecessors(RoundActionsLog *log, const Combo *combo, const ComboTargeting::targets_t &targets, BattleField *field)
{
	for (auto type : combo->get_predecessors())
		clear_all(log, type, targets, field);
}

void EnabledComboManager::apply(RoundActionsLog *log, const combatant_ptr_t &moved)
{
	this->params->foreach([log, &moved, this] (const Combo *combo) {
		auto targets = combo->targets(this->field, moved);
		if (targets.empty())
			return;

		clear_all_predecessors(log, combo, targets, this->field);
		combo->apply(log, targets, this->field);
	});
}

static bool try_apply(RoundActionsLog *log, const Combo *combo, const combatant_ptr_t &target, BattleField *field)
{
	auto targets = combo->targets(field, target);
	if (targets.empty())
		return false;

	combo->apply(log, targets, field);

	return true;
}

void EnabledComboManager::reapply(RoundActionsLog *log, const removed_t &removed)
{
	for (const Removed &entry : removed)
	{
		const Combo *combo = this->params->get(entry.type);
		if (try_apply(log, combo, entry.matching, this->field))
			continue;

		for (auto type : combo->get_predecessors())
		{
			const Combo *combo = this->params->get(type);
			try_apply(log, combo, entry.matching, this->field);
		}
	}
}

void EnabledComboManager::clear(RoundActionsLog *log, const combatant_ptr_t &moved)
{
	auto *summoner = moved->get_summoner();
	const auto *active_combos = moved->get_card()->active_combos;
	const auto combo_ids = active_combos->get_all();
	const auto active_cards = summoner->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);

	for (auto &combo_id : combo_ids)
	{
		auto general_type = active_combos->get_type(combo_id);
		const Combo *combo = this->params->get(general_type);
		for (auto &type : combo->get_predecessors())
			this->remove_combo(log, active_cards, summoner, type);

		this->remove_combo(log, active_cards, summoner, general_type);
	}
}

static ComboID get_combo_id(const cards_set_t &active_cards, ability::Type type)
{
	for (auto &card : active_cards)
	{
		ComboID combo_id = card->active_combos->get_id(type);
		if (combo_id.valid())
			return combo_id;
	}

	return ComboID::invalid();
}

void EnabledComboManager::remove_combo(RoundActionsLog *log, const cards_set_t &active_cards, Summoner *summoner, ability::Type type)
{
	ComboID combo_id = get_combo_id(active_cards, type);

	if (!combo_id.valid())
	{
		logger()->warning("Trying to remove invalid combo with type: %d", type);
		return;
	}

	ActiveCombos::ids_t targets;
	for (auto &card : active_cards)
	{
		if (!card->active_combos->has(combo_id))
			continue;

		card->active_combos->remove(combo_id);
		targets.push_back(card->object_id());

		auto combatant = std::make_shared<Combatant>(card, summoner);
		auto removed_effects = card->active_effects->on_combo_remove(combatant, this->field, combo_id);

		log->effects_remove(combatant.get(), removed_effects);
	}

	log->combo_removed(summoner, combo_id, type, targets);
}

static combatant_ptr_t find_first_other(const ActiveCombos::ids_t &from, const GameObject::Id &ignore, BattleField *field)
{
	auto iter = std::find_if(from.cbegin(), from.cend(), [&ignore] (const GameObject::Id &id) {
		return id != ignore;
	});
	if (iter == from.cend())
		throw Exception("Single-target combo detected");

	return field->get(*iter);
}

EnabledComboManager::removed_t EnabledComboManager::clear_removed(RoundActionsLog *log, const combatant_ptr_t &removed)
{
	if (!removed->is_card())
		return removed_t();

	ActiveCombos *combos = removed->get_card()->active_combos;
	std::vector<ComboID> active = combos->get_all();
	removed_t removal_log;
	for (const ComboID &id : active)
	{
		auto targets = combos->targets(id);
		auto type = combos->get_type(id);
		remove_effects(log, id, type, removed, this->field);
		removal_log.push_back({type, find_first_other(targets, removed->object_id(), this->field)});
	}
	return removal_log;
}