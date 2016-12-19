#pragma once

#include "GameObject.h"

#include "Combatant.h"

#include "ability/combo/ComboID.h"

#include <functional>
#include <map>

class ActiveEffects;
class BattleEffect;
class RetentionPolicy;

class ActiveEffect
{
	friend class ActiveEffects;

	typedef uint64_t composite_source_key_t;

	// It's not unordered because elements removal on container traversal only
	// preserves relative elements order from C++ 14.
	typedef std::map<composite_source_key_t, RetentionPolicy*> retentions_t;

	const BattleEffect *effect;
	retentions_t retentions;
	const combatant_ptr_t caster;

	void retention_update(const std::function<void(composite_source_key_t, RetentionPolicy*)> &callback);
	void retention_update(const std::function<void(RetentionPolicy*)> &callback);

	void add(composite_source_key_t key);

public:
	bool removed = false;

	explicit ActiveEffect(const BattleEffect *effect, combatant_ptr_t caster);
	~ActiveEffect();

	void add(const GameObject::Id &source);
	void add(ComboID combo);

	void on_end_turn();
	void on_move();
	void on_other_move(const GameObject::Id &moved);
	void on_end_action();
	void on_combo_removal(ComboID id);

	const BattleEffect* get() const;
	const BattleEffect* get_effect() const;
	bool expired() const;
};