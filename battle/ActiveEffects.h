#pragma once

#include "ability/effects/types.h"

#include <map>

class ActiveEffect;
class BattleEffect;

class ActiveEffects
{
	// It's not unordered because elements removal on container traversal only
	// preserves relative elements order from C++ 14.
	typedef std::map<uint32_t, ActiveEffect*> storage_t;
	storage_t effects_storage;

	ActiveEffect* add(const BattleEffect *effect, bool &added, const combatant_ptr_t caster);
	removed_effects_list expiration_update(const combatant_ptr_t &owner, BattleField *field, const std::function<void(ActiveEffect*)> &updater);
	removed_effects_list clear(const combatant_ptr_t &owner, BattleField *field, const std::function<bool(const ActiveEffect*)> &removal_predicate);

public:
	ActiveEffects();
	virtual ~ActiveEffects();

	bool add(const GameObject::Id &source, const BattleEffect *effect, const combatant_ptr_t caster);
	bool add(ComboID combo, const BattleEffect *effect);
	removed_effects_list clear(const combatant_ptr_t &owner, bool negative, BattleField *field);
	void clear();
	void expire();

	bool has_modifier(ability::Modifier ability);
	bool has_modifier_from(ability::Modifier modifier, GameObject::Id caster);

	void effects(active_effects_t &result) const;

	removed_effects_list get_expired(const combatant_ptr_t &owner, BattleField *field);
	removed_effects_list on_end_turn(const combatant_ptr_t &owner, BattleField *field);
	removed_effects_list on_move(const combatant_ptr_t &owner, BattleField *field);
	removed_effects_list on_other_move(const combatant_ptr_t &owner, BattleField *field, const combatant_ptr_t &moved);
	removed_effects_list on_combo_remove(const combatant_ptr_t &owner, BattleField *field, ComboID id);

#ifdef DEBUG
	void debug_state(std::stringstream &debug_data) const;
#endif
};