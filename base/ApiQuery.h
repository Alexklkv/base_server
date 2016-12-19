#pragma once

#include "Api.h"

class BasePlayer;

struct ApiQuery
{
	BasePlayer *player;

	uint64_t net_id;
	uint32_t inner_id;
	Api::Type type;
};