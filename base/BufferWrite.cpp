#include "BufferWrite.h"

#include "BaseServer.h"
#include "Log.h"

#include <sys/socket.h>

BufferWrite::BufferWrite():
	writed(0)
{}

void BufferWrite::clear()
{
	this->buckets.clear();

	this->current.reset();
	this->writed = 0;
}

void BufferWrite::add(const server::Packet &packet, bool web)
{
	if (web)
	{
		unsigned char header[10] = {0x82};
		uint8_t header_size = 0;

		uint32_t packet_size = packet.get_size();
		if (packet_size > 65535)
		{
			header_size = 10;
			*(uint8_t *) (header + 1) = 0x7F;
			*(uint64_t *) (header + 2) = htobe64(packet_size);
		}
		else if (packet_size > 125)
		{
			header_size = 4;
			*(uint8_t *) (header + 1) = 0x7E;
			*(uint16_t *) (header + 2) = htobe16(packet_size);
		}
		else
		{
			header_size = 2;
			*(uint8_t *) (header + 1) = static_cast<uint8_t>(packet_size);
		}

		this->add(reinterpret_cast<char*>(header), header_size);
	}

	this->buckets.push(packet.get_bucket());
}

void BufferWrite::add(const char *data, uint32_t size)
{
	bucket_t bucket(new server::Bucket);
	bucket->resize(size);
	bucket->add(data, size);

	this->buckets.push(bucket);
}

int BufferWrite::write(int socket, bool &empty)
{
	if (!this->current && !this->buckets.try_pop(this->current))
	{
		empty = true;
		return -1;
	}

	uint32_t total = this->current->get_size();

	int size = send(socket, this->current->get_data() + this->writed, total - this->writed, 0);
	if (size <= 0)
		return size;

	this->writed += size;

	if (this->writed == total)
	{
		this->current.reset();
		this->writed = 0;
	}

	return size;
}