#pragma once

struct ClientEvent
{
	uint8_t type;
	uint32_t sender_id;
	uint32_t data;
};