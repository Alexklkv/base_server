#pragma once

#include "Range.h"
#include "IDGenerator.h"

#include "ability/Data.h"
#include "battle/PassiveAbilities.h"

#include "enums.h"

#include <unordered_map>

class Ability;

class AbilitiesParams
{
	typedef std::unordered_map<ability::Type, Ability*, std::hash<uint16_t> > abilities_t;

	static const Range<ability::Type> CATEGORY_RANGE[ability::MAX_CATEGORY];

	abilities_t abilities;

	void init(IDGenerator &ids);

public:
	explicit AbilitiesParams(IDGenerator &ids);
	virtual ~AbilitiesParams();

	const Ability* get(ability::Type type) const;
	PassiveAbilities::passives_t get(const ability::abilities_t &types) const;

	ability::Category get_category(ability::Type ability) const;
	Range<ability::Type> get_range(ability::Category category) const;
};