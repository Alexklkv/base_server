#pragma once

#include "NoCopy.h"

#include "server/Bucket.h"

#include <boost/shared_ptr.hpp>

namespace server
{

class Group;
struct Object;

using boost::shared_ptr;

class Writer : private NoCopy
{
private:
	void write(const void *data, uint32_t length);

protected:
	uint32_t max;
	shared_ptr<Bucket> bucket;

	Writer();
	Writer(uint32_t start_size);

public:
	virtual ~Writer();

	const char* get_data() const;
	uint32_t get_size() const;
	shared_ptr<Bucket> get_bucket() const;

	virtual void add(const char *value);
	virtual void add(const char *value, uint32_t length);
	virtual void add(float value);
	virtual void add(uint64_t value);
	virtual void add(uint32_t value);
	virtual void add(uint16_t value);
	virtual void add(uint8_t value);
	virtual void add(const Object &object);
	virtual void add(const Object *object);
	virtual void add(const Group *group, bool as_array = false);
};

}