#include "Target.h"

#include "ActiveEffects.h"
#include "Exception.h"
#include "Log.h"
#include "PassiveAbilities.h"

#include <numeric>

Target::Target(uint16_t max_health):
	max_health(max_health), current_health(max_health)
{
	this->active_effects = new ActiveEffects();
	this->passive_abilities = new PassiveAbilities();
}

Target::~Target()
{
	delete this->active_effects;
	delete this->passive_abilities;
}

bool Target::change_extra(extra_t &extra, uint32_t effect_id, int16_t value, bool)
{
	auto result = extra.emplace(effect_id, value);

	if (!result.second)
	{
		logger()->debug("Applying already applied effect for %d", effect_id);
		return false;
	}

	return true;
}

int16_t Target::revert_extra(extra_t &extra, uint32_t effect_id)
{
	auto found = extra.find(effect_id);

	if (found == extra.cend())
		return 0;

	int16_t value = found->second;
	extra.erase(found);

	return value;
}

uint16_t Target::heal(uint16_t heal)
{
	heal = std::min(heal, this->get_injuires());
	this->current_health += heal;
	return heal;
}

damage_t Target::damage(damage_t damage, BaseCard::Range)
{
	damage = std::min<damage_t>(damage, this->current_health);
	this->current_health -= damage;
	return damage;
}

void Target::kill()
{
	this->current_health = 0;
}

bool Target::is_dead() const
{
	return (this->current_health == 0);
}

uint8_t Target::left_health_percent() const
{
	return ((float) this->get_health() / this->get_max_health());
}

uint16_t Target::get_health() const
{
	return this->current_health;
}

uint16_t Target::get_injuires() const
{
	return this->get_max_health() - this->get_health();
}

uint16_t Target::get_base_health() const
{
	return this->max_health;
}

uint16_t Target::get_max_health() const
{
	const extra_t &health = this->extras[BaseCard::ExtraType::HEALTH];
	int16_t extra = std::accumulate(health.begin(), health.end(), 0,
		[](const int32_t prevoius, const std::pair<uint64_t, int32_t> &next) {
			return prevoius + next.second;
		});

	return unsigned_change(this->get_base_health(), extra);
}

float Target::get_critical() const
{
	return .0f;
}

mockable float Target::get_dodge() const
{
	const extra_t &doodge = this->extras[BaseCard::ExtraType::DOODGE];
	int16_t extra = std::accumulate(doodge.begin(), doodge.end(), 0,
			[](const int32_t prevoius, const std::pair<uint64_t, int32_t> &next) {
				return prevoius + next.second;
			});

	return extra / 100.0f;
}

float Target::get_extra_spell_strength() const
{
	const extra_t &strength = this->extras[BaseCard::ExtraType::SPELL_STRENGTH];
	int16_t extra = std::accumulate(strength.begin(), strength.end(), 0,
			[](const int32_t prevoius, const std::pair<uint64_t, int32_t> &next) {
				return prevoius + next.second;
			});

	return extra / 100.0f;
}

bool Target::change_extra(BaseCard::ExtraType type, uint32_t effect_id, int16_t value, bool can_add)
{
	if (type >= BaseCard::ExtraType::MAX_EXTRA)
	{
		logger()->warning("Change extra. Incorrect type for %d", effect_id);
		throw Exception("Change extra with incorrect type");
	}

	bool changed = this->change_extra(this->extras[type], effect_id, value, can_add);

	if (type == BaseCard::ExtraType::HEALTH && changed)
		this->current_health = unsigned_change(this->current_health, value);

	return changed;
}

int16_t Target::revert_extra(BaseCard::ExtraType type, uint32_t effect_id)
{
	if (type >= BaseCard::ExtraType::MAX_EXTRA)
	{
		logger()->warning("Revert extra. Incorrect type for %d", effect_id);
		throw Exception("Revert extra with incorrect type");
	}

	return this->revert_extra(this->extras[type], effect_id);
}