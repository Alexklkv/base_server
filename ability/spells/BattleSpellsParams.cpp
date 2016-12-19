#include "BattleSpellsParams.h"

#include "AstralPortalSpell.h"
#include "AwakeningSpell.h"
#include "ClearEffectsSpell.h"
#include "DamageSpell.h"
#include "DaturaSpell.h"
#include "DarkRitualSpell.h"
#include "DivinePunishmentSpell.h"
#include "EffectsSpell.h"
#include "Exception.h"
#include "ExileSpell.h"
#include "HealSpell.h"
#include "LegendsServer.h"
#include "LibraryMessSpell.h"
#include "Log.h"
#include "ManaSourceSpell.h"
#include "RetrievalSpell.h"
#include "ShieldSpell.h"
#include "Spells.h"

#include "ability/abilities/Ability.h"
#include "ability/abilities/AbilitiesParams.h"
#include "ability/effects/AvoidDamageEffect.h"
#include "ability/effects/BlockAttackEffect.h"
#include "ability/effects/BlockCastEffect.h"
#include "ability/effects/SpellDamageEffect.h"
#include "ability/effects/DrainingEffect.h"
#include "ability/effects/ExtraCriticalEffect.h"
#include "ability/effects/ExtraDamageEffect.h"
#include "ability/effects/ExtraHealthEffect.h"
#include "ability/effects/ExtraReceivedDamageEffect.h"
#include "ability/effects/OnAttackEffect.h"
#include "ability/effects/OnReceivedAttackEfect.h"
#include "ability/effects/PoisoningEffect.h"
#include "ability/effects/SleepingEffect.h"
#include "ability/effects/StatsEffectsApplier.h"
#include "ability/effects/WarFogEffect.h"

#include "misc.h"
#include "params.h"

BattleSpellsParams::BattleSpellsParams(IDGenerator &ids)
{
	this->init(ids);
}

BattleSpellsParams::~BattleSpellsParams()
{
	for (auto &pair : this->spells)
		delete pair.second;
}

