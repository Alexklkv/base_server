#pragma once

#include "Api.h"
#include "ApiBalance.h"
#include "Ban.h"
#include "NoCopy.h"
#include "Savable.h"

#include <atomic.h>

class BaseClient;
class BaseDatabase;

namespace server
{
	class Packet;
}

using tbb::atomic;

class BasePlayer : public Savable, private NoCopy
{
private:
	virtual void save_info() const = 0;
	virtual void save_data() const = 0;

protected:
	enum Sex : uint8_t
	{
		SEX_UNKNOWN,
		SEX_WOMAN,
		SEX_MAN
	};

	enum Field : uint8_t
	{
		FIELD_NAME,
		FIELD_PHOTO,
		FIELD_PROFILE,
		FIELD_STATUS
	};

	atomic<BaseClient*> client;

	char *name;
	char *photo;
	char *profile;
	char *status;

	uint32_t login_time;
	uint32_t logout_time;
	uint32_t register_time;

	Sex sex;
	uint8_t moderator;
	int32_t bday;

	uint16_t day_start;
	uint16_t day_current;

	virtual bool login(BaseClient *client);
	virtual void logout();

	virtual bool update_day();

	virtual void set_ban(uint8_t reason, uint8_t repeated, uint32_t judge);

	void set(Field field, const char *value);

public:
	uint64_t net_id;
	uint32_t last_order;
	Api::Type type;

	Ban *ban;

	BasePlayer(uint32_t inner_id, uint64_t net_id, Api::Type type, uint32_t register_time);
	virtual ~BasePlayer();

	bool is_admin() const;
	bool is_moderator() const;
	bool is_online() const;
	bool is_expired() const;
	bool is_man() const;

	uint8_t get_age(time_t to_time) const;

	virtual void send(const server::Packet &packet);
	virtual void event(uint8_t type, uint32_t sender_id = 0, uint32_t data = 0);

	virtual void update_data();
	virtual void update_info();
	virtual void update_other();

	virtual bool save();

	virtual uint8_t calc_bonus(uint32_t value) = 0;
	virtual void add_balance(uint32_t value, uint8_t offer_type) = 0;
	virtual void update_offers(const std::vector<bool> &offers) = 0;

	virtual void on_load();
};