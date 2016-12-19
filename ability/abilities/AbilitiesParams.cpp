#include "AbilitiesParams.h"

#include "BaseCard.h"
#include "EffectsAbility.h"
#include "Enum.h"
#include "Exception.h"
#include "Log.h"

#include "ability/effects/AttackMoveEffect.h"
#include "ability/effects/BattleJoyEffect.h"
#include "ability/effects/BlockAttackEffect.h"
#include "ability/effects/BloodLustEffect.h"
#include "ability/effects/CannibalEffect.h"
#include "ability/effects/ChainReactionEffect.h"
#include "ability/effects/CsaadGiftEffect.h"
#include "ability/effects/DiscardExtraEffect.h"
#include "ability/effects/EagernessEffect.h"
#include "ability/effects/EarthThremorsEffect.h"
#include "ability/effects/EriylsSalvationEffect.h"
#include "ability/effects/EternalGuardEffect.h"
#include "ability/effects/ExtictionEffect.h"
#include "ability/effects/ExtraDamageEffect.h"
#include "ability/effects/ExtraDamageOnAttackEffect.h"
#include "ability/effects/ExtraDodgeEffect.h"
#include "ability/effects/ExtraHealthEffect.h"
#include "ability/effects/ExtraReceivedDamageEffect.h"
#include "ability/effects/ForbidMoveEffect.h"
#include "ability/effects/FuryEffect.h"
#include "ability/effects/HealerEffect.h"
#include "ability/effects/IfritEffect.h"
#include "ability/effects/InsanityEffect.h"
#include "ability/effects/IllusionEffect.h"
#include "ability/effects/MagicResistanceEffect.h"
#include "ability/effects/MarauderEffect.h"
#include "ability/effects/MeditationEffect.h"
#include "ability/effects/MirrorShieldEffect.h"
#include "ability/effects/NecromancyEffect.h"
#include "ability/effects/NoResponseEffect.h"
#include "ability/effects/OnAttackEffect.h"
#include "ability/effects/OnReceivedAttackEfect.h"
#include "ability/effects/OnResponseEffect.h"
#include "ability/effects/ParasiteEffect.h"
#include "ability/effects/PiercingStrikeEffect.h"
#include "ability/effects/PoisoningEffect.h"
#include "ability/effects/ProvocationEffect.h"
#include "ability/effects/RegenerationEffect.h"
#include "ability/effects/RevengeEffect.h"
#include "ability/effects/SacrificeEffect.h"
#include "ability/effects/SorcererEffect.h"
#include "ability/effects/StatsEffectsApplier.h"
#include "ability/effects/SuicideEffect.h"
#include "ability/effects/TacticalRetreatEffect.h"
#include "ability/effects/TargetFractionDamageEffect.h"
#include "ability/effects/TrapperturtleEffect.h"
#include "ability/effects/VampirismEffect.h"
#include "ability/effects/WatchDogEffect.h"

#include "misc.h"

