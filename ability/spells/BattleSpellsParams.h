#pragma once

#include "IDGenerator.h"
#include "SpellsTargeting.h"

#include "enums.h"

#include <unordered_map>

class Spell;

class BattleSpellsParams : private SpellsTargeting
{
	typedef std::unordered_map<ability::Type, Spell*, std::hash<uint16_t> > spells_t;

	spells_t spells;

	void init(IDGenerator &ids);

public:
	explicit BattleSpellsParams(IDGenerator &ids);
	virtual ~BattleSpellsParams();

	virtual const Spell* get(ability::Type type) const;
	bool has_spell(ability::Type type) const;

	ability::abilities_t get_available_spells(uint8_t level) const;

	ability::abilities_t get_available_bot_spells(uint8_t level) const;
	ability::abilities_t create_bot_spells(uint8_t level) const;
};