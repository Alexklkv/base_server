#pragma once

#include "Condition.h"
#include "ICard.h"

#include "../BaseCard.h"
#include "../CardMask.h"
#include "../QuestsParams.h"

class BaseCardParams;

namespace quests
{

class KillCardCondition : public Condition
{
	friend class ::QuestsParams;

private:
	CardMask mask;
	uint16_t card_type;
	uint16_t location_id;

public:
	KillCardCondition(CardMask &mask);
	KillCardCondition(const ICard *card);
	KillCardCondition(uint16_t card_type, uint16_t location_id = 0);

	QuestType type() const override;

	bool compare(const Condition *condition) const override;
};

}