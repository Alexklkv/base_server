#pragma once

#include "NoCopy.h"

#include "server/Bucket.h"
#include "server/Packet.h"

#include <boost/shared_ptr.hpp>

#include <concurrent_queue.h>

using boost::shared_ptr;

class BufferWrite : private NoCopy
{
private:
	typedef shared_ptr<server::Bucket> bucket_t;
	typedef tbb::concurrent_queue<bucket_t> buckets_t;

	buckets_t buckets;
	bucket_t current;
	uint32_t writed;

public:
	BufferWrite();

	void clear();

	void add(const server::Packet &packet, bool web);
	void add(const char *data, uint32_t size);

	int write(int socket, bool &empty);
};