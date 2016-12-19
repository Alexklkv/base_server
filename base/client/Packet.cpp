#include "Packet.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Log.h"

#include <stdlib.h>
#include <string.h>

namespace client
{

uint16_t Packet::max_type = 0;
const char **Packet::formats = nullptr;

void Packet::init(const char **formats, uint16_t max_type)
{
	Packet::formats = formats;
	Packet::max_type = max_type;
}

Packet::Packet(const char *buffer, uint32_t size, BaseConfig::Protocol protocol, uint32_t id):
	protocol(protocol), type(0), id(0), valid(false), size(size), buffer(nullptr), group(nullptr)
{
	if (max_type == 0 || formats == nullptr)
		throw "Client's packets uninitialized";

	this->buffer = static_cast<char*>(malloc(size));
	memcpy(this->buffer, buffer, size);

	char *buffer_orig = this->buffer;
	uint32_t size_orig = this->size;

	this->valid = this->parse(id);

	this->buffer = buffer_orig;
	this->size = size_orig;
}

Packet::~Packet()
{
	free(this->buffer);
}

bool Packet::parse(uint32_t id)
{
	try
	{
		this->id = (this->protocol == BaseConfig::PROTOCOL_TCP) ? this->read<uint32_t>() : 0;
		this->type = this->read<uint16_t>();

		if (this->type <= 0 || this->type >= max_type || this->id != id)
		{
			logger()->warning("Received bad packet with type %u and id %u != %u", this->type, this->id, id);
			return false;
		}

		logger()->debug("Received packet with type %u and length %u", this->type, this->size);

		const char *format = formats[type];

		bool optional = false;

		const char *group_pos = nullptr;
		uint16_t group_length = 0;

		while (*format != '\0')
		{
			char symbol = *format;
			format++;

			if (symbol == ',')
			{
				if (optional == true || group_pos != nullptr)
					throw "Bad format";

				optional = true;
				continue;
			}

			if (this->size == 0 && optional)
				break;

			if (symbol == ']')
			{
				if (this->group == nullptr)
					throw "Bad format";

				group_length--;

				if (group_length != 0)
				{
					format = group_pos;
					this->group->next();
					continue;
				}

				this->add(this->group);
				this->group = nullptr;
				continue;
			}

			if (symbol == '[')
			{
				if (this->group != nullptr)
					throw "Bad format";

				this->group = new Group;

				group_length = this->read<uint16_t>();

				if (group_length != 0)
				{
					group_pos = format;
					this->group->next();
					continue;
				}

				format = strchr(format, ']');
				if (format == nullptr)
					throw "Bad format";
				format++;

				this->add(this->group);
				this->group = nullptr;
				continue;
			}
			//logger()->debug("Packet::parse symbol: %c", symbol);
			switch (symbol)
			{
				case 'S':
					this->fetch<const char*>();
					break;
				case 'L':
					this->fetch<uint64_t>();
					break;
				case 'F':
					this->fetch<float>();
					break;
				case 'I':
					this->fetch<uint32_t>();
					break;
				case 'W':
					this->fetch<uint16_t>();
					break;
				case 'B':
					this->fetch<uint8_t>();
					break;
				case 'A':
					this->fetch<const uint8_t*>();
					break;
				default:
					throw "Unknown format symbol";
			}
		}

		if (this->size != 0)
			throw "Data left";
	}
	catch (const char *message)
	{
		logger()->warning("%s for client packet %u", message, this->type);
		return false;
	}
	catch (...)
	{
		logger()->warning("Strange error for client packet %u", this->type);
		return false;
	}

	return true;
}

template<> const char* Packet::read<const char*>()
{
	uint16_t length = this->read<uint16_t>();

	if (this->size < static_cast<size_t>(length) + 1)
		throw "No data for string";

	const char *data = this->buffer;
	this->buffer[length++] = 0;

	this->buffer += length;
	this->size -= length;

	return data;
}

template<> const uint8_t* Packet::read<const uint8_t*>()
{
	uint32_t length = *reinterpret_cast<const uint32_t*>(this->buffer);

	if (this->size < static_cast<size_t>(length))
		throw "No data for byte array";

	const uint8_t *data = reinterpret_cast<const uint8_t*>(this->buffer);

	this->buffer += length + sizeof(length);
	this->size -= length + sizeof(length);

	return data;
}

bool Packet::is_valid() const
{
	return this->valid;
}

uint16_t Packet::get_type() const
{
	return this->type;
}

const void* Packet::get_data() const
{
	return this->buffer;
}

size_t Packet::get_size() const
{
	return this->size;
}

BaseConfig::Protocol Packet::get_protocol() const
{
	return this->protocol;
}

}