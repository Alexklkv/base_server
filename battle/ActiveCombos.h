#pragma once

#include "GameObject.h"

#include "ability/combo/ComboID.h"
#include "ability/combo/ComboTargeting.h"

#include "enums.h"

#include <unordered_map>
#include <vector>

class ActiveCombos
{
public:
	typedef std::list<GameObject::Id> ids_t;

	struct Entry
	{
		ability::Type type;
		ComboID combo;
		ids_t ids;
	};

	typedef std::unordered_map<uint64_t, Entry> combos_t;

	combos_t combos;

	static ids_t make_ids(const ComboTargeting::targets_t &targets);

public:
	void add(ComboID combo, ability::Type type, const ComboTargeting::targets_t &targets);
	void remove(ComboID combo);

	ids_t targets(ComboID combo) const;
	ComboID get_id(ability::Type type) const;
	ability::Type get_type(ComboID combo) const;
	bool has(ComboID combo) const;

	std::vector<ComboID> get_all() const;

#ifdef DEBUG
	void debug_state(std::stringstream &debug_data) const;
#endif
};