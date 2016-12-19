#pragma once

#include "BattleAction.h"
#include "CardActionContext.h"
#include "Combatant.h"

#include "ability/spells/SpellsTargeting.h"

class BattleField;
class Spell;

class CardSpellContext : public CardActionContext
{
public:
	SpellsTargeting::targets_t targets;
	const Spell *const spell;
	Summoner *const caster;

	uint32_t cooldown;
	uint8_t mana;

public:
	CardSpellContext(BattleField *field, combatant_ptr_t &caster, combatant_ptr_t &target, const Spell *spell);
};