#pragma once

#include "basic/BattleEffect.h"
#include "basic/CardAttackEffect.h"
#include "basic/CardMoveEffect.h"
#include "basic/CardPlacementEffect.h"
#include "basic/RoundEffect.h"
#include "basic/SpellEffect.h"
#include "battle/ActiveEffect.h"

#include <set>
#include <vector>

struct EffectID
{
	ability::Type type;
	ability::Modifier modifier;
};
typedef std::vector<EffectID> removed_effects_list;

struct PriorityCompare
{
	bool operator() (const ActiveEffect *fst, const ActiveEffect *snd) const
	{
		return fst->get_effect()->get_priority() > snd->get_effect()->get_priority();
	}
};

typedef std::multiset<ActiveEffect*, PriorityCompare> active_effects_t;