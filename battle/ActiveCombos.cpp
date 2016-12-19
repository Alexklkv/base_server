#include "ActiveCombos.h"

#include "Exception.h"
#include "Log.h"

ActiveCombos::ids_t ActiveCombos::make_ids(const ComboTargeting::targets_t &targets)
{
	ids_t result;
	for (const combatant_ptr_t &card : targets)
		result.push_back(card->object_id());
	return result;
}

void ActiveCombos::add(ComboID combo, ability::Type type, const ComboTargeting::targets_t &targets)
{
	std::pair<combos_t::iterator, bool> inserted = this->combos.emplace(combo.id, Entry{type, combo, {}});
	if (!inserted.second)
		throw Exception("Combo ID duplication");

	inserted.first->second.ids = make_ids(targets);
}

void ActiveCombos::remove(ComboID combo)
{
	if (!this->combos.erase(combo.id))
		throw Exception("Delete Combo ID what doesn't exist");
}

ComboID ActiveCombos::get_id(ability::Type type) const
{
	// This lookup might be improved by adding dictionary hash like that: map<ability::Type, combos_t::iterator>
	// but I don't think this method performance will be an issue.

	combos_t::const_iterator found = std::find_if(this->combos.cbegin(), this->combos.cend(), [type] (const combos_t::value_type &pair) {
		return (pair.second.type == type);
	});
	if (found == this->combos.cend())
		return ComboID::invalid();
	else
		return found->second.combo;
}

ability::Type ActiveCombos::get_type(ComboID combo) const
{
	combos_t::const_iterator found = this->combos.find(combo.id);
	if (found == this->combos.cend())
	{
		logger()->warning("Unexpected combo ID %u supplied to ActiveCombos.get_type", combo.id);
		throw Exception("Unexpected combo ID supplied to ActiveCombos.get_type");
	}

	return found->second.type;
}

bool ActiveCombos::has(ComboID combo) const
{
	return this->combos.count(combo.id);
}

std::vector<ComboID> ActiveCombos::get_all() const
{
	std::vector<ComboID> result;
	result.reserve(this->combos.size());
	for (const combos_t::value_type &pair : this->combos)
		result.emplace_back(pair.first);
	return result;
}

ActiveCombos::ids_t ActiveCombos::targets(ComboID combo) const
{
	combos_t::const_iterator found = this->combos.find(combo.id);
	if (found == this->combos.cend())
		return ids_t{};
	else
		return found->second.ids;
}

#ifdef DEBUG

void ActiveCombos::debug_state(std::stringstream &debug_data) const
{
	debug_data << "Combos: ";

	for (auto combo : combos) {
		debug_data << combo.second.combo.id << " ";
	}

	debug_data << "\n";
}

#endif