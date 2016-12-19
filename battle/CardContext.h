#pragma once

#include "GameObjectContext.h"

class CardContext : public GameObjectContext
{
private:
	CardHandler *card;
	Summoner *summoner;

public:
	CardContext(CardHandler *card, Summoner *summoner);
	virtual ~CardContext();

	bool is_card() const override;

	uint16_t heal(uint16_t heal) override;
	damage_t damage(damage_t damage, BaseCard::Range type) override;

	void kill() override;

	void update_statistics(CardsStatistics::Type type, uint16_t data, bool is_critical = false) override;
	void check_quest(const quests::Condition *condition, uint32_t amount) override;

	uint16_t get_base_health() const override;
	uint16_t get_damage() const override;
	uint16_t get_health() const override;
	uint16_t get_injuire_bonus(const IObjectContext *target) const override;
	uint16_t get_injuires() const override;
	uint16_t get_max_health() const override;

	float get_attack_spell_bonus() const override;
	float get_critical() const override;
	float get_dodge() const override;
	uint16_t get_spell_strength_bonus(const uint16_t value) const override;
	float get_critical_strength_bonus() const override;
	uint8_t get_magic_resistance() const override;

	bool is_dead() const override;
	bool can_cast(bool can_be_dead) const override;

	BaseCard::Fraction get_fraction() const override;
	Effects& get_effects() const override;
	ActiveEffects* get_active_effects() const override;
	PassiveAbilities* get_passives() const override;
	ability::abilities_t get_abilities() const override;

	CardHandler* get_card() override;
	Summoner* get_summoner() override;

	const CardHandler* get_card() const override;
	const Summoner* get_summoner() const override;

	Id object_id() const override;

	bool change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add) override;
	int16_t revert_extra(BaseCard::ExtraType type, uint32_t effect_id) override;
};