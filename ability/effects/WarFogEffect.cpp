#include "WarFogEffect.h"

WarFogEffect::WarFogEffect(uint32_t id, ability::Type type, const policy_factory_t &factory):
	BattleEffect(id, type, ability::Modifier::WAR_FOG, 0, factory)
{}