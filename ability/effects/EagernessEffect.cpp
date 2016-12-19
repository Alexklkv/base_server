#include "EagernessEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"

#include "battle/RoundActionsLog.h"

EagernessEffect::EagernessEffect(uint32_t id, ability::Type type, const policy_factory_t &p):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, p)
{}

bool EagernessEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		throw Exception("EagernessEffect on non-card entity");

	auto target = combatant->get_card();
	if (!target->first_move)
		return false;

	target->used = false;

	ctx.targets_log.push_back({combatant.get(), DataPacker().pack(ability::Action::UNBLOCK)});
	ctx.log->ability_effect(combatant.get(), combatant.get(), this, ctx.targets_log);

	return true;
}