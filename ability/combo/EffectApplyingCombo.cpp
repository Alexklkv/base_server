#include "EffectApplyingCombo.h"

#include "BattleField.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

EffectApplyingCombo::EffectApplyingCombo(std::initializer_list<const BattleEffect*> effects):
	effects(effects)
{}

EffectApplyingCombo::~EffectApplyingCombo()
{
	for (auto effect : this->effects)
		delete effect;
}

bool EffectApplyingCombo::do_apply(RoundActionsLog *log, ComboID combo, const ComboTargeting::targets_t &targets, BattleField *field) const
{
	if (targets.empty())
		return true;

	const Summoner *summoner = (*targets.cbegin())->get_summoner();

	bool success = false;
	for (auto effect : this->effects)
	{
		BattleAction::targets_t targets_log;
		for (const combatant_ptr_t &target : targets)
			success = field->add_combo_effect(combo, target, effect, targets_log) || success;

		if (success)
			log->combo_effect(summoner, effect, std::move(targets_log));
	}

	return success;
}