#pragma once

#include "BattleAction.h"
#include "NoCopy.h"

#include "ability/Data.h"
#include "ability/combo/ComboTargeting.h"
#include "ability/effects/types.h"
#include "battle/ActiveCombos.h"
#include "server/Object.h"

#include <list>

class BattleEffect;
class GameObject;
class Spell;

class RoundActionsLog : private NoCopy, public server::Object
{
public:
	typedef std::list<BattleAction> actions_t;

private:
	actions_t actions;

public:
	void card_added(const GameObject *card, uint8_t slot);
	void card_moved(const GameObject *card, uint8_t target_slot);
	void attack(BattleAction::AttackType type, const GameObject *attacker, const GameObject *target, uint32_t damage);
	void spell(const GameObject *caster, const GameObject *target, const Spell *spell, uint64_t data);
	void spell(const GameObject *caster, const Spell *spell, BattleAction::targets_t &&targets);
	void effect(BattleAction::sources_t &&sources, BattleAction::targets_t &&targets, ability::Type type);
	void effect(const GameObject *source, const GameObject *target, const BattleEffect *effect, uint64_t data);
	void effect(const GameObject *source, const BattleEffect *effect);
	void effect_remove(const GameObject *owner, ability::Type type, ability::Modifier modifier);
	void effects_remove(const GameObject *owner, const removed_effects_list &removed);
	void mana_used(const GameObject *card, uint8_t mana);
	void ability_effect(const GameObject *source, const GameObject *target, const BattleEffect *effect, BattleAction::targets_t &log);
	void combo_effect(const GameObject *summoner, const BattleEffect *effect, BattleAction::targets_t &&log);
	void combo_applied(const GameObject *summoner, ComboID id, ability::Type type, const ComboTargeting::targets_t &targets);
	void combo_removed(const GameObject *summoner, ComboID id, ability::Type type, const ActiveCombos::ids_t &targets);

	void clear();
	bool empty() const;

	virtual void write(server::Writer *writer) const override;
};