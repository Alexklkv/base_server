#include "ComboParams.h"

#include "CardMask.h"
#include "EffectCombo.h"
#include "Exception.h"
#include "Log.h"

#include "ability/effects/DamageAllEffect.h"
#include "ability/effects/EagernessEffect.h"
#include "ability/effects/ExtraCriticalEffect.h"
#include "ability/effects/ExtraDamageEffect.h"
#include "ability/effects/ExtraHealthEffect.h"
#include "ability/effects/ForbidMoveEffect.h"
#include "ability/effects/HealAllEffect.h"
#include "ability/effects/MagicResistanceEffect.h"
#include "ability/effects/NoResponseEffect.h"
#include "ability/effects/OnAttackEffect.h"
#include "ability/effects/OnReceivedAttackEfect.h"
#include "ability/effects/PoisoningEffect.h"
#include "ability/effects/SorcererEffect.h"
#include "ability/effects/StatsEffectsApplier.h"

#include "misc.h"

ComboParams::ComboParams(IDGenerator &ids)
{
	this->init(ids);
}

ComboParams::~ComboParams()
{
	for (combos_t::value_type &pair : this->combos)
		delete pair.second;
	this->combos.clear();
}

void ComboParams::init(IDGenerator &ids)
{
	this->combos[ability::COMBO_FLOW] = new EffectCombo(ability::COMBO_FLOW, any_row(CardMask().set(BaseCard::WATER).set(BaseCard::DESTROYER), 3),
		{}, {
		new OnAttackEffect(ids.next(), ability::COMBO_FLOW, 100, CardMask(), {
			new NoResponseEffect(ids.next(), ability::COMBO_FLOW, BattleEffect::policy_actions(1))
		}, BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_FIREWALL] = new EffectCombo(ability::COMBO_FIREWALL, front_row(CardMask().set(BaseCard::FIRE).set(BaseCard::GUARD), 3),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_FIREWALL, new calculators::Percent(20), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_CELESTIAL_FIRE] = new EffectCombo(ability::COMBO_CELESTIAL_FIRE, any_row(CardMask().set(BaseCard::FIRE).set(BaseCard::MELEE), 3),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_CELESTIAL_FIRE, new calculators::Percent(30), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_DISCHARGE] = new EffectCombo(ability::COMBO_DISCHARGE, front_row(CardMask().set(BaseCard::AIR).set(BaseCard::DESTROYER), 3),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_DISCHARGE, new calculators::Percent(20), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_HEAVEN_COVER] = new EffectCombo(ability::COMBO_HEAVEN_COVER, back_row(CardMask().set(BaseCard::AIR).set(BaseCard::SUPPORT), 3),
		{}, {
		new MagicResistanceEffect(ids.next(), ability::COMBO_HEAVEN_COVER, 100, BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_EARTHWORKS] = new EffectCombo(ability::COMBO_EARTHWORKS, front_row(CardMask().set(BaseCard::EARTH).set(BaseCard::GUARD), 3),
		{}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_EARTHWORKS, new calculators::Percent(30), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_EARTHQUAKE] = new EffectCombo(ability::COMBO_EARTHQUAKE, any_row(CardMask().set(BaseCard::EARTH).set(BaseCard::SUPPORT), 3),
		{}, {
		new DamageAllEffect(ids.next(), ability::COMBO_EARTHQUAKE, CardMask(true).set(BaseCard::FLYING), new calculators::Percent(10), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_WATER_2] = new EffectCombo(ability::COMBO_WATER_2, anywhere(CardMask().set(BaseCard::WATER), {2}),
		{}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_WATER_2, new calculators::Percent(10), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_WATER_3] = new EffectCombo(ability::COMBO_WATER_3, anywhere(CardMask().set(BaseCard::WATER), {3}),
		{ability::COMBO_WATER_2}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_WATER_3, new calculators::Percent(15), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_WATER_4] = new EffectCombo(ability::COMBO_WATER_4, anywhere(CardMask().set(BaseCard::WATER), {4}),
		{ability::COMBO_WATER_2, ability::COMBO_WATER_3}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_WATER_4, new calculators::Percent(20), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_WATER_5] = new EffectCombo(ability::COMBO_WATER_5, anywhere_from(CardMask().set(BaseCard::WATER), 5),
		{ability::COMBO_WATER_2, ability::COMBO_WATER_3, ability::COMBO_WATER_4}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_WATER_5, new calculators::Percent(25), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_FIRE_2] = new EffectCombo(ability::COMBO_FIRE_2, anywhere(CardMask().set(BaseCard::FIRE), {2}),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_FIRE_2, new calculators::Percent(10), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_FIRE_3] = new EffectCombo(ability::COMBO_FIRE_3, anywhere(CardMask().set(BaseCard::FIRE), {3}),
		{ability::COMBO_FIRE_2}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_FIRE_3, new calculators::Percent(15), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_FIRE_4] = new EffectCombo(ability::COMBO_FIRE_4, anywhere(CardMask().set(BaseCard::FIRE), {4}),
		{ability::COMBO_FIRE_2, ability::COMBO_FIRE_3}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_FIRE_4, new calculators::Percent(20), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_FIRE_5] = new EffectCombo(ability::COMBO_FIRE_5, anywhere_from(CardMask().set(BaseCard::FIRE), 5),
		{ability::COMBO_FIRE_2, ability::COMBO_FIRE_3, ability::COMBO_FIRE_4}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_FIRE_5, new calculators::Percent(25), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_EARTH_2] = new EffectCombo(ability::COMBO_EARTH_2, anywhere(CardMask().set(BaseCard::EARTH), {2}),
		{}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_EARTH_2, new calculators::Percent(10), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_EARTH_3] = new EffectCombo(ability::COMBO_EARTH_3, anywhere(CardMask().set(BaseCard::EARTH), {3}),
		{ability::COMBO_EARTH_2}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_EARTH_3, new calculators::Percent(15), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_EARTH_4] = new EffectCombo(ability::COMBO_EARTH_4, anywhere(CardMask().set(BaseCard::EARTH), {4}),
		{ability::COMBO_EARTH_2, ability::COMBO_EARTH_3}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_EARTH_4, new calculators::Percent(20), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_EARTH_5] = new EffectCombo(ability::COMBO_EARTH_5, anywhere_from(CardMask().set(BaseCard::EARTH), 5),
		{ability::COMBO_EARTH_2, ability::COMBO_EARTH_3, ability::COMBO_EARTH_4}, {
		new ExtraHealthEffect(ids.next(), ability::COMBO_EARTH_5, new calculators::Percent(25), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_AIR_2] = new EffectCombo(ability::COMBO_AIR_2, anywhere(CardMask().set(BaseCard::AIR), {2}),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_AIR_2, new calculators::Percent(10), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_AIR_3] = new EffectCombo(ability::COMBO_AIR_3, anywhere(CardMask().set(BaseCard::AIR), {3}),
		{ability::COMBO_AIR_2}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_AIR_3, new calculators::Percent(15), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_AIR_4] = new EffectCombo(ability::COMBO_AIR_4, anywhere(CardMask().set(BaseCard::AIR), {4}),
		{ability::COMBO_AIR_2, ability::COMBO_AIR_3}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_AIR_4, new calculators::Percent(20), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_AIR_5] = new EffectCombo(ability::COMBO_AIR_5, anywhere_from(CardMask().set(BaseCard::AIR), 5),
		{ability::COMBO_AIR_2, ability::COMBO_AIR_3, ability::COMBO_AIR_4}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_AIR_5, new calculators::Percent(25), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_NORTH_2_3] = new EffectCombo(ability::COMBO_NORTH_2_3, anywhere(CardMask().set(BaseCard::NORTH), {2, 3}),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_NORTH_2_3, new calculators::Percent(10), BattleEffect::policy_combo()),
		new ExtraHealthEffect(ids.next(), ability::COMBO_NORTH_2_3, new calculators::Percent(10), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_NORTH_4_MORE] = new EffectCombo(ability::COMBO_NORTH_4_MORE, anywhere_from(CardMask().set(BaseCard::NORTH), 4),
		{ability::COMBO_NORTH_2_3}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_NORTH_4_MORE, new calculators::Percent(15), BattleEffect::policy_combo()),
			new ExtraHealthEffect(ids.next(), ability::COMBO_NORTH_4_MORE, new calculators::Percent(25), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_COMMUNE_2_3] = new EffectCombo(ability::COMBO_COMMUNE_2_3, anywhere(CardMask().set(BaseCard::COMMUNE), {2, 3}),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_COMMUNE_2_3, new calculators::Percent(10), BattleEffect::policy_combo()),
		new ExtraHealthEffect(ids.next(), ability::COMBO_COMMUNE_2_3, new calculators::Percent(10), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_COMMUNE_4_MORE] = new EffectCombo(ability::COMBO_COMMUNE_4_MORE, anywhere_from(CardMask().set(BaseCard::COMMUNE), 4),
		{ability::COMBO_COMMUNE_2_3}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_COMMUNE_4_MORE, new calculators::Percent(25), BattleEffect::policy_combo()),
			new ExtraHealthEffect(ids.next(), ability::COMBO_COMMUNE_4_MORE, new calculators::Percent(15), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_FRATERNITY_2_3] = new EffectCombo(ability::COMBO_FRATERNITY_2_3, anywhere(CardMask().set(BaseCard::FRATERNITY), {2, 3}),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_FRATERNITY_2_3, new calculators::Percent(10), BattleEffect::policy_combo()),
		new ExtraHealthEffect(ids.next(), ability::COMBO_FRATERNITY_2_3, new calculators::Percent(10), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_FRATERNITY_4_MORE] = new EffectCombo(ability::COMBO_FRATERNITY_4_MORE, anywhere_from(CardMask().set(BaseCard::FRATERNITY), 4),
		{ability::COMBO_FRATERNITY_2_3}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_FRATERNITY_4_MORE, new calculators::Percent(15), BattleEffect::policy_combo()),
			new ExtraHealthEffect(ids.next(), ability::COMBO_FRATERNITY_4_MORE, new calculators::Percent(25), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_DEAD_LEGION_2_3] = new EffectCombo(ability::COMBO_DEAD_LEGION_2_3, anywhere(CardMask().set(BaseCard::DEAD_LEGION), {2, 3}),
		{}, {
		new ExtraDamageEffect(ids.next(), ability::COMBO_DEAD_LEGION_2_3, new calculators::Percent(10), BattleEffect::policy_combo()),
		new ExtraHealthEffect(ids.next(), ability::COMBO_DEAD_LEGION_2_3, new calculators::Percent(10), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_DEAD_LEGION_4_MORE] = new EffectCombo(ability::COMBO_DEAD_LEGION_4_MORE, anywhere_from(CardMask().set(BaseCard::DEAD_LEGION), 4),
		{ability::COMBO_DEAD_LEGION_2_3}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_DEAD_LEGION_4_MORE, new calculators::Percent(15), BattleEffect::policy_combo()),
			new ExtraHealthEffect(ids.next(), ability::COMBO_DEAD_LEGION_4_MORE, new calculators::Percent(25), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_PRAYS_TO_CHROARCHINE] = new EffectCombo(ability::COMBO_PRAYS_TO_CHROARCHINE, any_row(CardMask().set(BaseCard::NORTH).set(BaseCard::SUPPORT), 3),
		{}, {
		new HealAllEffect(ids.next(), ability::COMBO_PRAYS_TO_CHROARCHINE, CardMask(), new calculators::Percent(30), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_ICE_WALL] = new EffectCombo(ability::COMBO_ICE_WALL, front_row(CardMask().set(BaseCard::GUARD).set(BaseCard::WATER), 3),
		{}, {
		new OnReceivedAttackEfect(ids.next(), ability::COMBO_ICE_WALL, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::COMBO_ICE_WALL, new calculators::Percent(-20), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->combos[ability::COMBO_LINE_UP] = new EffectCombo(ability::COMBO_LINE_UP, any_row(CardMask().set(BaseCard::NORTH), 4),
		{}, {
		new OnReceivedAttackEfect(ids.next(), ability::COMBO_LINE_UP, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::COMBO_LINE_UP, new calculators::Percent(-30), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_infinite())
	});
	this->combos[ability::COMBO_HORDE] = new EffectCombo(ability::COMBO_HORDE, anywhere_from(CardMask().set(BaseCard::COMMUNE), 4),
		{}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_HORDE, new calculators::Percent(15), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_RAID] = new EffectCombo(ability::COMBO_RAID, front_row(CardMask().set(BaseCard::COMMUNE).set(BaseCard::DESTROYER), 3),
		{}, {
			new EagernessEffect(ids.next(), ability::COMBO_RAID, BattleEffect::policy_placement()),
			new OnReceivedAttackEfect(ids.next(), ability::COMBO_RAID, 20, CardMask(), {
				new ExtraDamageEffect(ids.next(), ability::COMBO_RAID, new calculators::Percent(-100), BattleEffect::policy_actions(1), true)
			}, BattleEffect::policy_infinite())
	});
	this->combos[ability::COMBO_ARMY_OF_DARKNESS] = new EffectCombo(ability::COMBO_ARMY_OF_DARKNESS, anywhere_from(CardMask().set(BaseCard::DEAD_LEGION), 4),
		{}, {
			new OnReceivedAttackEfect(ids.next(), ability::COMBO_ARMY_OF_DARKNESS, 30, CardMask(), {
				new ExtraDamageEffect(ids.next(), ability::COMBO_ARMY_OF_DARKNESS, new calculators::Percent(-100), BattleEffect::policy_actions(1), true)
			}, BattleEffect::policy_infinite())
	});
	this->combos[ability::COMBO_DEAD_RISING] = new EffectCombo(ability::COMBO_DEAD_RISING, front_row(CardMask().set(BaseCard::DEAD_LEGION).set(BaseCard::DESTROYER), 3),
		{}, {
			new EagernessEffect(ids.next(), ability::COMBO_DEAD_RISING, BattleEffect::policy_placement()),
			new ExtraDamageEffect(ids.next(), ability::COMBO_DEAD_RISING, new calculators::Percent(15), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_DEATH_MAGIC] = new EffectCombo(ability::COMBO_DEATH_MAGIC, back_row(CardMask().set(BaseCard::DEAD_LEGION).set(BaseCard::SUPPORT), 3),
		{}, {
			new SorcererEffect(ids.next(), ability::COMBO_DEATH_MAGIC, new calculators::Percent(10), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_PEOPLE_ALLIANCE] = new EffectCombo(ability::COMBO_PEOPLE_ALLIANCE, anywhere_from(CardMask().set(BaseCard::NORTH), 4),
		{}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_PEOPLE_ALLIANCE, new calculators::Percent(15), BattleEffect::policy_combo()),
			new ExtraHealthEffect(ids.next(), ability::COMBO_PEOPLE_ALLIANCE, new calculators::Percent(15), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_FLOTILLA] = new EffectCombo(ability::COMBO_FLOTILLA, anywhere_from(CardMask().set(BaseCard::WATER), 4),
		{}, {
			new ExtraHealthEffect(ids.next(), ability::COMBO_FLOTILLA, new calculators::Percent(20), BattleEffect::policy_combo())
	});
	this->combos[ability::COMBO_VORTEX] = new EffectCombo(ability::COMBO_VORTEX, reverse_wedge(CardMask().set(BaseCard::WATER), 3),
		{}, {
			new StatsEffectsApplier(ids.next(), ability::COMBO_VORTEX, CardMask().set(BaseCard::WATER), {
				new ExtraCriticalEffect(ids.next(), ability::COMBO_VORTEX, new calculators::Value(10), BattleEffect::policy_combo())
			}, BattleEffect::policy_infinite()),
	});
	this->combos[ability::COMBO_FUNNEL] = new EffectCombo(ability::COMBO_FUNNEL, reverse_wedge(CardMask().set(BaseCard::AIR), 3),
		{}, {
			new OnReceivedAttackEfect(ids.next(), ability::COMBO_FUNNEL, 100, CardMask(), {
				new ExtraDamageEffect(ids.next(), ability::COMBO_FUNNEL, new calculators::Percent(-30), BattleEffect::policy_actions(1), true)
			}, BattleEffect::policy_infinite())
	});
	this->combos[ability::COMBO_ROCKFALL] = new EffectCombo(ability::COMBO_ROCKFALL, reverse_wedge(CardMask().set(BaseCard::EARTH), 3),
		{}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_ROCKFALL, new calculators::Percent(20), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_AMBUSH] = new EffectCombo(ability::COMBO_AMBUSH, reverse_wedge(CardMask().set(BaseCard::FRATERNITY), 3),
		{}, {
			new ExtraDamageEffect(ids.next(), ability::COMBO_AMBUSH, new calculators::Percent(20), BattleEffect::policy_combo()),
	});
	this->combos[ability::COMBO_SPIDER_JAWS] = new EffectCombo(ability::COMBO_SPIDER_JAWS, reverse_wedge(CardMask().set(BaseCard::DEAD_LEGION), 3),
		{}, {
			new OnAttackEffect(ids.next(), ability::COMBO_SPIDER_JAWS, 100, CardMask(), {
				new PoisoningEffect(ids.next(), ability::COMBO_SPIDER_JAWS, new calculators::Percent(10), BattleEffect::policy_combo())
			}, BattleEffect::policy_infinite())
	});
	this->combos[ability::COMBO_STONE_SKIN] = new EffectCombo(ability::COMBO_STONE_SKIN, any_row(CardMask().set(BaseCard::EARTH), 5),
		{}, {
			new OnReceivedAttackEfect(ids.next(), ability::COMBO_STONE_SKIN, 60, CardMask().set(BaseCard::DISTANT), {
				new ExtraDamageEffect(ids.next(), ability::COMBO_RAID, new calculators::Percent(-100), BattleEffect::policy_actions(1), true)
			}, BattleEffect::policy_infinite()),
			new OnReceivedAttackEfect(ids.next(), ability::COMBO_STONE_SKIN, 20, CardMask().set(BaseCard::MELEE), {
				new ExtraDamageEffect(ids.next(), ability::COMBO_RAID, new calculators::Percent(-100), BattleEffect::policy_actions(1), true)
			}, BattleEffect::policy_infinite())
	});
}

void ComboParams::foreach(const std::function<void(const Combo*)> &callback) const
{
	for (const combos_t::value_type &pair : this->combos)
		callback(pair.second);
}

const Combo* ComboParams::get(ability::Type type) const
{
	auto found = this->combos.find(type);
	if (found == this->combos.cend())
	{
		logger()->warning("Invalid combo %u requested in ComboParams", enum_unwrap(type));
		throw Exception("Invalid combo requested in ComboParams");
	}
	return found->second;
}