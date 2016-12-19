#include "ActiveEffect.h"

#include "Exception.h"

#include "ability/effects/basic/BattleEffect.h"
#include "ability/effects/retention/RetentionPolicy.h"

static uint64_t c_key(ComboID combo)
{
	// Combo key sets highest bit to 1 making all combos greater than game objects
	return bitwise_pack<uint64_t>(1, combo.id, sizeof(uint64_t) * 8 - 1);
}

static uint64_t c_key(const GameObject::Id &id)
{
	return id.value();
}

ActiveEffect::ActiveEffect(const BattleEffect *effect, combatant_ptr_t caster) :
	effect(effect), caster(caster)
{}

ActiveEffect::~ActiveEffect()
{
	for (auto &pair : this->retentions)
		delete pair.second;
}

void ActiveEffect::add(composite_source_key_t key)
{
	std::pair<retentions_t::iterator, bool> inserted = this->retentions.emplace(key, nullptr);
	if (!inserted.second)
		delete inserted.first->second;
	inserted.first->second = this->effect->create_policy();
	this->removed = false;
}

void ActiveEffect::add(const GameObject::Id &source)
{
	this->add(c_key(source));
}

void ActiveEffect::add(ComboID combo)
{
	this->add(c_key(combo));
}

void ActiveEffect::retention_update(const std::function<void(composite_source_key_t, RetentionPolicy*)> &callback)
{
	for (auto iter = this->retentions.begin(); iter != this->retentions.end(); )
	{
		RetentionPolicy *retention = iter->second;
		callback(iter->first, retention);

		if (!retention->expired())
		{
			++iter;
			continue;
		}

		delete retention;
		iter = this->retentions.erase(iter);
	}
}

void ActiveEffect::retention_update(const std::function<void(RetentionPolicy*)> &callback)
{
	this->retention_update([&callback] (composite_source_key_t, RetentionPolicy *policy) {
		callback(policy);
	});
}

void ActiveEffect::on_end_turn()
{
	this->retention_update(&RetentionPolicy::end_turn);
}

void ActiveEffect::on_move()
{
	this->retention_update(&RetentionPolicy::move);
}

void ActiveEffect::on_other_move(const GameObject::Id &moved)
{
	auto moved_key = c_key(moved);
	this->retention_update([moved_key] (composite_source_key_t key, RetentionPolicy *policy) {
		if (key == moved_key)
			policy->move();
	});
}

void ActiveEffect::on_end_action()
{
	this->retention_update(&RetentionPolicy::end_action);
}

void ActiveEffect::on_combo_removal(ComboID id)
{
	auto combo_key = c_key(id);
	this->retention_update([combo_key] (composite_source_key_t, RetentionPolicy *policy) {
		policy->combo_removal();
	});
}

const BattleEffect* ActiveEffect::get() const
{
	if (this->expired())
		throw Exception("Expired effect requested");

	return this->effect;
}

const BattleEffect* ActiveEffect::get_effect() const
{
	return this->effect;
}

bool ActiveEffect::expired() const
{
	if (this->removed)
		return true;

	if (this->retentions.empty())
		return true;

	if (this->caster != nullptr && this->caster->is_dead())
		return true;

	return std::all_of(this->retentions.cbegin(), this->retentions.cend(), [] (const retentions_t::value_type & pair) {
		return pair.second->expired();
	});
}