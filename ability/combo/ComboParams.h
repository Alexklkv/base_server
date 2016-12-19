#pragma once

#include "ComboTargeting.h"
#include "IDGenerator.h"

#include "enums.h"

#include <functional>
#include <unordered_map>

class Combo;

class ComboParams : private ComboTargeting
{
	typedef std::unordered_map<ability::Type, const Combo*, std::hash<uint16_t> > combos_t;

	combos_t combos;

	void init(IDGenerator &ids);

public:
	explicit ComboParams(IDGenerator &ids);
	~ComboParams();

	void foreach(const std::function<void(const Combo*)> &callback) const;
	const Combo* get(ability::Type type) const;
};