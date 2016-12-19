#pragma once

#include "Effects.h"
#include "GameObject.h"
#include "IEntity.h"
#include "NoCopy.h"

#include <unordered_map>

class ActiveEffects;
class PassiveAbilities;

class Target : public IEntity, public GameObject, private NoCopy
{
public:
	typedef std::unordered_map<uint32_t, int16_t> extra_t;

private:
	std::array<extra_t, BaseCard::ExtraType::MAX_EXTRA> extras;

	inline bool change_extra(extra_t &extra, uint32_t effect_id, int16_t value, bool can_add = false);
	inline int16_t revert_extra(extra_t &extra, uint32_t effect_id);

	const uint16_t max_health;

protected:
	uint16_t current_health;

public:
	ActiveEffects *active_effects;
	PassiveAbilities *passive_abilities;
	Effects effects;

	explicit Target(uint16_t max_health);
	virtual ~Target();

	uint16_t heal(uint16_t heal) override;
	damage_t damage(damage_t damage, BaseCard::Range type) override;

	bool is_dead() const override;
	void kill() override;

	uint8_t left_health_percent() const;

	uint16_t get_health() const override;
	uint16_t get_injuires() const override;
	uint16_t get_base_health() const override;
	uint16_t get_max_health() const override;
	float get_critical() const override;
	float get_spell_strength() const;
	virtual float get_dodge() const;
	float get_extra_spell_strength() const;

	bool change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add = false);
	int16_t revert_extra(BaseCard::ExtraType type, uint32_t effect_id);
};