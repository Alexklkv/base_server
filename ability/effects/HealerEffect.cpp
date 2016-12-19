#include "HealerEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

#include "types.h"

#include <algorithm>

HealerEffect::HealerEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

HealerEffect::~HealerEffect()
{
	delete this->calculator;
}

combatant_ptr_t HealerEffect::get_min_health_card(combatant_ptr_t &owner) const
{
	Summoner *summoner = owner->get_summoner();
	auto cards = summoner->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);

	for (auto it = cards.begin(); it != cards.end(); )
	{
		if ((*it)->get_injuires() == 0)
			cards.erase(it++);
		else
			++it;
	}

	if (cards.empty())
		return nullptr;

	CardHandler* min_health_card = *std::min_element(cards.begin(), cards.end(), [](CardHandler* first, CardHandler* second){
		return first->get_health() < second->get_health();
	});

	return std::make_shared<Combatant>(min_health_card, summoner);
}

bool HealerEffect::on_self_round_start(RoundContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto min_health_card = this->get_min_health_card(combatant);
	if (min_health_card == nullptr)
		return false;

	uint16_t heal = this->calculator->get(min_health_card->get_card()->get_base_health());
	heal = ctx.field->heal(combatant, min_health_card, heal);
	if (heal == 0)
		return false;

	ctx.field->write_effect(this, combatant, {{min_health_card->object_id(), DataPacker().pack(ability::Action::HEAL, (uint32_t)heal)}});

	return true;
}

bool HealerEffect::on_before_application(StatsContext &) const
{
	return false;
}