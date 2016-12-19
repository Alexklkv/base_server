#include "EquipmentAbilitiesParams.h"

#include "BaseCard.h"
#include "Enum.h"
#include "Exception.h"
#include "Log.h"

#include "ability/abilities/EffectsAbility.h"
#include "ability/effects/ExtraCriticalEffect.h"
#include "ability/effects/ExtraDamageEffect.h"
#include "ability/effects/ExtraDodgeEffect.h"
#include "ability/effects/ExtraHealthEffect.h"
#include "ability/effects/ExtraSpellStrength.h"
#include "ability/effects/MagicResistanceEffect.h"
#include "ability/effects/OnAttackEffect.h"
#include "ability/effects/OnReceivedAttackEfect.h"
#include "ability/effects/StatsEffectsApplier.h"
#include "ability/effects/VampirismEffect.h"

#include "misc.h"

void EquipmentAbilitiesParams::init(IDGenerator &ids)
{
	/// PAULDRONS
	this->abilities[ability::EQUIPMENT_WORN_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_WORN_SHOULDERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_WORN_SHOULDERS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_WORN_SHOULDERS, new calculators::Percent(2), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_CHAMPION_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_CHAMPION_SHOULDERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_CHAMPION_SHOULDERS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_CHAMPION_SHOULDERS, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_PALADIN_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_PALADIN_SHOULDERS, AbilityTargeting::all_friend_targets_with_summoner, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_PALADIN_SHOULDERS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_PALADIN_SHOULDERS, new calculators::Percent(5), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_PALADIN_SHOULDERS, CardMask().set(BaseCard::GUARD), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_PALADIN_SHOULDERS, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_RAIDER_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_RAIDER_SHOULDERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_RAIDER_SHOULDERS, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_RAIDER_SHOULDERS, new calculators::Percent(5), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_PATHFINDER_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_PATHFINDER_SHOULDERS, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::EQUIPMENT_PATHFINDER_SHOULDERS, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_PATHFINDER_SHOULDERS, new calculators::Percent(-10), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_EMISSARY_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_EMISSARY_SHOULDERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_EMISSARY_SHOULDERS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_EMISSARY_SHOULDERS, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_EMISSARY_SHOULDERS, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_MAGE_CLOAK] = new EffectsAbility(ability::EQUIPMENT_MAGE_CLOAK, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_MAGE_CLOAK, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::EQUIPMENT_MAGE_CLOAK, 15, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_NECROMANCER_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_NECROMANCER_SHOULDERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_NECROMANCER_SHOULDERS, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::EQUIPMENT_NECROMANCER_SHOULDERS, 20, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_WITCHING_CROWS] = new EffectsAbility(ability::EQUIPMENT_WITCHING_CROWS, AbilityTargeting::all_enemy_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_WITCHING_CROWS, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::EQUIPMENT_WITCHING_CROWS, 0, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_INTIMIDATORS_SHOULDERS] = new EffectsAbility(ability::EQUIPMENT_INTIMIDATORS_SHOULDERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_INTIMIDATORS_SHOULDERS, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_INTIMIDATORS_SHOULDERS, new calculators::Percent(20), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});

	/// BODY
	this->abilities[ability::EQUIPMENT_ELVEN_JACKET] = new EffectsAbility(ability::EQUIPMENT_ELVEN_JACKET, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_ELVEN_JACKET, CardMask().set(BaseCard::DESTROYER).set(BaseCard::DISTANT), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_ELVEN_JACKET, new calculators::Percent(20), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_RICH_TEGILYAY] = new EffectsAbility(ability::EQUIPMENT_RICH_TEGILYAY, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_RICH_TEGILYAY, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_RICH_TEGILYAY, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_SURCOAT_NECROMANCER] = new EffectsAbility(ability::EQUIPMENT_SURCOAT_NECROMANCER, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_SURCOAT_NECROMANCER, CardMask().set(BaseCard::DEAD_LEGION).set(BaseCard::SUPPORT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_SURCOAT_NECROMANCER, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_THE_CAMISOLE_ELDERS] = new EffectsAbility(ability::EQUIPMENT_THE_CAMISOLE_ELDERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_THE_CAMISOLE_ELDERS, CardMask().set(BaseCard::SUPPORT), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_THE_CAMISOLE_ELDERS, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_BREASTPLATE_ABSORBER] = new EffectsAbility(ability::EQUIPMENT_BREASTPLATE_ABSORBER, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::EQUIPMENT_BREASTPLATE_ABSORBER, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_BREASTPLATE_ABSORBER, new calculators::Percent(-10), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});

	/// GLOVES
	this->abilities[ability::EQUIPMENT_WARRIOR_BRACERS] = new EffectsAbility(ability::EQUIPMENT_WARRIOR_BRACERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_WARRIOR_BRACERS, CardMask().set(BaseCard::GUARD), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_WARRIOR_BRACERS, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_HIGHT_QUALITY_BRACERS] = new EffectsAbility(ability::EQUIPMENT_HIGHT_QUALITY_BRACERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_HIGHT_QUALITY_BRACERS, CardMask().set(BaseCard::DESTROYER), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_HIGHT_QUALITY_BRACERS, new calculators::Percent(15), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_PALADIN_BRACERS] = new EffectsAbility(ability::EQUIPMENT_PALADIN_BRACERS, AbilityTargeting::all_friend_targets, {
		new OnAttackEffect(ids.next(), ability::EQUIPMENT_PALADIN_BRACERS, 100, CardMask().set(BaseCard::SUPPORT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_PALADIN_BRACERS, new calculators::Percent(15), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_ELVEN_BRACERS] = new EffectsAbility(ability::EQUIPMENT_ELVEN_BRACERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_ELVEN_BRACERS, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_ELVEN_BRACERS, new calculators::Percent(15), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_GOLDEN_BRACERS] = new EffectsAbility(ability::EQUIPMENT_GOLDEN_BRACERS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_GOLDEN_BRACERS, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_GOLDEN_BRACERS, new calculators::Percent(15), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_WIZARD_BRACERS] = new EffectsAbility(ability::EQUIPMENT_WIZARD_BRACERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_WIZARD_BRACERS, CardMask(), {
			new ExtraSpellStrength(ids.next(), ability::EQUIPMENT_WIZARD_BRACERS, 10, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_DARK_WIZARD_BRACERS] = new EffectsAbility(ability::EQUIPMENT_DARK_WIZARD_BRACERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_DARK_WIZARD_BRACERS, CardMask(), {
			new ExtraSpellStrength(ids.next(), ability::EQUIPMENT_DARK_WIZARD_BRACERS, 20, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_SORCERER_BRACELETS] = new EffectsAbility(ability::EQUIPMENT_SORCERER_BRACELETS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_SORCERER_BRACELETS, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::EQUIPMENT_SORCERER_BRACELETS, 15, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});

	/// LEGS
	this->abilities[ability::EQUIPMENT_RELIABLE_GREAVES] = new EffectsAbility(ability::EQUIPMENT_RELIABLE_GREAVES, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_RELIABLE_GREAVES, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_RELIABLE_GREAVES, new calculators::Percent(5), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_BRIGANDINE_SKIRT] = new EffectsAbility(ability::EQUIPMENT_BRIGANDINE_SKIRT, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_BRIGANDINE_SKIRT, CardMask().set(BaseCard::DESTROYER).set(BaseCard::MELEE), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_BRIGANDINE_SKIRT, new calculators::Percent(15), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_SATIN_MANTLE] = new EffectsAbility(ability::EQUIPMENT_SATIN_MANTLE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_SATIN_MANTLE, CardMask().set(BaseCard::SUPPORT), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_SATIN_MANTLE, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_SKIRT_DARK_WIZARD] = new EffectsAbility(ability::EQUIPMENT_SKIRT_DARK_WIZARD, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_SKIRT_DARK_WIZARD, CardMask().set(BaseCard::SUPPORT), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_SKIRT_DARK_WIZARD, new calculators::Percent(15), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_PANTS_ELDERS] = new EffectsAbility(ability::EQUIPMENT_PANTS_ELDERS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_PANTS_ELDERS, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_PANTS_ELDERS, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_GAITERS_LORD] = new EffectsAbility(ability::EQUIPMENT_GAITERS_LORD, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_GAITERS_LORD, CardMask().set(BaseCard::DESTROYER).set(BaseCard::DEAD_LEGION), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_GAITERS_LORD, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});

	/// SHOES
	this->abilities[ability::EQUIPMENT_OLD_LEGGINGS] = new EffectsAbility(ability::EQUIPMENT_OLD_LEGGINGS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_OLD_LEGGINGS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_OLD_LEGGINGS, new calculators::Percent(2), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_PALADIN_LEGGINGS] = new EffectsAbility(ability::EQUIPMENT_PALADIN_LEGGINGS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_PALADIN_LEGGINGS, CardMask().set(BaseCard::GUARD), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_PALADIN_LEGGINGS, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_BOUNTY_HUNTER_BOOTS] = new EffectsAbility(ability::EQUIPMENT_BOUNTY_HUNTER_BOOTS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_BOUNTY_HUNTER_BOOTS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_BOUNTY_HUNTER_BOOTS, new calculators::Percent(4), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_ELVEN_SHIN] = new EffectsAbility(ability::EQUIPMENT_ELVEN_SHIN, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_ELVEN_SHIN, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_ELVEN_SHIN, new calculators::Percent(5), BattleEffect::policy_infinite()),
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_ELVEN_SHIN, new calculators::Percent(15), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_GOLDEN_LEGGINGS] = new EffectsAbility(ability::EQUIPMENT_GOLDEN_LEGGINGS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_GOLDEN_LEGGINGS, CardMask().set(BaseCard::DESTROYER), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_GOLDEN_LEGGINGS, new calculators::Percent(15), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_RICH_BOOTS] = new EffectsAbility(ability::EQUIPMENT_RICH_BOOTS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_RICH_BOOTS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_RICH_BOOTS, new calculators::Percent(3), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_EXTERMINATOR_LEGGINGS] = new EffectsAbility(ability::EQUIPMENT_EXTERMINATOR_LEGGINGS, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_EXTERMINATOR_LEGGINGS, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_EXTERMINATOR_LEGGINGS, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_EXTERMINATOR_LEGGINGS, new calculators::Percent(15), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});

	/// HELMET
	this->abilities[ability::EQUIPMENT_FALCON_FURY] = new EffectsAbility(ability::EQUIPMENT_FALCON_FURY, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_FALCON_FURY, CardMask().set(BaseCard::FLYING), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_FALCON_FURY, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});

	/// WEAPON
	this->abilities[ability::EQUIPMENT_NECROMANCER_STAFF] = new EffectsAbility(ability::EQUIPMENT_NECROMANCER_STAFF, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_NECROMANCER_STAFF, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_NECROMANCER_STAFF, new calculators::Percent(15), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_NECROMANCER_STAFF, new calculators::Percent(15), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_HALBERD_PALACE_GUARDS] = new EffectsAbility(ability::EQUIPMENT_HALBERD_PALACE_GUARDS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_HALBERD_PALACE_GUARDS, CardMask().set(BaseCard::GUARD), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_HALBERD_PALACE_GUARDS, new calculators::Percent(10), BattleEffect::policy_infinite()),
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_HALBERD_PALACE_GUARDS, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_PIEDMONT_LORD_HAMMER] = new EffectsAbility(ability::EQUIPMENT_PIEDMONT_LORD_HAMMER, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_PIEDMONT_LORD_HAMMER, CardMask().set(BaseCard::EARTH), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_PIEDMONT_LORD_HAMMER, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_CRUSHER_SKULLS] = new EffectsAbility(ability::EQUIPMENT_CRUSHER_SKULLS, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_CRUSHER_SKULLS, CardMask().set(BaseCard::DESTROYER).set(BaseCard::MELEE), {
			new ExtraCriticalEffect(ids.next(), ability::EQUIPMENT_CRUSHER_SKULLS, new calculators::Value(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_FLAMING] = new EffectsAbility(ability::EQUIPMENT_FLAMING, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_FLAMING, CardMask().set(BaseCard::FIRE), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_FLAMING, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_ICE_SOUL] = new EffectsAbility(ability::EQUIPMENT_ICE_SOUL, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_ICE_SOUL, CardMask().set(BaseCard::WATER), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_ICE_SOUL, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_REAPER] = new EffectsAbility(ability::EQUIPMENT_REAPER, AbilityTargeting::all_friend_targets, {
		new OnAttackEffect(ids.next(), ability::EQUIPMENT_REAPER, 15, CardMask().set(BaseCard::DEAD_LEGION), {
			new VampirismEffect(ids.next(), ability::EQUIPMENT_REAPER, new calculators::Percent(20), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_WAND_SUMMONER] = new EffectsAbility(ability::EQUIPMENT_WAND_SUMMONER, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_WAND_SUMMONER, CardMask(), {
			new ExtraSpellStrength(ids.next(), ability::EQUIPMENT_WAND_SUMMONER, 20, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_WOLF_BLADE] = new EffectsAbility(ability::EQUIPMENT_WOLF_BLADE, AbilityTargeting::all_friend_targets, {
		new OnAttackEffect(ids.next(), ability::EQUIPMENT_WOLF_BLADE, 100, CardMask().set(BaseCard::DEAD_LEGION).set(BaseCard::FRATERNITY), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_WOLF_BLADE, new calculators::Percent(10), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_DHELL_GIFT] = new EffectsAbility(ability::EQUIPMENT_DHELL_GIFT, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_DHELL_GIFT, CardMask().set(BaseCard::DESTROYER), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_DHELL_GIFT, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_DHELL_GIFT, CardMask(), {
			new ExtraCriticalEffect(ids.next(), ability::EQUIPMENT_DHELL_GIFT, new calculators::Value(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_DHELL_GIFT, CardMask().set(BaseCard::MELEE), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_DHELL_GIFT, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_REGALIA_POWER] = new EffectsAbility(ability::EQUIPMENT_REGALIA_POWER, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_REGALIA_POWER, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_REGALIA_POWER, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_DEVIL_BLADE] = new EffectsAbility(ability::EQUIPMENT_DEVIL_BLADE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_DEVIL_BLADE, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_DEVIL_BLADE, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_FIGHTER_ORCS] = new EffectsAbility(ability::EQUIPMENT_FIGHTER_ORCS, AbilityTargeting::all_friend_targets, {
		new OnAttackEffect(ids.next(), ability::EQUIPMENT_FIGHTER_ORCS, 100, CardMask().set(BaseCard::FRATERNITY), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_FIGHTER_ORCS, new calculators::Percent(10), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_BOW_OF_SEARING_ARROWS] = new EffectsAbility(ability::EQUIPMENT_BOW_OF_SEARING_ARROWS, AbilityTargeting::all_friend_targets, {
		new OnAttackEffect(ids.next(), ability::EQUIPMENT_BOW_OF_SEARING_ARROWS, 100, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_BOW_OF_SEARING_ARROWS, new calculators::Percent(10), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_ASTRAL_WORLD_STAFF] = new EffectsAbility(ability::EQUIPMENT_ASTRAL_WORLD_STAFF, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_ASTRAL_WORLD_STAFF, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_ASTRAL_WORLD_STAFF, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_HEAD_CRACKER] = new EffectsAbility(ability::EQUIPMENT_HEAD_CRACKER, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_HEAD_CRACKER, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_HEAD_CRACKER, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_STAFF_SAGE] = new EffectsAbility(ability::EQUIPMENT_STAFF_SAGE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_STAFF_SAGE, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_STAFF_SAGE, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_HARMFUL_RAPIER_REVENGE] = new EffectsAbility(ability::EQUIPMENT_HARMFUL_RAPIER_REVENGE, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_HARMFUL_RAPIER_REVENGE, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_HARMFUL_RAPIER_REVENGE, new calculators::Percent(15), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_BOW_HUNTER] = new EffectsAbility(ability::EQUIPMENT_BOW_HUNTER, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_BOW_HUNTER, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_BOW_HUNTER, new calculators::Percent(15), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_NORTHERN_FLAME_SWORD] = new EffectsAbility(ability::EQUIPMENT_NORTHERN_FLAME_SWORD, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_NORTHERN_FLAME_SWORD, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_NORTHERN_FLAME_SWORD, new calculators::Percent(15), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});

	/// SHIELD
	this->abilities[ability::EQUIPMENT_NORTH_GUARD_SHIELD] = new EffectsAbility(ability::EQUIPMENT_NORTH_GUARD_SHIELD, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_NORTH_GUARD_SHIELD, CardMask().set(BaseCard::NORTH), {
			new ExtraHealthEffect(ids.next(), ability::EQUIPMENT_NORTH_GUARD_SHIELD, new calculators::Percent(10), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_DEFENDER_THICKETS] = new EffectsAbility(ability::EQUIPMENT_DEFENDER_THICKETS, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::EQUIPMENT_DEFENDER_THICKETS, 100, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_DEFENDER_THICKETS, new calculators::Percent(-15), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_SHIELD_HIGHLANDER] = new EffectsAbility(ability::EQUIPMENT_SHIELD_HIGHLANDER, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::EQUIPMENT_SHIELD_HIGHLANDER, 100, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_SHIELD_HIGHLANDER, new calculators::Percent(-15), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_GLADIATORIAL_BUCKLER] = new EffectsAbility(ability::EQUIPMENT_GLADIATORIAL_BUCKLER, AbilityTargeting::all_friend_targets, {
		new StatsEffectsApplier(ids.next(), ability::EQUIPMENT_GLADIATORIAL_BUCKLER, CardMask().set(BaseCard::DESTROYER), {
			new ExtraDodgeEffect(ids.next(), ability::EQUIPMENT_GLADIATORIAL_BUCKLER, new calculators::Percent(5), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::EQUIPMENT_SHIELD_WALL_CITADEL] = new EffectsAbility(ability::EQUIPMENT_SHIELD_WALL_CITADEL, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::EQUIPMENT_SHIELD_WALL_CITADEL, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_SHIELD_WALL_CITADEL, new calculators::Percent(-10), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::EQUIPMENT_AN_ANCIENT_ENEMY] = new EffectsAbility(ability::EQUIPMENT_AN_ANCIENT_ENEMY, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::EQUIPMENT_AN_ANCIENT_ENEMY, 100, CardMask().set(BaseCard::FLYING), {
			new ExtraDamageEffect(ids.next(), ability::EQUIPMENT_AN_ANCIENT_ENEMY, new calculators::Percent(-15), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
}

EquipmentAbilitiesParams::EquipmentAbilitiesParams(IDGenerator &ids)
{
	this->init(ids);
}

EquipmentAbilitiesParams::~EquipmentAbilitiesParams()
{
	for (auto &pair : this->abilities)
		delete pair.second;
}

const Ability* EquipmentAbilitiesParams::get(ability::Type type) const
{
	auto found = this->abilities.find(type);
	if (found == this->abilities.cend())
	{
		logger()->warning("Invalid equipment ability %u requested", enum_unwrap(type));
		throw Exception("Invalid equipment ability requested");
	}

	return found->second;
}

PassiveAbilities::passives_t EquipmentAbilitiesParams::get(const ability::abilities_t &types) const
{
	PassiveAbilities::passives_t result;
	result.reserve(types.size());
	for (auto type : types)
	{
		try
		{
			// TODO: Remove when all abilities are implemented.
			result.push_back(this->get(type));
		}
		catch (Exception &)
		{}
	}

	return result;
}