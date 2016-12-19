#include "Data.h"

namespace ability
{

bool is_stat_modifier(ability::Modifier modifier)
{
	return (STATS_MODIFIERS.find(modifier) != STATS_MODIFIERS.end());
}

#ifdef DEBUG
std::string debug_ability_category(Category category)
{
	switch (category)
	{
		case ability::SPELL: return "PLAYER";
		case ability::CARD: return "CARD";
		case ability::COMBO: return "COMBO";
		case ability::LOCATION: return "LOCATION";
		case ability::EQUIPMENT: return "EQUIPMENT";
		case ability::SHARPENING: return "SHARPENING";
		case ability::QUEST: return "QUEST";
		case ability::TROPHIES: return "TROPHIES";
		case ability::MAX_CATEGORY: return "MAX_CATEGORY";
	}

	return "Wrong category";
}

std::string debug_modifier(Modifier modifier)
{
	switch (modifier)
	{
		case NONE_MODIFIER: return "NONE_MODIFIER";
		case MODIFY_INJUIRE: return "MODIFY_INJUIRE";
		case MODIFY_ATTACK: return "MODIFY_ATTACK";
		case MODIFY_DODGE: return "MODIFY_DODGE";
		case MODIFY_CRITICAL: return "MODIFY_CRITICAL";
		case MODIFY_CRITICAL_FAILURE: return "MODIFY_CRITICAL_FAILURE";
		case MODIFY_HEALTH: return "MODIFY_HEALTH";
		case MODIFY_SPELL_INJUIRE: return "MODIFY_SPELL_ATTACK_INJUIRE";
		case MODIFY_SPELL_INJUIRE_FAILURE_CHANCE: return "MODIFY_SPELL_INJUIRE_FAILURE_CHANCE";
		case BLOCK_IN_RESPONSE: return "BLOCK_IN_RESPONSE";
		case BLOCK_MOVE: return "BLOCK_MOVE";
		case BLOCK_CAST: return "BLOCK_CAST";
		case BLOCK_SPELLS: return "BLOCK_SPELLS";
		case BLOCK_PASSIVE: return "BLOCK_PASSIVE";
		case BLOCK_MODIFIER_EFFECT: return "BLOCK_MODIFIER_EFFECT";
		case BLOCK_SLOT: return "BLOCK_SLOT";
		case BLOCK_PASSIVE_USE: return "BLOCK_PASSIVE_USE";
		case ALWAYS_FIRST: return "ALWAYS_FIRST";
		case CAN_ATTACK_FROM_REAR: return "CAN_ATTACK_FROM_REAR";
		case SHIELD: return "SHIELD";
		case PROVOCATION: return "PROVOCATION";
		case SLEEP: return "SLEEP";
		case POLYMORF: return "POLYMORF";
		case ADDITIONAL_ABILITY: return "ADDITIONAL_ABILITY";
		case DATURA: return "DATURA";
		case WAR_FOG: return "WAR_FOG";
		case ASTRAL_STORM: return "ASTRAL_STORM";
		case SPOLIED_FOLIO: return "SPOLIED_FOLIO";
		case DEAFNESS: return "DEAFNESS";
		case SUMMONER_BURDEN: return "SUMMONER_BURDEN";
		case WRONG_SUMMON: return "WRONG_SUMMON";
		case CAN_RESPOND_FLYING: return "CAN_RESPOND_FLYING";
	}

	return "Wrong modifier";
}
#endif

}