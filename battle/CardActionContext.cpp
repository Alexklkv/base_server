#include "CardActionContext.h"

#include "BattleField.h"

CardActionContext::CardActionContext(BattleField *field, BattleAction::targets_t &targets):
	field(field), log(field->actions_log), targets_log(targets)
{}

CardActionContext::CardActionContext(BattleField *field):
	field(field), log(field->actions_log)
{}

void CardActionContext::changed_by(ability::Type ability)
{
	this->affected_by.emplace_back(ability);
}