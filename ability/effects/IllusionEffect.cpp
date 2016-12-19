#include "IllusionEffect.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"
#include "Log.h"

IllusionEffect::IllusionEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory)
{}

IllusionEffect::params_t IllusionEffect::get_middle_params(const cards_set_t &&cards) const
{
	auto begin = cards.begin();
	auto end = cards.end();
	size_t size = cards.size();

	params_t result = {
		std::accumulate(begin, end, 0,
			[](const uint16_t previous, const CardHandler* card) {
				return previous + card->get_health();
		}),
		std::accumulate(begin, end, 0,
			[](const uint16_t previous, const CardHandler* card) {
				return previous + card->get_damage();
		})
	};

	return {result.first / size, result.second / size};
}

bool IllusionEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();

	params_t old = {card->get_health(), card->get_damage()};
	params_t middle = this->get_middle_params(std::move(combatant->get_summoner()->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD)));

	if (old == middle)
		return false;

	params_t new_extra = {middle.first - card->get_health(), middle.second - card->get_damage()};

	bool changed = false;
	changed |= ctx.field->change_health(combatant, this->get_id(), new_extra.first);
	changed |= card->change_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id(), new_extra.second);

	if (changed)
	{
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::CHANGE_EFFECT, ability::Modifier::MODIFY_HEALTH, (int16_t)new_extra.first)});
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::CHANGE_EFFECT, ability::Modifier::MODIFY_ATTACK, (int16_t)new_extra.second)});
	}

	return changed;
}

bool IllusionEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();
	card->revert_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id());
	card->revert_extra(BaseCard::ExtraType::HEALTH, this->get_id());

	return true;
}
