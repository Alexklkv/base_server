#include "NoneContext.h"

#include "ActiveEffects.h"
#include "LegendsServer.h"
#include "Log.h"
#include "PassiveAbilities.h"

#include "misc.h"

const GameObject::Id NoneContext::NONE_ID = {0, 0};

NoneContext::NoneContext():
	active_effects(new ActiveEffects()),
	passive_abilities(new PassiveAbilities())
{}

NoneContext::NoneContext(ability::abilities_t abilities):
	abilities(abilities),
	active_effects(new ActiveEffects()),
	passive_abilities(new PassiveAbilities())
{}

NoneContext::~NoneContext()
{
	delete this->active_effects;
	delete this->passive_abilities;
}

uint16_t NoneContext::heal(uint16_t)
{
	logger()->warning("Healing NoneCombatant");

	return 0;
}

damage_t NoneContext::damage(damage_t, BaseCard::Range)
{
	logger()->warning("Damaging NoneCombatant");

	return 0;
}

void NoneContext::kill()
{
	logger()->warning("Kill NoneCombatant");
}

void NoneContext::update_statistics(CardsStatistics::Type, uint16_t, bool)
{}

void NoneContext::check_quest(const quests::Condition *, uint32_t)
{}

uint16_t NoneContext::get_base_health() const
{
	logger()->warning("Base health request for NoneCombatant");

	return 0;
}

uint16_t NoneContext::get_damage() const
{
	return 0;
}

uint16_t NoneContext::get_health() const
{
	logger()->warning("Health request for NoneCombatant");

	return 0;
}

uint16_t NoneContext::get_injuire_bonus(const IObjectContext *) const
{
	return 0;
}

uint16_t NoneContext::get_injuires() const
{
	logger()->warning("Injures request for NoneCombatant");

	return 0;
}

uint16_t NoneContext::get_max_health() const
{
	logger()->warning("Max health request for NoneCombatant");

	return 0;
}

float NoneContext::get_attack_spell_bonus() const
{
	return 0;
}

float NoneContext::get_critical() const
{
	return 0;
}

float NoneContext::get_dodge() const
{
	return 0;
}

uint8_t NoneContext::get_magic_resistance() const
{
	return 0;
}

uint16_t NoneContext::get_spell_strength_bonus(const uint16_t) const
{
	return 0;
}

float NoneContext::get_critical_strength_bonus() const
{
	return .0f;
}

bool NoneContext::is_dead() const
{
	return false;
}

bool NoneContext::can_cast(bool) const
{
	return true;
}

BaseCard::Fraction NoneContext::get_fraction() const
{
	return BaseCard::NEUTRAL;
}

Effects& NoneContext::get_effects() const
{
	logger()->warning("Returning effects from NoneCombatant");

	return this->effects;
}

ActiveEffects* NoneContext::get_active_effects() const
{
	logger()->warning("Returning active effects from NoneCombatant");

	return this->active_effects;
}

PassiveAbilities* NoneContext::get_passives() const
{
	return this->passive_abilities;
}

ability::abilities_t NoneContext::get_abilities() const
{
	return this->abilities;
}

CardHandler* NoneContext::get_card()
{
	logger()->warning("Returning card from NoneCombatant");

	return nullptr;
}

Summoner* NoneContext::get_summoner()
{
	logger()->warning("Returning summoner from NoneCombatant");

	return nullptr;
}

const CardHandler* NoneContext::get_card() const
{
	logger()->warning("Returning const_card from NoneCombatant");

	return nullptr;
}

const Summoner* NoneContext::get_summoner() const
{
	logger()->warning("Returning const_summoner from NoneCombatant");

	return nullptr;
}

GameObject::Id NoneContext::object_id() const
{
	return NONE_ID;
}

bool NoneContext::change_extra(BaseCard::ExtraType, uint32_t, int16_t, bool)
{
	logger()->warning("Change extra from NoneCombatant");
	return false;
}

int16_t NoneContext::revert_extra(BaseCard::ExtraType, uint32_t)
{
	logger()->warning("Revert extra from NoneCombatant");
	return 0;
}