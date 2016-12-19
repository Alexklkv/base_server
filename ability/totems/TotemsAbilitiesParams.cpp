#include "TotemsAbilitiesParams.h"

#include "BaseCard.h"
#include "Enum.h"
#include "Exception.h"
#include "Log.h"

#include "ability/abilities/EffectsAbility.h"
#include "ability/effects/ExtraDamageEffect.h"
#include "ability/effects/ExtraHealthEffect.h"
#include "ability/effects/StatsEffectsApplier.h"

#include "misc.h"

void TotemsAbilitiesParams::init(IDGenerator &ids)
{
	this->abilities[ability::TOTEMS_GREED_VARONA] = new EffectsAbility(ability::TOTEMS_GREED_VARONA, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_GREED_VARONA, CardMask().set(BaseCard::COMMUNE), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_GREED_VARONA, new calculators::Percent(3), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_GREED_VARONA, new calculators::Percent(3), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_THE_RITE_OF_FAITH] = new EffectsAbility(ability::TOTEMS_THE_RITE_OF_FAITH, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_THE_RITE_OF_FAITH, CardMask().set(BaseCard::COMMUNE), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_THE_RITE_OF_FAITH, new calculators::Percent(5), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_THE_RITE_OF_FAITH, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_BATTLE_TRANCE] = new EffectsAbility(ability::TOTEMS_BATTLE_TRANCE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_BATTLE_TRANCE, CardMask().set(BaseCard::COMMUNE), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_BATTLE_TRANCE, new calculators::Percent(7), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_BATTLE_TRANCE, new calculators::Percent(7), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_1] = new EffectsAbility(ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_1, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_1, CardMask().set(BaseCard::COMMUNE), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_1, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_1, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_2] = new EffectsAbility(ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_2, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_2, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_THE_GREATNESS_OF_THE_WAR_2, new calculators::Percent(3), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_DARK_HAND] = new EffectsAbility(ability::TOTEMS_DARK_HAND, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_DARK_HAND, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_DARK_HAND, new calculators::Percent(3), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_DARK_HAND, new calculators::Percent(3), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_UNSTOPPABLE_GROWTH] = new EffectsAbility(ability::TOTEMS_UNSTOPPABLE_GROWTH, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_UNSTOPPABLE_GROWTH, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_UNSTOPPABLE_GROWTH, new calculators::Percent(5), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_UNSTOPPABLE_GROWTH, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_AFTERLIFE_KNOWLEDGE] = new EffectsAbility(ability::TOTEMS_AFTERLIFE_KNOWLEDGE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_AFTERLIFE_KNOWLEDGE, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_AFTERLIFE_KNOWLEDGE, new calculators::Percent(7), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_AFTERLIFE_KNOWLEDGE, new calculators::Percent(7), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_THE_DOMINANCE_OF_DEATH_1] = new EffectsAbility(ability::TOTEMS_THE_DOMINANCE_OF_DEATH_1, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_THE_DOMINANCE_OF_DEATH_1, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_THE_DOMINANCE_OF_DEATH_1, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_THE_DOMINANCE_OF_DEATH_1, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_THE_DOMINANCE_OF_DEATH_2] = new EffectsAbility(ability::TOTEMS_THE_DOMINANCE_OF_DEATH_2, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_THE_DOMINANCE_OF_DEATH_2, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_THE_DOMINANCE_OF_DEATH_2, new calculators::Percent(3), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_PHENOMENA_HROARHINA] = new EffectsAbility(ability::TOTEMS_PHENOMENA_HROARHINA, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_PHENOMENA_HROARHINA, CardMask().set(BaseCard::NORTH), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_PHENOMENA_HROARHINA, new calculators::Percent(3), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_PHENOMENA_HROARHINA, new calculators::Percent(3), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_COMBINING_HOMES] = new EffectsAbility(ability::TOTEMS_COMBINING_HOMES, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_COMBINING_HOMES, CardMask().set(BaseCard::NORTH), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_COMBINING_HOMES, new calculators::Percent(5), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_COMBINING_HOMES, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_CRUSADE] = new EffectsAbility(ability::TOTEMS_CRUSADE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_CRUSADE, CardMask().set(BaseCard::NORTH), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_CRUSADE, new calculators::Percent(7), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_CRUSADE, new calculators::Percent(7), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_CONSEQUENCES_OF_FAITH_1] = new EffectsAbility(ability::TOTEMS_CONSEQUENCES_OF_FAITH_1, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_CONSEQUENCES_OF_FAITH_1, CardMask().set(BaseCard::NORTH), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_CONSEQUENCES_OF_FAITH_1, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_CONSEQUENCES_OF_FAITH_1, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_CONSEQUENCES_OF_FAITH_2] = new EffectsAbility(ability::TOTEMS_CONSEQUENCES_OF_FAITH_2, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_CONSEQUENCES_OF_FAITH_2, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_CONSEQUENCES_OF_FAITH_2, new calculators::Percent(3), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_BLESSING_SEED] = new EffectsAbility(ability::TOTEMS_BLESSING_SEED, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_BLESSING_SEED, CardMask().set(BaseCard::FRATERNITY), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_BLESSING_SEED, new calculators::Percent(3), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_BLESSING_SEED, new calculators::Percent(3), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_THE_POWER_OF_NATURE] = new EffectsAbility(ability::TOTEMS_THE_POWER_OF_NATURE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_THE_POWER_OF_NATURE, CardMask().set(BaseCard::FRATERNITY), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_THE_POWER_OF_NATURE, new calculators::Percent(5), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_THE_POWER_OF_NATURE, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_DAYLIGHT] = new EffectsAbility(ability::TOTEMS_DAYLIGHT, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_DAYLIGHT, CardMask().set(BaseCard::FRATERNITY), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_DAYLIGHT, new calculators::Percent(7), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_DAYLIGHT, new calculators::Percent(7), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_TOUCHING_ERYL_1] = new EffectsAbility(ability::TOTEMS_TOUCHING_ERYL_1, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_TOUCHING_ERYL_1, CardMask().set(BaseCard::FRATERNITY), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_TOUCHING_ERYL_1, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::TOTEMS_TOUCHING_ERYL_1, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::TOTEMS_TOUCHING_ERYL_2] = new EffectsAbility(ability::TOTEMS_TOUCHING_ERYL_2, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::TOTEMS_TOUCHING_ERYL_2, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::TOTEMS_TOUCHING_ERYL_2, new calculators::Percent(3), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
}

TotemsAbilitiesParams::TotemsAbilitiesParams(IDGenerator &ids)
{
	this->init(ids);
}

TotemsAbilitiesParams::~TotemsAbilitiesParams()
{
	for (auto &pair : this->abilities)
		delete pair.second;
}

const Ability* TotemsAbilitiesParams::get(ability::Type type) const
{
	auto found = this->abilities.find(type);
	if (found == this->abilities.cend())
	{
		logger()->warning("Invalid totem ability %u requested", enum_unwrap(type));
		throw Exception("Invalid totem ability requested");
	}

	return found->second;
}

PassiveAbilities::passives_t TotemsAbilitiesParams::get(const ability::abilities_t &types) const
{
	PassiveAbilities::passives_t result;
	result.reserve(types.size());
	for (auto type : types)
		result.push_back(this->get(type));

	return result;
}