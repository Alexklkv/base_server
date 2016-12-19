#pragma once

#include "basic/CardAttackEffect.h"
#include "basic/NegativeEffect.h"

#include "misc.h"

class PiercingStrikeEffect final : public CardAttackEffect, public NegativeEffect
{
private:
	mutable uint16_t start_target_health;

	combatant_ptr_t get_target(combatant_ptr_t old_target) const;

protected:
	bool on_attacker_before(CardAttackContext &ctx) const override;
	bool on_attacker_after(CardAttackContext &ctx) const override;

public:
	PiercingStrikeEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};