#pragma once

namespace server
{

class Bucket
{
	friend class Writer;

private:
	char *data;
	uint32_t size;

public:
	Bucket();
	~Bucket();

	void resize(uint32_t size);
	void add(const void *data, uint32_t length);

	const char* get_data() const;
	uint32_t get_size() const;
};

}