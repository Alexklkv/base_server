#pragma once

class EventListener
{
public:
	virtual ~EventListener() = default;

	virtual void event(uint8_t type, uint32_t sender_id = 0, uint32_t data = 0) = 0;
};