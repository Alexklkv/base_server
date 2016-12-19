#include "CardContext.h"

#include "Exception.h"
#include "Log.h"

#include "../CardHandler.h"
#include "../LegendsServer.h"
#include "../Range.h"
#include "../Summoner.h"

CardContext::CardContext(CardHandler *card, Summoner *summoner):
	card(card), summoner(summoner)
{
	if (card == nullptr)
		throw Exception("Null card supplied to CardContext constructor");

	if (summoner == nullptr)
		throw Exception("Null summoner supplied to CardContext constructor");
}

CardContext::~CardContext()
{}

bool CardContext::is_card() const
{
	return true;
}

uint16_t CardContext::heal(uint16_t heal)
{
	return this->card->heal(heal);
}

damage_t CardContext::damage(damage_t damage, BaseCard::Range type)
{
	return this->card->damage(damage, type);
}

void CardContext::kill()
{
	this->card->kill();
}

void CardContext::update_statistics(CardsStatistics::Type type, uint16_t data, bool is_critical)
{
	switch (type)
	{
		case CardsStatistics::DAMAGE:
			this->summoner->cards_statistics.update_damage(this->card, data, is_critical);
			return;
		case CardsStatistics::HEAL:
			this->summoner->cards_statistics.update_heal(this->card, data);
			return;
		case CardsStatistics::INJUIRE:
			this->summoner->cards_statistics.update_injuire(this->card, data);
			return;
		case CardsStatistics::DIED:
			this->summoner->cards_statistics.card_died(this->card, data);
			return;
		case CardsStatistics::MAX_TYPE:
			logger()->warning("Wrong card statistic type");
			return;
	}
}

void CardContext::check_quest(const quests::Condition *condition, uint32_t amount)
{
	this->summoner->check_quest(condition, amount);
}

uint16_t CardContext::get_base_health() const
{
	return this->card->get_base_health();
}

uint16_t CardContext::get_damage() const
{
	return this->card->get_damage();
}

uint16_t CardContext::get_health() const
{
	return this->card->get_health();
}

uint16_t CardContext::get_injuire_bonus(const IObjectContext *) const
{
	return 0;
}

uint16_t CardContext::get_injuires() const
{
	return this->card->get_injuires();
}

uint16_t CardContext::get_max_health() const
{
	return this->card->get_max_health();
}

float CardContext::get_attack_spell_bonus() const
{
	return 0;
}

float CardContext::get_critical() const
{
	return this->card->get_critical() / 100.0f;
}

float CardContext::get_dodge() const
{
	return this->card->get_dodge();
}

uint8_t CardContext::get_magic_resistance() const
{
	return this->card->get_magic_resistance();
}

uint16_t CardContext::get_spell_strength_bonus(const uint16_t) const
{
	return 0;
}

float CardContext::get_critical_strength_bonus() const
{
	return 2.0f;
}

bool CardContext::is_dead() const
{
	return this->card->is_dead();
}

bool CardContext::can_cast(bool can_be_dead) const
{
	return (!this->is_dead() || can_be_dead);
}

BaseCard::Fraction CardContext::get_fraction() const
{
	return this->card->get_fraction();
}

Effects& CardContext::get_effects() const
{
	return this->card->effects;
}

ActiveEffects* CardContext::get_active_effects() const
{
	return this->card->active_effects;
}

PassiveAbilities* CardContext::get_passives() const
{
	return this->card->passive_abilities;
}

ability::abilities_t CardContext::get_abilities() const
{
	return this->card->get_abilities();
}

CardHandler* CardContext::get_card()
{
	return this->card;
}

Summoner* CardContext::get_summoner()
{
	return this->summoner;
}

const CardHandler* CardContext::get_card() const
{
	return this->card;
}

const Summoner* CardContext::get_summoner() const
{
	return this->summoner;
}

GameObject::Id CardContext::object_id() const
{
	return GameObject::Id{card->get_id(), summoner->get_id()};
}

bool CardContext::change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add)
{
	return this->card->change_extra(type, effect_id, value, can_add);
}

int16_t CardContext::revert_extra(BaseCard::ExtraType type, uint32_t effect_id)
{
	return this->card->revert_extra(type, effect_id);
}