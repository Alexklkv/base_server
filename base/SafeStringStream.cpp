#include "SafeStringStream.h"

template<>
typename std::enable_if<!std::is_enum<uint8_t>::value, SafeStringStream&>::type SafeStringStream::operator <<(const uint8_t &value)
{
	this->s << static_cast<uint16_t>(value);
	return *this;
}

template<>
typename std::enable_if<!std::is_enum<int8_t>::value, SafeStringStream&>::type SafeStringStream::operator <<(const int8_t &value)
{
	this->s << static_cast<int16_t>(value);
	return *this;
}