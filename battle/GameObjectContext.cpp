#include "GameObjectContext.h"

#include "Random.h"

#include "misc.h"

GameObjectContext::~GameObjectContext()
{}

bool GameObjectContext::is_card() const
{
	return false;
}

bool GameObjectContext::is_summoner() const
{
	return false;
}