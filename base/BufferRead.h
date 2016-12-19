#pragma once

#include "NoCopy.h"

#include "client/Packet.h"

class HTTP;

class BufferRead : private NoCopy
{
private:
	char *data;
	uint32_t size;
	uint32_t readed;
	uint32_t length;
	uint32_t next_id;

	void update();
	void shift(uint32_t size);

	bool empty() const;

public:
	BufferRead();
	~BufferRead();

	bool policy();

	void clear();
	int read(int socket);
	client::Packet* get();
	client::Packet* web(bool &success);
	bool http(HTTP *http);
};