void BattleSpellsParams::init(IDGenerator &ids)
{
	this->spells[ability::SPELL_MAGIC_ARROW] = new DamageSpell(ability::SPELL_MAGIC_ARROW, 1, 2, 1, new calculators::Value(30), self());
	this->spells[ability::SPELL_LESSER_HEALING] = new HealSpell(ability::SPELL_LESSER_HEALING, 3, 2, 1, new calculators::Value(30), self());
	this->spells[ability::SPELL_STONE_SKIN] = new EffectsSpell(ability::SPELL_STONE_SKIN, ability::OTHER_POSITIVE, 5, 2, 1, self(), {
		new AvoidDamageEffect(ids.next(), ability::SPELL_STONE_SKIN, 10, BattleEffect::policy_turn(2))
	});
	this->spells[ability::SPELL_AWAIKENING] = new AwakeningSpell(ability::SPELL_AWAIKENING, 5, 2, 1);
	this->spells[ability::SPELL_CHARMED_WEAPON] = new EffectsSpell(ability::SPELL_CHARMED_WEAPON, ability::OTHER_POSITIVE, 5, 2, 2, self(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_CHARMED_WEAPON, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_CHARMED_WEAPON, new::calculators::Value(50), BattleEffect::policy_infinite())
		}, BattleEffect::policy_infinite())
	});
	this->spells[ability::SPELL_PURIFICATION] = new ClearEffectsSpell(ability::SPELL_PURIFICATION, 7, 2, 1, ClearEffectsSpell::EffectType::NEGATIVE);
	this->spells[ability::SPELL_EXILE] = new ExileSpell(ability::SPELL_EXILE, 7, 3, 1, self());
	this->spells[ability::SPELL_HEALING_TOUCH] = new HealSpell(ability::SPELL_HEALING_TOUCH, 9, 2, 1, new calculators::Percent(20), combine({self(), n_neighbours(2)}));
	this->spells[ability::SPELL_SLEEP] = new EffectsSpell(ability::SPELL_SLEEP, ability::OTHER_NEGATIVE, 9, 2, 1, self(), {
		new SleepingEffect(ids.next(), ability::SPELL_SLEEP, BattleEffect::policy_turn(2))
	});
	this->spells[ability::SPELL_MANA_SOURCE] = new ManaSourceSpell(ability::SPELL_MANA_SOURCE, 9, 3, 0, 1, new calculators::Percent(10));
	this->spells[ability::SPELL_LIGHTING] = new DamageSpell(ability::SPELL_LIGHTING, 11, 2, 2, new calculators::Percent(20), combine({self(), n_neighbours(1)}));
	this->spells[ability::SPELL_DRAINING] = new EffectsSpell(ability::SPELL_DRAINING, ability::OTHER_NEGATIVE, 11, 3, 2, self(), {
		new DrainingEffect(ids.next(), ability::SPELL_DRAINING, -2, BattleEffect::policy_turn(2))
	});
	this->spells[ability::SPELL_CAMOUFLAGE] = new EffectsSpell(ability::SPELL_CAMOUFLAGE, ability::OTHER_POSITIVE, 13, 3, 2, self(), {
		new OnReceivedAttackEfect(ids.next(), ability::SPELL_CAMOUFLAGE, 50, CardMask().set(BaseCard::DISTANT), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_CAMOUFLAGE, new calculators::Percent(-100), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_actions(2))
	});
	this->spells[ability::SPELL_MAGIC_SHIELD] = new ShieldSpell(ids.next(), ability::SPELL_MAGIC_SHIELD, 5, 2, 1, 50, self());
	this->spells[ability::SPELL_CURSE] = new EffectsSpell(ability::SPELL_CURSE, ability::OTHER_NEGATIVE, 13, 3, 2, self(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_CURSE, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_CURSE, new calculators::Percent(-20), BattleEffect::policy_infinite()),
			new ExtraCriticalEffect(ids.next(), ability::SPELL_CURSE, new calculators::Percent(-100), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
	this->spells[ability::SPELL_MENTAL_PUNCH] = new DamageSpell(ability::SPELL_MENTAL_PUNCH, 13, 3, 2, new calculators::Percent(10), self());
	this->spells[ability::SPELL_POISONED_ARROW] = new EffectsSpell(ability::SPELL_POISONED_ARROW, ability::OTHER_NEGATIVE, 7, 2, 2, self(), {
		new PoisoningEffect(ids.next(), ability::SPELL_POISONED_ARROW, new calculators::Percent(10), BattleEffect::policy_infinite())
	});
	this->spells[ability::SPELL_HEALING_PRAY] = new HealSpell(ability::SPELL_HEALING_PRAY, 15, 2, 1, new calculators::Percent(30), combine({self(), n_neighbours(1)}));
	this->spells[ability::SPELL_MAGIC_SPHERE] = new DamageSpell(ability::SPELL_MAGIC_SPHERE, 15, 2, 2, new calculators::Value(150), self());
	this->spells[ability::SPELL_AVERAGE_HEALING] = new HealSpell(ability::SPELL_AVERAGE_HEALING, 15, 2, 2, new calculators::Value(130), self());
	this->spells[ability::SPELL_RESTORATION] = new HealSpell(ability::SPELL_RESTORATION, 18, 2, 2, new calculators::Percent(15), self());
	this->spells[ability::SPELL_PACIFICATION] = new EffectsSpell(ability::SPELL_PACIFICATION, ability::OTHER_NEGATIVE, 18, 2, 2, self(), {
		new BlockAttackEffect(ids.next(), ability::SPELL_PACIFICATION, BattleEffect::policy_turn(6))
	});
	this->spells[ability::SPELL_MAGIC_STORM] = new DamageSpell(ability::SPELL_MAGIC_STORM, 21, 3, 3, new calculators::Value(150), n_neighbours(3));
	this->spells[ability::SPELL_FURY_RUNES] = new EffectsSpell(ability::SPELL_FURY_RUNES, ability::OTHER_POSITIVE, 21, 2, 3, self(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_FURY_RUNES, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_FURY_RUNES, new calculators::Value(300), BattleEffect::policy_infinite()),
		}, BattleEffect::policy_infinite())
	});
	this->spells[ability::SPELL_RETRIEVAL] = new RetrievalSpell(ability::SPELL_RETRIEVAL, 21, 5, 4);
	this->spells[ability::SPELL_WAR_SONGS] = new EffectsSpell(ability::SPELL_WAR_SONGS, ability::OTHER_POSITIVE, 24, 4, 3, all_cards(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_WAR_SONGS, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_WAR_SONGS, new calculators::Percent(30), BattleEffect::policy_turn(3)),
		}, BattleEffect::policy_turn(3))
	});
	this->spells[ability::SPELL_ASTRAL_PORTAL] = new AstralPortalSpell(ability::SPELL_ASTRAL_PORTAL, 24, 3, 3);
	this->spells[ability::SPELL_MASS_HEALING] = new HealSpell(ability::SPELL_MASS_HEALING, 27, 3, 2, new calculators::Percent(30), all_cards());
	this->spells[ability::SPELL_GUARDIAN_HELP] = new EffectsSpell(ability::SPELL_GUARDIAN_HELP, ability::OTHER_POSITIVE, 27, 3, 2, self(), {
		new OnReceivedAttackEfect(ids.next(), ability::SPELL_GUARDIAN_HELP, 100, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_GUARDIAN_HELP, new calculators::Percent(-100), BattleEffect::policy_actions(1))
		}, BattleEffect::policy_actions(1))
	});
	this->spells[ability::SPELL_MARVELOUS_RECOVERY] = new HealSpell(ability::SPELL_MARVELOUS_RECOVERY, 27, 3, 3, new calculators::Percent(40), self());
	this->spells[ability::SPELL_MENTAL_TORTURE] = new EffectsSpell(ability::SPELL_MENTAL_TORTURE, ability::OTHER_NEGATIVE, 18, 2, 2, self(), {
		new SpellDamageEffect(ids.next(), ability::SPELL_MENTAL_TORTURE, CardMask(), new calculators::Percent(20), BattleEffect::policy_actions(1)),
		new DrainingEffect(ids.next(), ability::SPELL_MENTAL_TORTURE, -2, BattleEffect::policy_turn(2))
	});
	this->spells[ability::SPELL_INCINERATION] = new DamageSpell(ability::SPELL_INCINERATION, 30, 4, 4, new calculators::Value(1000), self());
	this->spells[ability::SPELL_GREAT_HEALING] = new HealSpell(ability::SPELL_GREAT_HEALING, 30, 2, 2, new calculators::Value(200), self());
	this->spells[ability::SPELL_METEOR_RAIN] = new DamageSpell(ability::SPELL_METEOR_RAIN, 33, 3, 4, new calculators::Value(400), n_neighbours(4));
	this->spells[ability::SPELL_EPIDEMY] = new EffectsSpell(ability::SPELL_EPIDEMY, ability::OTHER_NEGATIVE, 33, 8, 6, all_cards(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_EPIDEMY, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_EPIDEMY, new calculators::Percent(-60), BattleEffect::policy_infinite())
		}, BattleEffect::policy_turn(5))
	});
	this->spells[ability::SPELL_DIVINE_PUNUSHMENT] = new DivinePunishmentSpell(ability::SPELL_DIVINE_PUNUSHMENT, 35, 10, 6, 48);
	this->spells[ability::SPELL_DATURA] = new DaturaSpell(ability::SPELL_DATURA, 5, 4, 2);
	this->spells[ability::SPELL_WAR_FOG] = new EffectsSpell(ability::SPELL_WAR_FOG, ability::OTHER_NEGATIVE, 7, 4, 3, self(), {
		new WarFogEffect(ids.next(), ability::SPELL_WAR_FOG, BattleEffect::policy_turn(2))
	});
	this->spells[ability::SPELL_ASTRAL_STORM] = new EffectsSpell(ability::SPELL_ASTRAL_STORM, ability::OTHER_NEGATIVE, 9, 4, 5, all_cards(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_ASTRAL_STORM, CardMask(), {
			new ExtraHealthEffect(ids.next(), ability::SPELL_ASTRAL_STORM, new calculators::Percent(-20), BattleEffect::policy_turn(4))
		}, BattleEffect::policy_turn(4))
	});
	this->spells[ability::SPELL_LIBRARY_MESS] = new LibraryMessSpell(ability::SPELL_LIBRARY_MESS, 11, 2, 2);
	this->spells[ability::SPELL_MAGIC_BASICS] = new EffectsSpell(ability::SPELL_MAGIC_BASICS, ability::OTHER_POSITIVE, 1, 1, 1, self(), {
		new StatsEffectsApplier(ids.next(), ability::SPELL_MAGIC_BASICS, CardMask(), {
			new ExtraDamageEffect(ids.next(), ability::SPELL_MAGIC_BASICS, new calculators::Percent(20), BattleEffect::policy_turn(2)),
			new ExtraHealthEffect(ids.next(), ability::SPELL_MAGIC_BASICS, new calculators::Percent(20), BattleEffect::policy_turn(2))
		}, BattleEffect::policy_turn(2))
	});
	this->spells[ability::SPELL_DARK_RITUAL] = new DarkRitualSpell(ability::SPELL_DARK_RITUAL, 30, 3, 4);
	this->spells[ability::SPELL_DEAFNESS] = new EffectsSpell(ability::SPELL_DEAFNESS, ability::OTHER_NEGATIVE, 18, 3, 3, self(), {
		new BlockCastEffect(ids.next(), ability::SPELL_DEAFNESS, BattleEffect::policy_turn(2))
	});
}

