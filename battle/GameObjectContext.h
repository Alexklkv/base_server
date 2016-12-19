#pragma once

#include "BaseCard.h"
#include "CardsStatistics.h"
#include "GameObject.h"
#include "IObjectContext.h"

class CardHandler;
class Summoner;

class GameObjectContext : public IObjectContext
{
public:
	GameObjectContext() = default;
	GameObjectContext(const GameObjectContext &game_object_context) = default;
	virtual ~GameObjectContext();

	virtual bool is_card() const;
	virtual bool is_summoner() const;
};