void AbilitiesParams::init(IDGenerator &ids)
{
	/// Cards
	this->abilities[ability::CARD_STONE_WALL] = new EffectsAbility(ability::CARD_STONE_WALL, AbilityTargeting::behind_target, {
		new StatsEffectsApplier(ids.next(), ability::CARD_STONE_WALL, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::CARD_STONE_WALL, new calculators::Percent(20), BattleEffect::policy_placement())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_LACERATIONS] = new EffectsAbility(ability::CARD_LACERATIONS, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_LACERATIONS, 100, CardMask(), {
			new ExtraReceivedDamageEffect(ids.next(), ability::CARD_LACERATIONS, BaseCard::Range::NONE, BaseCard::Fraction::NEUTRAL, 5, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_HEALER] = new EffectsAbility(ability::CARD_HEALER, AbilityTargeting::self, {
		new HealerEffect(ids.next(), ability::CARD_HEALER, new calculators::Percent(50), BattleEffect::policy_turn(1))
	});
	this->abilities[ability::CARD_LEADER] = new EffectsAbility(ability::CARD_LEADER, AbilityTargeting::self_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_LEADER, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::CARD_LEADER, new calculators::Percent(20), BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_SORCERER] = new EffectsAbility(ability::CARD_SORCERER, AbilityTargeting::self, {
		new SorcererEffect(ids.next(), ability::CARD_SORCERER, new calculators::Percent(10), BattleEffect::policy_turn(1))
	});
	this->abilities[ability::CARD_FLIGHT] = new EffectsAbility(ability::CARD_FLIGHT, AbilityTargeting::self, {
		//new OnReceivedAttackEfect(ids.next(), ability::CARD_FLIGHT, 100, CardMask().set(BaseCard::MELEE), {
		//	new BlockAttackEffect(ids.next(), ability::CARD_FLIGHT, BattleEffect::policy_actions(1))
		//}, BattleEffect::policy_infinite()),
		//new OnReceivedAttackEfect(ids.next(), ability::CARD_FLIGHT, 5, CardMask(true).set(BaseCard::MELEE), {
		//	new BlockAttackEffect(ids.next(), ability::CARD_FLIGHT, BattleEffect::policy_actions(1))
		//}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ORCS_HUNTER] = new EffectsAbility(ability::CARD_ORCS_HUNTER, AbilityTargeting::self, {
		new TargetFractionDamageEffect(ids.next(), ability::CARD_ORCS_HUNTER, CardMask().set(BaseCard::COMMUNE), new calculators::Percent(35), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_MAN_EATER] = new EffectsAbility(ability::CARD_MAN_EATER, AbilityTargeting::self, {
		new TargetFractionDamageEffect(ids.next(), ability::CARD_MAN_EATER, CardMask().set(BaseCard::NORTH), new calculators::Percent(35), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ELVES_HUNTER] = new EffectsAbility(ability::CARD_ELVES_HUNTER, AbilityTargeting::self, {
		new TargetFractionDamageEffect(ids.next(), ability::CARD_ELVES_HUNTER, CardMask().set(BaseCard::FRATERNITY), new calculators::Percent(35), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_EXORCIST] = new EffectsAbility(ability::CARD_EXORCIST, AbilityTargeting::self, {
		new TargetFractionDamageEffect(ids.next(), ability::CARD_EXORCIST, CardMask().set(BaseCard::DEAD_LEGION), new calculators::Percent(35), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_PIERCING_STRIKE] = new EffectsAbility(ability::CARD_PIERCING_STRIKE, AbilityTargeting::self, {
		new PiercingStrikeEffect(ids.next(), ability::CARD_PIERCING_STRIKE, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_TRAPPERTURTLLE] = new EffectsAbility(ability::CARD_TRAPPERTURTLLE, AbilityTargeting::self, {
		new TrapperturtleEffect(ids.next(), ability::CARD_TRAPPERTURTLLE, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_EAGERNESS] = new EffectsAbility(ability::CARD_EAGERNESS, AbilityTargeting::self, {
		new EagernessEffect(ids.next(), ability::CARD_EAGERNESS, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_PROVOCATION] = new EffectsAbility(ability::CARD_PROVOCATION, AbilityTargeting::enemy_row_targets, {
		new ProvocationEffect(ids.next(), ability::CARD_PROVOCATION, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_FURY] = new EffectsAbility(ability::CARD_FURY, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::CARD_FURY, CardMask(), {
			new FuryEffect(ids.next(), ability::CARD_FURY, new calculators::Percent(30), new calculators::Percent(30), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_CHARMED] = new EffectsAbility(ability::CARD_CHARMED, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::CARD_CHARMED, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::CARD_CHARMED, 100, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ELUSIVE] = new EffectsAbility(ability::CARD_ELUSIVE, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_ELUSIVE, 100, CardMask().set(BaseCard::DISTANT), {
			new BlockAttackEffect(ids.next(), ability::CARD_ELUSIVE, BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::CARD_SHIELD] = new EffectsAbility(ability::CARD_SHIELD, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::CARD_SHIELD, CardMask(), {
			new ExtraDodgeEffect(ids.next(), ability::CARD_SHIELD, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_MEDITATION] = new EffectsAbility(ability::CARD_MEDITATION, AbilityTargeting::self, {
		new MeditationEffect(ids.next(), ability::CARD_MEDITATION, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_VAMPRISM] = new EffectsAbility(ability::CARD_VAMPRISM, AbilityTargeting::self, {
		new VampirismEffect(ids.next(), ability::CARD_VAMPRISM, new calculators::Percent(30), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_POISON] = new EffectsAbility(ability::CARD_POISON, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_POISON, 100, CardMask(), {
			new PoisoningEffect(ids.next(), ability::CARD_POISON, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_FEAR] = new EffectsAbility(ability::CARD_FEAR, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_FEAR, 100, CardMask(true).set(BaseCard::DEAD_LEGION), {
			new NoResponseEffect(ids.next(), ability::CARD_FEAR, BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_SACRIFICE] = new EffectsAbility(ability::CARD_SACRIFICE, AbilityTargeting::self, {
		new SacrificeEffect(ids.next(), ability::CARD_SACRIFICE, new calculators::Percent(30), BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_MARAUDER] = new EffectsAbility(ability::CARD_MARAUDER, AbilityTargeting::self, {
		new MarauderEffect(ids.next(), ability::CARD_MARAUDER, new calculators::Percent(35), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ERIYLS_SALVATION] = new EffectsAbility(ability::CARD_ERIYLS_SALVATION, AbilityTargeting::self, {
		new EriylsSalvationEffect(ids.next(), ability::CARD_ERIYLS_SALVATION, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_COMISSAR] = new EffectsAbility(ability::CARD_COMISSAR, AbilityTargeting::front_target, {
		new EagernessEffect(ids.next(), ability::CARD_COMISSAR, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_SUPPRESSION] = new EffectsAbility(ability::CARD_SUPPRESSION, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_SUPPRESSION, 60, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::CARD_SUPPRESSION, new calculators::Percent(-20), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_GUARDING_SPELLS] = new EffectsAbility(ability::CARD_GUARDING_SPELLS, AbilityTargeting::self_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_GUARDING_SPELLS, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::CARD_GUARDING_SPELLS, new calculators::Percent(20), BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_INVIOLABILITY] = new EffectsAbility(ability::CARD_INVIOLABILITY, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_INVIOLABILITY, 100, CardMask().set(BaseCard::MELEE), {
			new BlockAttackEffect(ids.next(), ability::CARD_INVIOLABILITY, BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::CARD_BLOOD_THIRST] = new EffectsAbility(ability::CARD_BLOOD_THIRST, AbilityTargeting::self, {
		new BloodLustEffect(ids.next(), ability::CARD_BLOOD_THIRST, new calculators::Percent(10), BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_ABSORPTION] = new EffectsAbility(ability::CARD_ABSORPTION, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_ABSORPTION, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::CARD_ABSORPTION, new calculators::Percent(-30), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_THICK_SKINNED] = new EffectsAbility(ability::CARD_THICK_SKINNED, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_THICK_SKINNED, 100, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::CARD_THICK_SKINNED, new calculators::Percent(-30), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_HOLY_ARMOR] = new EffectsAbility(ability::CARD_HOLY_ARMOR, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_HOLY_ARMOR, 100, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraDamageEffect(ids.next(), ability::CARD_HOLY_ARMOR, new calculators::Percent(-30), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_DROVER] = new EffectsAbility(ability::CARD_DROVER, AbilityTargeting::self_fraction_targets, {
		new EagernessEffect(ids.next(), ability::CARD_DROVER, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_FOREST_MASTER] = new EffectsAbility(ability::CARD_FOREST_MASTER, AbilityTargeting::self_fraction_targets, {
		new EagernessEffect(ids.next(), ability::CARD_FOREST_MASTER, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_SHADOW_LORD] = new EffectsAbility(ability::CARD_SHADOW_LORD, AbilityTargeting::self_fraction_targets, {
		new EagernessEffect(ids.next(), ability::CARD_SHADOW_LORD, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_COMMANDER] = new EffectsAbility(ability::CARD_COMMANDER, AbilityTargeting::self_fraction_targets, {
		new EagernessEffect(ids.next(), ability::CARD_COMMANDER, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_KAMIKADZE] = new EffectsAbility(ability::CARD_KAMIKADZE, AbilityTargeting::self, {
		new EagernessEffect(ids.next(), ability::CARD_KAMIKADZE, BattleEffect::policy_placement()),
		new SuicideEffect(ids.next(), ability::CARD_KAMIKADZE, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_INFIRMITY_AURA] = new EffectsAbility(ability::CARD_INFIRMITY_AURA, AbilityTargeting::enemy_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_INFIRMITY_AURA, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::CARD_INFIRMITY_AURA, new calculators::Percent(-20), BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_PARASITE] = new EffectsAbility(ability::CARD_PARASITE, AbilityTargeting::self, {
		new ParasiteEffect(ids.next(), ability::CARD_PARASITE, new calculators::Percent(5), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_HEAVY_LIFTED] = new EffectsAbility(ability::CARD_HEAVY_LIFTED, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_HEAVY_LIFTED, 30, CardMask(), {
			new ExtraReceivedDamageEffect(ids.next(), ability::CARD_HEAVY_LIFTED, BaseCard::Range::NONE, BaseCard::Fraction::NEUTRAL, -50, BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_SLOW] = new EffectsAbility(ability::CARD_SLOW, AbilityTargeting::self, {
		new NoResponseEffect(ids.next(), ability::CARD_SLOW, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ILLUSION] = new EffectsAbility(ability::CARD_ILLUSION, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::CARD_ILLUSION, CardMask(), {
			new IllusionEffect(ids.next(), ability::CARD_ILLUSION, BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_ETERNAL_GUARD] = new EffectsAbility(ability::CARD_ETERNAL_GUARD, AbilityTargeting::self, {
		new EternalGuardEffect(ids.next(), ability::CARD_ETERNAL_GUARD, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_CSAAD_GIFT] = new EffectsAbility(ability::CARD_CSAAD_GIFT, AbilityTargeting::self, {
		new CsaadGiftEffect(ids.next(), ability::CARD_CSAAD_GIFT, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_DHELL_CALL] = new EffectsAbility(ability::CARD_DHELL_CALL, AbilityTargeting::self_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_DHELL_CALL, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::CARD_DHELL_CALL, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_SNIPER] = new EffectsAbility(ability::CARD_SNIPER, AbilityTargeting::self, {
		new OnResponseEffect(ids.next(), ability::CARD_SNIPER, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::CARD_SNIPER, new calculators::Percent(15), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_FIRE_WEAPON] = new EffectsAbility(ability::CARD_FIRE_WEAPON, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_FIRE_WEAPON, 100, CardMask(true).set(BaseCard::WATER), {
			new ExtraReceivedDamageEffect(ids.next(), ability::CARD_FIRE_WEAPON, BaseCard::Range::NONE, BaseCard::Fraction::NEUTRAL, 10, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ICE_TOUCH] = new EffectsAbility(ability::CARD_ICE_TOUCH, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_ICE_TOUCH, 100, CardMask().set(BaseCard::FIRE), {
			new EternalGuardEffect(ids.next(), ability::CARD_ICE_TOUCH, BattleEffect::policy_turn(2))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_EARTH_TREMORS] = new EffectsAbility(ability::CARD_EARTH_TREMORS, AbilityTargeting::self, {
		new EarthThremorsEffect(ids.next(), ability::CARD_EARTH_TREMORS, CardMask(true).set(BaseCard::AIR).set(BaseCard::FLYING), new calculators::Percent(30), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_HURRICANE_BREATHE] = new EffectsAbility(ability::CARD_HURRICANE_BREATHE, AbilityTargeting::all_enemy_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_HURRICANE_BREATHE, CardMask(true).set(BaseCard::EARTH), {
			new NoResponseEffect(ids.next(), ability::CARD_HURRICANE_BREATHE, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_WATCH_DOG] = new EffectsAbility(ability::CARD_WATCH_DOG, AbilityTargeting::self, {
		new WatchDogEffect(ids.next(), ability::CARD_WATCH_DOG, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_CANNIBAL] = new EffectsAbility(ability::CARD_CANNIBAL, AbilityTargeting::self, {
		new CannibalEffect(ids.next(), ability::CARD_CANNIBAL, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_HOLY_WEAPON] = new EffectsAbility(ability::CARD_HOLY_WEAPON, AbilityTargeting::self, {
		new TargetFractionDamageEffect(ids.next(), ability::CARD_HOLY_WEAPON, CardMask().set(BaseCard::DEAD_LEGION), new calculators::Value(10000), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_PLAGUE_WEAPON] = new EffectsAbility(ability::CARD_PLAGUE_WEAPON, AbilityTargeting::self, {
		new TargetFractionDamageEffect(ids.next(), ability::CARD_PLAGUE_WEAPON, CardMask(true).set(BaseCard::DEAD_LEGION), new calculators::Value(10000), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_CHAIN_REACTION] = new EffectsAbility(ability::CARD_CHAIN_REACTION, AbilityTargeting::self, {
		new ChainReactionEffect(ids.next(), ability::CARD_CHAIN_REACTION, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_MIRROR_SHIELD] = new EffectsAbility(ability::CARD_MIRROR_SHIELD, AbilityTargeting::self, {
		new MirrorShieldEffect(ids.next(), ability::CARD_MIRROR_SHIELD, CardMask().set(BaseCard::DISTANT), new calculators::Percent(30), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_MAGIC_RESISTANCE] = new EffectsAbility(ability::CARD_MAGIC_RESISTANCE, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::CARD_MAGIC_RESISTANCE, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::CARD_MAGIC_RESISTANCE, 50, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_TACTICAL_RETREAT] = new EffectsAbility(ability::CARD_TACTICAL_RETREAT, AbilityTargeting::self, {
		new TacticalRetreatEffect(ids.next(), ability::CARD_TACTICAL_RETREAT, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_IFRIT] = new EffectsAbility(ability::CARD_IFRIT, AbilityTargeting::self, {
		new IfritEffect(ids.next(), ability::CARD_IFRIT, CardMask().set(BaseCard::FIRE), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_CHTHONICAL_DEMON] = new EffectsAbility(ability::CARD_CHTHONICAL_DEMON, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_CHTHONICAL_DEMON, 100, CardMask().set(BaseCard::EARTH), {
			new ExtraDamageEffect(ids.next(), ability::CARD_CHTHONICAL_DEMON, new calculators::Percent(-100), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
		new OnReceivedAttackEfect(ids.next(), ability::CARD_CHTHONICAL_DEMON, 100, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraDamageEffect(ids.next(), ability::CARD_CHTHONICAL_DEMON, new calculators::Percent(-50), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::CARD_SEA_CREATURE] = new EffectsAbility(ability::CARD_SEA_CREATURE, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_SEA_CREATURE, 100, CardMask().set(BaseCard::WATER), {
			new ExtraDamageEffect(ids.next(), ability::CARD_SEA_CREATURE, new calculators::Percent(-100), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
		new OnReceivedAttackEfect(ids.next(), ability::CARD_SEA_CREATURE, 100, CardMask().set(BaseCard::MELEE), {
			new ExtraDamageEffect(ids.next(), ability::CARD_SEA_CREATURE, new calculators::Percent(-30), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::CARD_STORM_SPIRIT] = new EffectsAbility(ability::CARD_STORM_SPIRIT, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_STORM_SPIRIT, 100, CardMask().set(BaseCard::AIR), {
			new ExtraDamageEffect(ids.next(), ability::CARD_STORM_SPIRIT, new calculators::Percent(-100), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
		new OnReceivedAttackEfect(ids.next(), ability::CARD_STORM_SPIRIT, 100, CardMask().set(BaseCard::FLYING), {
			new ExtraDamageEffect(ids.next(), ability::CARD_STORM_SPIRIT, new calculators::Percent(-30), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite()),
	});
	this->abilities[ability::CARD_REGENERATION] = new EffectsAbility(ability::CARD_REGENERATION, AbilityTargeting::self, {
		new RegenerationEffect(ids.next(), ability::CARD_REGENERATION, new calculators::Percent(30), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_MAGIC_COVER] = new EffectsAbility(ability::CARD_MAGIC_COVER, AbilityTargeting::self_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_MAGIC_COVER, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::CARD_MAGIC_COVER, 100, BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_CONTROL] = new EffectsAbility(ability::CARD_CONTROL, AbilityTargeting::enemy_row_targets, {
		new ForbidMoveEffect(ids.next(), ability::CARD_CONTROL, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_INSANITY] = new EffectsAbility(ability::CARD_INSANITY, AbilityTargeting::self, {
		new InsanityEffect(ids.next(), ability::CARD_INSANITY, BattleEffect::policy_infinite()),
		new ForbidMoveEffect(ids.next(), ability::CARD_INSANITY, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_ONSLAUGHT] = new EffectsAbility(ability::CARD_ONSLAUGHT, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_ONSLAUGHT, 50, CardMask(), {
			new AttackMoveEffect(ids.next(), ability::CARD_ONSLAUGHT, BattleEffect::policy_turn(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_CAMOUFLAGE] = new EffectsAbility(ability::CARD_CAMOUFLAGE, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_CAMOUFLAGE, 50, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::CARD_CAMOUFLAGE, new calculators::Percent(-100), BattleEffect::policy_actions(1), true)
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_GIANT] = new EffectsAbility(ability::CARD_GIANT, AbilityTargeting::behind_target, {
		new OnReceivedAttackEfect(ids.next(), ability::CARD_GIANT, 100, CardMask(), {
			new BlockAttackEffect(ids.next(), ability::CARD_GIANT, BattleEffect::policy_actions(1))
		}, BattleEffect::policy_placement()),
	});
	this->abilities[ability::CARD_TROOPER] = new EffectsAbility(ability::CARD_TROOPER, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_TROOPER, 30, CardMask(), {
			new NoResponseEffect(ids.next(), ability::CARD_TROOPER, BattleEffect::policy_turn(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_POINTER] = new EffectsAbility(ability::CARD_POINTER, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::CARD_POINTER, 100, CardMask(), {
			new ExtraReceivedDamageEffect(ids.next(), ability::CARD_POINTER, BaseCard::Range::DISTANT, BaseCard::Fraction::NEUTRAL, 20, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_THUNDERBOLT] = new EffectsAbility(ability::CARD_THUNDERBOLT, AbilityTargeting::self, {
		new ExtraDamageOnAttackEffect(ids.next(), ability::CARD_THUNDERBOLT, BattleEffect::policy_placement(),
			70, ExtraDamageOnAttackEffect::target_health_percent(20))
	});
	this->abilities[ability::CARD_IDENTIFICATION] = new EffectsAbility(ability::CARD_IDENTIFICATION, AbilityTargeting::enemy_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::CARD_IDENTIFICATION, CardMask(), {
			new DiscardExtraEffect(ids.next(), ability::CARD_IDENTIFICATION, BattleEffect::policy_infinite())
		}, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_TRAP] = new EffectsAbility(ability::CARD_TRAP, AbilityTargeting::enemy_row_targets, {
		new NoResponseEffect(ids.next(), ability::CARD_TRAP, BattleEffect::policy_placement())
	});
	this->abilities[ability::CARD_NECROMANCY] = new EffectsAbility(ability::CARD_NECROMANCY, AbilityTargeting::self_row_targets, {
		new NecromancyEffect(ids.next(), ability::CARD_NECROMANCY, new calculators::Percent(50), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_BATTLE_JOY] = new EffectsAbility(ability::CARD_BATTLE_JOY, AbilityTargeting::self, {
		new BattleJoyEffect(ids.next(), ability::CARD_BATTLE_JOY, new calculators::Percent(20), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_EXTICTION] = new EffectsAbility(ability::CARD_EXTICTION, AbilityTargeting::self, {
		new ExtictionEffect(ids.next(), ability::CARD_EXTICTION, new calculators::Percent(-10), BattleEffect::policy_infinite())
	});
	this->abilities[ability::CARD_REVENGE] = new EffectsAbility(ability::CARD_REVENGE, AbilityTargeting::self_row_targets, {
		new RevengeEffect(ids.next(), ability::CARD_REVENGE, new calculators::Percent(25), BattleEffect::policy_placement())
	});

	/// Sharpening
	this->abilities[ability::SHARPENING_CHROARCHINE_LIITANY] = new EffectsAbility(ability::SHARPENING_CHROARCHINE_LIITANY, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_CHROARCHINE_LIITANY, 100, CardMask().set(BaseCard::NORTH), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_CHROARCHINE_LIITANY, new calculators::Percent(-20), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_GRIMOIRE_OF_DEATH] = new EffectsAbility(ability::SHARPENING_GRIMOIRE_OF_DEATH, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_GRIMOIRE_OF_DEATH, 100, CardMask().set(BaseCard::DEAD_LEGION), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_GRIMOIRE_OF_DEATH, new calculators::Percent(-20), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_LEAF_OF_ANCIENT_BLOOM] = new EffectsAbility(ability::SHARPENING_LEAF_OF_ANCIENT_BLOOM, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_LEAF_OF_ANCIENT_BLOOM, 100, CardMask().set(BaseCard::FRATERNITY), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_LEAF_OF_ANCIENT_BLOOM, new calculators::Percent(-20), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_PATRIMONIAL_PLATE] = new EffectsAbility(ability::SHARPENING_PATRIMONIAL_PLATE, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_PATRIMONIAL_PLATE, 100, CardMask().set(BaseCard::COMMUNE), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_PATRIMONIAL_PLATE, new calculators::Percent(-20), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_ALCHEMIST_NOTES] = new EffectsAbility(ability::SHARPENING_ALCHEMIST_NOTES, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::SHARPENING_ALCHEMIST_NOTES, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::SHARPENING_ALCHEMIST_NOTES, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_STRATEGYCON] = new EffectsAbility(ability::SHARPENING_STRATEGYCON, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::SHARPENING_STRATEGYCON, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_STRATEGYCON, new calculators::Percent(10), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_DRAGON_STONE] = new EffectsAbility(ability::SHARPENING_DRAGON_STONE, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_DRAGON_STONE, 100, CardMask().set(BaseCard::FIRE), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_DRAGON_STONE, new calculators::Percent(-2), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_FALCON_STONE] = new EffectsAbility(ability::SHARPENING_FALCON_STONE, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_FALCON_STONE, 100, CardMask().set(BaseCard::AIR), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_FALCON_STONE, new calculators::Percent(-2), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_GRINDSTONE] = new EffectsAbility(ability::SHARPENING_GRINDSTONE, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::SHARPENING_GRINDSTONE, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_GRINDSTONE, new calculators::Percent(2), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_WAR_FIRE] = new EffectsAbility(ability::SHARPENING_WAR_FIRE, AbilityTargeting::self, {
		new OnAttackEffect(ids.next(), ability::SHARPENING_WAR_FIRE, 1, CardMask(), {
			new NoResponseEffect(ids.next(), ability::SHARPENING_WAR_FIRE, BattleEffect::policy_turn(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_GNOME_COMPAS] = new EffectsAbility(ability::SHARPENING_GNOME_COMPAS, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_GNOME_COMPAS, 100, CardMask().set(BaseCard::EARTH), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_GNOME_COMPAS, new calculators::Percent(-2), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_RUNE_STONE] = new EffectsAbility(ability::SHARPENING_RUNE_STONE, AbilityTargeting::self, {
		new StatsEffectsApplier(ids.next(), ability::SHARPENING_RUNE_STONE, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::SHARPENING_RUNE_STONE, new calculators::Percent(2), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_NORTHEN_STAR] = new EffectsAbility(ability::SHARPENING_NORTHEN_STAR, AbilityTargeting::self, {
		new OnReceivedAttackEfect(ids.next(), ability::SHARPENING_NORTHEN_STAR, 100, CardMask().set(BaseCard::WATER), {
			new ExtraDamageEffect(ids.next(), ability::SHARPENING_NORTHEN_STAR, new calculators::Percent(-2), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::SHARPENING_WITCHING_POWDER] = new EffectsAbility(ability::SHARPENING_WITCHING_POWDER, AbilityTargeting::self_row_targets, {
		new StatsEffectsApplier(ids.next(), ability::SHARPENING_WITCHING_POWDER, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::SHARPENING_WITCHING_POWDER, 2, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});

	/// Boosters
	this->abilities[ability::BOOST_MAGIC_RESISTANCE_POTION] = new EffectsAbility(ability::BOOST_MAGIC_RESISTANCE_POTION, AbilityTargeting::all_enemy_targets_with_summoner, {
		new StatsEffectsApplier(ids.next(), ability::BOOST_MAGIC_RESISTANCE_POTION, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::BOOST_MAGIC_RESISTANCE_POTION, 2, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->abilities[ability::BOOST_SCROLL_MAGIC_RESISTANCE] = new EffectsAbility(ability::BOOST_SCROLL_MAGIC_RESISTANCE, AbilityTargeting::all_enemy_targets_with_summoner, {
		new StatsEffectsApplier(ids.next(), ability::BOOST_SCROLL_MAGIC_RESISTANCE, CardMask(), {
			new MagicResistanceEffect(ids.next(), ability::BOOST_SCROLL_MAGIC_RESISTANCE, 2, BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
}

const Range<ability::Type> AbilitiesParams::CATEGORY_RANGE[ability::MAX_CATEGORY] =
{
	{ability::CARD_STONE_WALL, ability::CARD_BATTLE_JOY},				// CARD
	{ability::SPELL_MAGIC_ARROW, ability::SPELL_MAGIC_BASICS},			// SPELL
	{ability::COMBO_FLOW, ability::COMBO_DEAD_LEGION_4_MORE},			// COMBO
	{ability::LOCATION_POISONOUS_WASTELAND, ability::LOCATION_EDUCATION_BATTLE},	// LOCATION
	{ability::EQUIPMENT_WORN_SHOULDERS, ability::EQUIPMENT_AN_ANCIENT_ENEMY},	// EQUIPMENT
	{ability::SHARPENING_CHROARCHINE_LIITANY, ability::SHARPENING_WITCHING_POWDER},	// SHARPENING
	{ability::QUEST_ROGOLD_NECROMANCER, ability::QUEST_ORIGINAL_SPIRIT},		// QUEST
	{ability::TROPHIES_ORCS_FLAG, ability::TROPHIES_DHELL_ALTAIR},			// TROPHIES
};

AbilitiesParams::AbilitiesParams(IDGenerator &ids)
{
	this->init(ids);
}

AbilitiesParams::~AbilitiesParams()
{
	for (auto &pair : this->abilities)
		delete pair.second;
}

const Ability* AbilitiesParams::get(ability::Type type) const
{
	auto found = this->abilities.find(type);
	if (found == this->abilities.cend())
	{
		logger()->debug("Invalid ability %u requested", enum_unwrap(type));
		throw Exception("Invalid ability requested");
	}

	return found->second;
}

PassiveAbilities::passives_t AbilitiesParams::get(const ability::abilities_t &types) const
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
		catch (Exception &) {}
	}
	return result;
}

ability::Category AbilitiesParams::get_category(ability::Type ability) const
{
	for (uint8_t category = 0; category < ability::MAX_CATEGORY; ++category)
	{
		if (CATEGORY_RANGE[category].in(ability))
			return static_cast<ability::Category>(category);
	}

	return ability::MAX_CATEGORY;
}

Range<ability::Type> AbilitiesParams::get_range(ability::Category category) const
{
	return CATEGORY_RANGE[category];
}