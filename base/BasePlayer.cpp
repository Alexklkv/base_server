#include "BasePlayer.h"

#include "Api.h"
#include "BaseClient.h"
#include "BaseConfig.h"
#include "BaseServer.h"
#include "Log.h"
#include "Saver.h"

#include "server/Group.h"

#include "util.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

BasePlayer::BasePlayer(uint32_t inner_id, uint64_t net_id, Api::Type type, uint32_t register_time):
	Savable(inner_id), register_time(register_time), net_id(net_id), type(type)
{
	this->ban = new Ban;

	this->name = strdup("");
	this->photo = strdup("");
	this->profile = strdup("");
	this->status = strdup("");

	this->bday = 0;
	this->sex = SEX_UNKNOWN;
	this->moderator = 0;

	this->login_time = 0;
	this->logout_time = 0;
	this->day_start = 0;
	this->day_current = 0;
	this->last_order = 0;

	this->client = nullptr;
}

BasePlayer::~BasePlayer()
{
	delete this->ban;

	free(this->status);
	free(this->profile);
	free(this->photo);
	free(this->name);
}

bool BasePlayer::login(BaseClient *client)
{
	this->login_time = time(nullptr);

	if (this->client.compare_and_swap(client, nullptr) != nullptr)
		return false;
	return true;
}

void BasePlayer::logout()
{
	this->logout_time = time(nullptr);

	this->saved_remove(SAVED_DATA);

	this->client = nullptr;
}

bool BasePlayer::is_admin() const
{
	return (this->type == Api::TYPE_ADMIN);
}

bool BasePlayer::is_moderator() const
{
	return (this->moderator == 1);
}

bool BasePlayer::is_online() const
{
	return (this->client != nullptr);
}

bool BasePlayer::is_expired() const
{
	return (time(nullptr) - this->saved_time > config()->PLAYER_EXPIRE_TIMEOUT);
}

bool BasePlayer::is_man() const
{
	return (this->sex == SEX_MAN);
}

void BasePlayer::set_ban(uint8_t reason, uint8_t repeated, uint32_t judge)
{
	this->ban->set(reason, repeated, judge);

	this->saved_remove(SAVED_DATA);
}

void BasePlayer::on_load()
{}

uint8_t BasePlayer::get_age(time_t to_time) const
{
	if (this->bday == 0)
		return 0;

	time_t curr_time = to_time;
	time_t bday_time = static_cast<time_t>(this->bday);

	tm curr = gmtime_threadsafe(curr_time);
	tm bday = gmtime_threadsafe(bday_time);

	int years_left = curr.tm_year - bday.tm_year;
	if (years_left <= 0)
		return 0;

	if (curr.tm_mon < bday.tm_mon)
		years_left--;
	if (curr.tm_mon == bday.tm_mon && curr.tm_mday < bday.tm_mday)
		years_left--;

	return years_left;
}

bool BasePlayer::update_day()
{
	time_t curr_time = time(nullptr);

	tm curr = localtime_threadsafe(curr_time);

	uint16_t day = static_cast<uint16_t>(curr.tm_yday) + 1;

	if (this->day_current == day)
		return false;

	if (this->day_start == 0 || this->day_current != day - 1)
		this->day_start = day;

	this->day_current = day;

	this->saved_remove(SAVED_DATA);

	return true;
}

bool BasePlayer::save()
{
	logger()->debug("Saving player %u", this->inner_id);

	bool saved = false;
	int saved_old = this->saved.fetch_and_store(SAVED_ALL);

	if ((saved_old & SAVED_DATA) == 0)
	{
		logger()->debug("Saving player %u data", this->inner_id);
		this->save_data();
		saved = true;
	}

	if ((saved_old & SAVED_INFO) == 0)
	{
		logger()->debug("Saving player %u info", this->inner_id);
		this->save_info();
		saved = true;
	}

	this->saved_time = time(nullptr);

	return saved;
}

void BasePlayer::set(Field field, const char *value)
{
	char **field_ref = nullptr;
	size_t field_length = 0;

	switch (field)
	{
		case FIELD_NAME:
			field_ref = &this->name;
			field_length = 25;
			break;
		case FIELD_PHOTO:
			field_ref = &this->photo;
			field_length = 255;
			break;
		case FIELD_PROFILE:
			field_ref = &this->profile;
			field_length = 255;
			break;
		case FIELD_STATUS:
			field_ref = &this->status;
			field_length = 100;
			break;
	}

	if (field_ref == nullptr)
		return;

	if (value == nullptr)
		value = "";

	size_t length = strlen_utf(value);
	if (length > field_length)
		return;

	char *old_ref = *field_ref;

	if (field == FIELD_NAME)
		*field_ref = strdup_clean(value);
	else
		*field_ref = strdup(value);

	if (old_ref != nullptr)
		free(old_ref);
}

void BasePlayer::send(const server::Packet &packet)
{
	BaseClient *client = this->client;
	if (client == nullptr)
		return;

	client->send(packet);
}

void BasePlayer::event(uint8_t type, uint32_t sender_id, uint32_t data)
{
	BaseClient *client = this->client;
	if (client == nullptr)
		return;

	client->event(type, sender_id, data);
}

void BasePlayer::update_data()
{
	this->saved_remove(SAVED_DATA);
}

void BasePlayer::update_info()
{
	this->saved_remove(SAVED_INFO);
}

void BasePlayer::update_other()
{
	this->saved_remove(SAVED_OTHER);
}