const Spell* BattleSpellsParams::get(ability::Type type) const
{
	spells_t::const_iterator found = this->spells.find(type);
	if (found == this->spells.cend())
	{
		logger()->debug("Invalid spell %u requested", enum_unwrap(type));
		throw Exception("Invalid spell requested");
	}

	return found->second;
}

bool BattleSpellsParams::has_spell(ability::Type type) const
{
	return (this->spells.find(type) != this->spells.cend());
}

ability::abilities_t BattleSpellsParams::get_available_spells(uint8_t level) const
{
	ability::abilities_t available_spells;

	auto spells_range = abilities_params()->get_range(ability::SPELL);
	for (ability::Type spell_id = spells_range.min; spell_id < spells_range.max; spell_id = static_cast<ability::Type>(spell_id + 1))
	{
		const Spell* spell;

		try
		{ // TODO: Remove when all spells are implemented.
			spell = this->get(spell_id);
		}
		catch (Exception &)
		{
			continue;
		}

		if (spell->level <= level)
			available_spells.insert(spell_id);
	}

	return available_spells;
}

ability::abilities_t BattleSpellsParams::get_available_bot_spells(uint8_t level) const
{
	ability::abilities_t available_spells;

	for (auto &iter : pve::BOT_SPELLS)
	{
		if (iter.max_level < level)
			continue;

		for (auto spell_id : iter.spells)
		{
			auto spell = this->get(spell_id);

			if (spell->level <= level)
				available_spells.insert(spell_id);
		}

		break;
	}

	return available_spells;
}

ability::abilities_t BattleSpellsParams::create_bot_spells(uint8_t level) const
{
	ability::abilities_t available_spells = get_available_bot_spells(level);

	ability::abilities_t spells;
	while (!available_spells.empty() && spells.size() < Spells::MAX_ACTIVE_SPELLS)
	{
		auto spell_iter = std::next(available_spells.begin(), Random::uint(available_spells.size()));
		spells.insert(*spell_iter);
		available_spells.erase(spell_iter);
	}

	return spells;
}
