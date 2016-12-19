#include "ActiveEffects.h"

#include "ability/effects/basic/BattleEffect.h"

ActiveEffects::ActiveEffects()
{}

ActiveEffects::~ActiveEffects()
{
	this->clear();
}

void ActiveEffects::effects(active_effects_t &result) const
{
	for (const storage_t::value_type &pair : this->effects_storage)
		result.insert(pair.second);
}

ActiveEffect* ActiveEffects::add(const BattleEffect *effect, bool &added, const combatant_ptr_t caster)
{
	std::pair<storage_t::iterator, bool> inserted = this->effects_storage.emplace(effect->get_id(), nullptr);

	if (inserted.second)
		inserted.first->second = new ActiveEffect(effect, caster);

	added = (inserted.second || inserted.first->second->removed); // Effect might be applied after removal but before actual object erasure.
	return inserted.first->second;
}

bool ActiveEffects::add(const GameObject::Id &source, const BattleEffect *effect, const combatant_ptr_t caster)
{
	bool added = false;
	ActiveEffect *storage = this->add(effect, added, caster);
	storage->add(source);
	return added;
}

bool ActiveEffects::add(ComboID combo, const BattleEffect *effect)
{
	bool added = false;
	ActiveEffect *storage = this->add(effect, added, nullptr);
	storage->add(combo);
	return added;
}

removed_effects_list ActiveEffects::clear(const combatant_ptr_t &owner, BattleField *field, const std::function<bool(const ActiveEffect*)> &removal_predicate)
{
	for (storage_t::value_type &pair : this->effects_storage)
	{
		ActiveEffect *active_effect = pair.second;

		if (active_effect->expired())
			continue;

		if (!removal_predicate(active_effect))
			continue;

		active_effect->removed = true;
	}

	return this->get_expired(owner, field);
}

bool ActiveEffects::has_modifier(ability::Modifier modifier)
{
	for (auto iter : this->effects_storage)
	{
		ActiveEffect *active_effect = iter.second;

		if (active_effect->expired())
			continue;

		if (active_effect->effect->get_effect() == modifier)
			return true;
	}

	return false;
}

bool ActiveEffects::has_modifier_from(ability::Modifier modifier, GameObject::Id caster)
{
	for (auto iter : this->effects_storage)
	{
		if (iter.second->effect->get_effect() != modifier)
			continue;

		if (iter.second->caster->object_id() == caster)
			return true;
	}

	return false;
}

removed_effects_list ActiveEffects::clear(const combatant_ptr_t &owner, bool negative, BattleField *field)
{
	return this->clear(owner, field, [negative, &owner] (const ActiveEffect *effect) {
		return (effect->get()->is_negative_for(owner) == negative);
	});
}

void ActiveEffects::clear()
{
	for (auto pair : this->effects_storage)
		delete pair.second;
	this->effects_storage.clear();
}

void ActiveEffects::expire()
{
	for (auto pair : this->effects_storage)
		pair.second->removed = true;
}

removed_effects_list ActiveEffects::get_expired(const combatant_ptr_t &owner, BattleField *field)
{
	removed_effects_list removed;
	for (storage_t::iterator iter = this->effects_storage.begin(); iter != this->effects_storage.end(); )
	{
		ActiveEffect *value = iter->second;
		if (!value->removed)
		{
			if (!value->expired())
			{
				iter++;
				continue;
			}

			value->removed = true;

			BattleAction::targets_t targets;
			StatsContext ctx(owner, field, targets, value->caster);

			value->get_effect()->after_removal(ctx);
			removed.push_back({value->get_effect()->get_ability(), value->get_effect()->get_effect()});
		}

		delete value;
		iter = this->effects_storage.erase(iter);
	}

	return removed;
}

removed_effects_list ActiveEffects::expiration_update(const combatant_ptr_t &owner, BattleField *field, const std::function<void(ActiveEffect*)> &updater)
{
	removed_effects_list removed;
	for (storage_t::value_type &pair : this->effects_storage)
	{
		ActiveEffect *effect = pair.second;

		if (effect->expired())
			continue;

		updater(effect);

		if (!effect->expired())
			continue;

		effect->removed = true;

		BattleAction::targets_t targets;
		StatsContext ctx(owner, field, targets, effect->caster);

		effect->get_effect()->after_removal(ctx);
		removed.push_back({effect->get_effect()->get_ability(), effect->get_effect()->get_effect()});
	}

	return removed;
}

removed_effects_list ActiveEffects::on_end_turn(const combatant_ptr_t &owner, BattleField *field)
{
	return this->expiration_update(owner, field, &ActiveEffect::on_end_turn);
}

removed_effects_list ActiveEffects::on_move(const combatant_ptr_t &owner, BattleField *field)
{
	return this->expiration_update(owner, field, &ActiveEffect::on_move);
}

removed_effects_list ActiveEffects::on_other_move(const combatant_ptr_t &owner, BattleField *field, const combatant_ptr_t &moved)
{
	return this->expiration_update(owner, field, [&moved] (ActiveEffect *effect) {
		effect->on_other_move(moved->object_id());
	});
}

removed_effects_list ActiveEffects::on_combo_remove(const combatant_ptr_t& owner, BattleField* field, ComboID id)
{
	return this->expiration_update(owner, field, [id] (ActiveEffect *effect) {
		effect->on_combo_removal(id);
	});
}

#ifdef DEBUG

void ActiveEffects::debug_state(std::stringstream &debug_data) const
{
	debug_data << "Active effects: ";

	for (auto effect : this->effects_storage)
	{
		if (effect.second->expired())
			continue;

		debug_data << effect.second->get()->get_effect() << " ";
	}
}

#endif