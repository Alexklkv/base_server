#pragma once

#include "IDGenerator.h"

#include "ability/Data.h"
#include "battle/PassiveAbilities.h"

#include "enums.h"

#include <unordered_map>

class Ability;

class EquipmentAbilitiesParams
{
private:
	typedef std::unordered_map<ability::Type, Ability*, std::hash<uint16_t> > abilities_t;

	abilities_t abilities;

	void init(IDGenerator &ids);

public:
	explicit EquipmentAbilitiesParams(IDGenerator &ids);
	virtual ~EquipmentAbilitiesParams();

	const Ability* get(ability::Type type) const;
	PassiveAbilities::passives_t get(const ability::abilities_t &types) const;
};