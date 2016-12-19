#include "Combo.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Exception.h"
#include "Summoner.h"

#include "battle/ActiveCombos.h"
#include "battle/RoundActionsLog.h"

Combo::Combo():
	Combo(ability::NO_ABILITY, {})
{}

Combo::Combo(ability::Type type, std::initializer_list<ability::Type> predecessors):
	type(type), predecessors(predecessors)
{}

Combo::~Combo()
{}

ability::Type Combo::get_ability() const
{
	return this->type;
}

const Combo::predecessors_t& Combo::get_predecessors() const
{
	return this->predecessors;
}

bool Combo::apply(RoundActionsLog *log, const ComboTargeting::targets_t &targets, BattleField *field) const
{
	ComboID combo = field->new_combo();
	const Summoner *owner = (*targets.cbegin())->get_summoner();

	log->combo_applied(owner, combo, this->get_ability(), targets);

	ComboTargeting::targets_t to_add_effects;
	for (const combatant_ptr_t &target : targets)
	{
		if (!target->is_card())
			throw Exception("Not card supplied to combo applier");

		auto combos = target->get_card()->active_combos;

		ComboID exist_combo = combos->get_id(this->get_ability());
		if (exist_combo == ComboID::invalid())
			to_add_effects.insert(target);
		else
		{
			log->combo_removed(owner, exist_combo, this->get_ability(), combos->targets(exist_combo));
			combos->remove(exist_combo);
		}

		combos->add(combo, this->get_ability(), targets);
	}

	return this->do_apply(log, combo, to_add_effects, field);
}