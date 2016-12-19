#include "Ban.h"

#include "BaseConfig.h"
#include "BaseServer.h"

#include <time.h>

Ban::Ban():
	type(TYPE_NONE), reason(0), judge(0), finish(0), start(0)
{}

void Ban::set(uint8_t reason, uint8_t repeated, uint32_t jugde)
{
	if (reason >= config()->BAN_TIMES.size())
		return;

	uint32_t current_time = time(nullptr);
	if (current_time < this->start + config()->BAN_REPEAT_TIMEOUT)
		return;

	Type type = repeated ? config()->BAN_TIMES[reason].repeated_type : config()->BAN_TIMES[reason].type;
	uint32_t duration = (repeated ? config()->BAN_TIMES[reason].repeated_time : config()->BAN_TIMES[reason].time) * 60;

	this->type = type;
	this->reason = reason;
	this->judge = jugde;
	this->finish = current_time + duration;
	this->start = current_time;
}

void Ban::set(Type type, uint8_t reason, uint32_t judge, uint32_t finish)
{
	this->type = type;
	this->reason = reason;
	this->judge = judge;
	this->finish = finish;
}

bool Ban::is_active(Type type) const
{
	if (this->type != type)
		return false;

	return (this->finish > time(nullptr));
}

uint32_t Ban::get() const
{
	uint32_t current_time = time(nullptr);
	if (this->finish <= current_time)
		return 0;

	return (this->finish - current_time);
}

void Ban::write(server::Writer *writer) const
{
	writer->add(static_cast<uint8_t>(this->type));
	writer->add(this->reason);
	writer->add(this->judge);
	writer->add(this->get());
}