#include "SummonerContext.h"

#include "BasePlayer.h"
#include "Exception.h"
#include "Log.h"

#include "../Summoner.h"

SummonerContext::SummonerContext(Summoner *summoner):
	summoner(summoner)
{
	if (summoner == nullptr)
		throw Exception("Null summoner supplied to SummonnerContext constructor");
}

SummonerContext::~SummonerContext()
{}

bool SummonerContext::is_summoner() const
{
	return true;
}

uint16_t SummonerContext::heal(uint16_t heal)
{
	return this->summoner->heal(heal);
}

damage_t SummonerContext::damage(damage_t damage, BaseCard::Range type)
{
	return this->summoner->damage(damage, type);
}

void SummonerContext::kill()
{
	this->summoner->kill();
}

void SummonerContext::update_statistics(CardsStatistics::Type, uint16_t, bool)
{}

void SummonerContext::check_quest(const quests::Condition *condition, uint32_t amount)
{
	this->summoner->check_quest(condition, amount);
}

uint16_t SummonerContext::get_base_health() const
{
	return this->summoner->get_base_health();
}

uint16_t SummonerContext::get_damage() const
{
	logger()->warning("Returning summoner damage");

	return 0;
}

uint16_t SummonerContext::get_health() const
{
	return this->summoner->get_health();
}

uint16_t SummonerContext::get_injuire_bonus(const IObjectContext *) const
{
	return 0;
}

uint16_t SummonerContext::get_injuires() const
{
	return this->summoner->get_injuires();
}

uint16_t SummonerContext::get_max_health() const
{
	return this->summoner->get_max_health();
}

float SummonerContext::get_attack_spell_bonus() const
{
	return this->summoner->get_attack_spell_bonus();
}

float SummonerContext::get_critical() const
{
	return 0;
}

float SummonerContext::get_dodge() const
{
	return this->summoner->get_dodge();
}

uint8_t SummonerContext::get_magic_resistance() const
{
	return this->summoner->get_magic_resistance();
}

uint16_t SummonerContext::get_spell_strength_bonus(const uint16_t value) const
{
	return this->summoner->get_spell_bonus(value);
}

float SummonerContext::get_critical_strength_bonus() const
{
	return this->summoner->get_critical_strength_bonus();
}

bool SummonerContext::is_dead() const
{
	return this->summoner->is_dead();
}

bool SummonerContext::can_cast(bool) const
{
	return true;
}

BaseCard::Fraction SummonerContext::get_fraction() const
{
	return this->summoner->fraction;
}

Effects& SummonerContext::get_effects() const
{
	return this->summoner->effects;
}

ActiveEffects* SummonerContext::get_active_effects() const
{
	return this->summoner->active_effects;
}

PassiveAbilities* SummonerContext::get_passives() const
{
	return this->summoner->passive_abilities;
}

ability::abilities_t SummonerContext::get_abilities() const
{
	return this->summoner->get_abilities();
}

CardHandler* SummonerContext::get_card()
{
	return nullptr;
}

Summoner* SummonerContext::get_summoner()
{
	return this->summoner;
}

const CardHandler* SummonerContext::get_card() const
{
	return nullptr;
}

const Summoner* SummonerContext::get_summoner() const
{
	return this->summoner;
}

GameObject::Id SummonerContext::object_id() const
{
	return GameObject::Id{0, this->summoner->get_id()};
}

bool SummonerContext::change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add)
{
	return this->summoner->change_extra(type, effect_id, value, can_add);
}

int16_t SummonerContext::revert_extra(BaseCard::ExtraType type, uint32_t effect_id)
{
	return this->summoner->revert_extra(type, effect_id);
}