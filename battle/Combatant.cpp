#include "Combatant.h"

#include "CardContext.h"
#include "Log.h"
#include "NoneContext.h"
#include "Random.h"
#include "SummonerContext.h"

#include "misc.h"

static GameObjectContext* create_context(GameObjectContext *context)
{
	if (context->is_card())
		return new CardContext(context->get_card(), context->get_summoner());
	if (context->is_summoner())
		return new SummonerContext(context->get_summoner());

	NoneContext* none_context = dynamic_cast<NoneContext*>(context);
	if (none_context == nullptr)
	{
		logger()->warning("NoneContext cannot be casted to NoneContext");
		return new NoneContext();
	}

	return new NoneContext(none_context->get_abilities());
}

static GameObjectContext* create_context(CardHandler *card, Summoner *summoner)
{
	if (card != nullptr)
		return new CardContext(card, summoner);
	if (summoner != nullptr)
		return new SummonerContext(summoner);

	return new NoneContext();
}

Combatant::Combatant(ability::abilities_t abilities):
	context(new NoneContext(abilities))
{}

Combatant::Combatant(Summoner *summoner):
	context(new SummonerContext(summoner))
{}

Combatant::Combatant(CardHandler *card, Summoner *summoner):
	context(create_context(card, summoner))
{}

Combatant::Combatant(const Combatant &combatant):
	context(create_context(combatant.context))
{}

Combatant::~Combatant()
{
	delete this->context;
}

bool Combatant::is_opponent(const Combatant &other) const
{
	if ((!this->is_card() && !this->is_summoner()) || (!other.is_card() && !other.is_summoner()))
		return false;

	return (this->get_summoner() != other.get_summoner());
}

bool Combatant::equals(const Combatant &other) const
{
	return (this->object_id() == other.object_id());
}

bool Combatant::check_critical(float additional) const
{
	return Random::chance(this->get_critical() + additional);
}

bool Combatant::check_dodge(float additional) const
{
	return Random::chance(this->get_dodge() + additional);
}

bool Combatant::is_card() const
{
	return this->context->is_card();
}

bool Combatant::is_summoner() const
{
	return this->context->is_summoner();
}

uint16_t Combatant::heal(uint16_t heal)
{
	return this->context->heal(heal);
}

damage_t Combatant::damage(damage_t damage, BaseCard::Range type)
{
	return this->context->damage(damage, type);
}

void Combatant::kill()
{
	this->context->kill();
}

void Combatant::update_statistics(CardsStatistics::Type type, uint16_t value, bool is_critical)
{
	this->context->update_statistics(type, value, is_critical);
}

void Combatant::check_quest(const quests::Condition *condition, uint32_t amount)
{
	this->context->check_quest(condition, amount);
}

uint16_t Combatant::get_base_health() const
{
	return this->context->get_base_health();
}

uint16_t Combatant::get_damage() const
{
	return this->context->get_damage();
}

uint16_t Combatant::get_health() const
{
	return this->context->get_health();
}

uint16_t Combatant::get_injuires() const
{
	return this->context->get_injuires();
}

uint16_t Combatant::get_injuire_bonus(const IObjectContext *target) const
{
	return this->context->get_injuire_bonus(target);
}

uint16_t Combatant::get_max_health() const
{
	return this->context->get_max_health();
}

float Combatant::get_attack_spell_bonus() const
{
	return this->context->get_attack_spell_bonus();
}

float Combatant::get_critical() const
{
	return this->context->get_critical();
}

float Combatant::get_dodge() const
{
	return this->context->get_dodge();
}

uint8_t Combatant::get_magic_resistance() const
{
	return this->context->get_magic_resistance();
}

uint16_t Combatant::get_spell_strength_bonus(const uint16_t value) const
{
	return this->context->get_spell_strength_bonus(value);
}

float Combatant::get_critical_strength_bonus() const
{
	return this->context->get_critical_strength_bonus();
}

bool Combatant::is_dead() const
{
	return this->context->is_dead();
}

bool Combatant::can_cast(bool can_be_dead) const
{
	return this->context->can_cast(can_be_dead);
}

BaseCard::Fraction Combatant::get_fraction() const
{
	return this->context->get_fraction();
}

Effects& Combatant::get_effects() const
{
	return this->context->get_effects();
}

ActiveEffects* Combatant::get_active_effects() const
{
	return this->context->get_active_effects();
}

PassiveAbilities* Combatant::get_passives() const
{
	return this->context->get_passives();
}

ability::abilities_t Combatant::get_abilities() const
{
	return this->context->get_abilities();
}

CardHandler* Combatant::get_card()
{
	return this->context->get_card();
}

Summoner* Combatant::get_summoner()
{
	return this->context->get_summoner();
}

const CardHandler* Combatant::get_card() const
{
	return this->context->get_card();
}

const Summoner* Combatant::get_summoner() const
{
	return this->context->get_summoner();
}

GameObject::Id Combatant::object_id() const
{
	return this->context->object_id();
}

bool Combatant::change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add)
{
	return this->context->change_extra(type, effect_id, value, can_add);
}

int16_t Combatant::revert_extra(BaseCard::ExtraType type, uint32_t effect_id)
{
	return this->context->revert_extra(type, effect_id);
}