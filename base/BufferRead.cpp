#include "BufferRead.h"

#include "HTTP.h"
#include "Log.h"

#include "client/Packet.h"

#include <sys/socket.h>

#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE	1024
#define POLICY_DATA		"<policy-file-request/>"

#define WEBSOCKET_CONTINUE	0x0
//#define WEBSOCKET_TEXT	0x1
#define WEBSOCKET_BINARY	0x2
#define WEBSOCKET_CLOSE		0x8

BufferRead::BufferRead():
	size(DEFAULT_BUFFER_SIZE), readed(0), length(0), next_id(0)
{
	this->data = static_cast<char*>(malloc(this->size));
}

BufferRead::~BufferRead()
{
	this->length = 0;
	free(this->data);
}

bool BufferRead::empty() const
{
	if (this->length == 0)
		return true;
	return (this->readed < this->length + sizeof(this->length));
}

void BufferRead::clear()
{
	this->length = 0;
	this->readed = 0;
	this->next_id = 0;
}

int BufferRead::read(int socket)
{
	int size = recv(socket, this->data + this->readed, this->size - this->readed, 0);
	if (size <= 0)
		return size;

	this->readed += size;

	if (this->readed == this->size)
	{
		this->size *= 2;
		this->data = static_cast<char*>(realloc(this->data, this->size));
	}

	return size;
}

client::Packet* BufferRead::get()
{
	this->update();

	if (this->empty())
		return nullptr;

	client::Packet *packet = new client::Packet(this->data + sizeof(this->length), this->length, BaseConfig::PROTOCOL_TCP, this->next_id++);

	uint32_t size = this->length + sizeof(this->length);

	this->shift(size);

	return packet;
}

client::Packet* BufferRead::web(bool &success)
{
	uint32_t need = 2;
	uint32_t left = this->readed - this->length;

	if (left < need)
		return nullptr;

	char *current = this->data + this->length;

	bool fin = (*current & 0x80) >> 7;
	char type = *current & 0x0F;
	current++;

	if (this->length != 0 && type != 0)
	{
		logger()->warning("Received not first websocket packet fragment with type %d != 0", static_cast<int>(type));
		success = false;
		return nullptr;
	}

	if (type == WEBSOCKET_CLOSE)
	{
		success = false;
		return nullptr;
	}

	if (type != WEBSOCKET_CONTINUE && type != WEBSOCKET_BINARY)
	{
		logger()->warning("Received bad websocket packet type %d", static_cast<int>(type));
		success = false;
		return nullptr;
	}

	bool mask = (*current & 0x80) >> 7;
	uint64_t length = *current & 0x7F;
	current++;

	if (length == 126)
	{
		need += 2;
		if (left < need)
			return nullptr;

		length = * (uint16_t *) current;
		length = be16toh(length);

		current += 2;
	}
	else if (length == 127)
	{
		need += 8;
		if (left < need)
			return nullptr;

		length = * (uint64_t *) current;
		length = be64toh(length);

		current += 8;
	}

	uint32_t mask_key = 0;
	if (mask)
	{
		need += 4;
		if (left < need)
			return nullptr;

		mask_key = * (uint32_t *) current;

		current += 4;
	}

	if (left < need + length)
		return nullptr;

	logger()->debug("Readed WebSocket header fin: %" PRIu8 ", type: %" PRIu8 ", mask: %" PRIu8 ", length: %" PRIu32 " + %" PRIu64 ", mask_key: %" PRIu32, fin, type, mask, need, length, mask_key);

	if (mask_key != 0)
	{
		uint64_t boundary = length - length % 4;

		for (uint64_t i = 0; i < boundary; i += 4)
			* (uint32_t *) (current + i) ^= mask_key;

		for (uint64_t i = boundary; i < length; i++)
		{
			current[i] ^= (mask_key & 0xFF);
			mask_key >>= 8;
		}
	}

	left -= need;

	if (left != 0)
		memmove(this->data + this->length, current, left);

	this->length += length;
	this->readed -= need;

	if (fin == 0)
		return nullptr;

	client::Packet *packet = new client::Packet(this->data, this->length, BaseConfig::PROTOCOL_TCP, this->next_id++);

	uint32_t size = this->length;

	this->readed -= size;
	this->length = 0;

	if (this->readed != 0)
		memmove(this->data, this->data + size, this->readed);

	return packet;
}

bool BufferRead::http(HTTP *http)
{
	if (this->readed < 4)
		return false;
	this->data[this->readed] = 0;

	uint32_t readed = 0;
	if (!http->parse(this->data, readed))
		return false;

	if (readed == 0)
		return true;

	this->readed -= readed;

	if (this->readed != 0)
		memmove(this->data, this->data + readed, this->readed);

	return true;
}

void BufferRead::update()
{
	if (this->length != 0)
		return;
	if (this->readed < sizeof(this->length))
		return;

	//this->length = * (uint32_t *) this->data;
	this->length = * reinterpret_cast<uint32_t*>(this->data);
}

void BufferRead::shift(uint32_t size)
{
	this->readed -= size;
	this->length = 0;

	if (this->readed != 0)
		memmove(this->data, this->data + size, this->readed);
}

bool BufferRead::policy()
{
	if (this->next_id != 0)
		return false;

	const uint32_t size = sizeof(POLICY_DATA);

	if (this->readed < size)
		return false;

	if (strcmp(this->data, POLICY_DATA) != 0)
		return false;

	this->shift(size);

	return true;
}