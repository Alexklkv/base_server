#pragma once

#include "../IEntity.h"

class ActiveEffects;
class CardHandler;
class Effects;
class PassiveAbilities;
class Summoner;

namespace quests
{
	class Condition;
}

class IObjectContext : public IEntity, public GameObject
{
public:
	virtual bool is_card() const = 0;
	virtual bool is_summoner() const = 0;

	virtual void update_statistics(CardsStatistics::Type type, uint16_t value, bool is_critical = false) = 0;
	virtual void check_quest(const quests::Condition *condition, uint32_t amount = 1) = 0;

	virtual uint16_t get_damage() const = 0;
	virtual uint16_t get_injuire_bonus(const IObjectContext *target) const = 0;

	virtual float get_attack_spell_bonus() const = 0;
	virtual float get_dodge() const = 0;
	virtual uint16_t get_spell_strength_bonus(const uint16_t value) const = 0;
	virtual float get_critical_strength_bonus() const = 0;
	virtual uint8_t get_magic_resistance() const = 0;

	virtual bool can_cast(bool can_be_dead) const = 0;

	virtual BaseCard::Fraction get_fraction() const = 0;
	virtual Effects& get_effects() const = 0;
	virtual ActiveEffects* get_active_effects() const = 0;
	virtual PassiveAbilities* get_passives() const = 0;
	virtual ability::abilities_t get_abilities() const = 0;

	virtual CardHandler* get_card() = 0;
	virtual Summoner* get_summoner() = 0;

	virtual const CardHandler* get_card() const = 0;
	virtual const Summoner* get_summoner() const = 0;

//	virtual const CardHandler* get_const_card() const = 0;
//	virtual const Summoner* get_const_summoner() const = 0;

	virtual bool change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add) = 0;
	virtual int16_t revert_extra(BaseCard::ExtraType type, uint32_t effect_id) = 0;
};