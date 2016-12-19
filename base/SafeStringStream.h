#pragma once

#include <sstream>
#include <string>
#include <type_traits>

class SafeStringStream
{
	std::stringstream s;

public:
	void str(const std::stringstream::__string_type &new_string)
	{
		this->s.str(new_string);
	}

	std::stringstream::__string_type str() const
	{
		return this->s.str();
	}

	std::stringstream::pos_type tellp()
	{
		return this->s.tellp();
	}

	void clear()
	{
		this->s.clear();
	}

	size_t size()
	{
		return this->s.tellp();
	}

	bool empty()
	{
		return this->size() == 0;
	}

	template<typename T>
	typename std::enable_if<std::is_enum<T>::value, SafeStringStream&>::type operator <<(const T &value);

	template<typename T>
	typename std::enable_if<!std::is_enum<T>::value, SafeStringStream&>::type operator <<(const T &value);
};

template<typename T>
typename std::enable_if<std::is_enum<T>::value, SafeStringStream&>::type SafeStringStream::operator <<(const T &value)
{
	return this->operator << (static_cast<typename std::underlying_type<T>::type>(value));
}

template<typename T>
typename std::enable_if<!std::is_enum<T>::value, SafeStringStream&>::type SafeStringStream::operator <<(const T &value)
{
	this->s << value;
	return *this;
}

template<>
typename std::enable_if<!std::is_enum<uint8_t>::value, SafeStringStream&>::type SafeStringStream::operator <<(const uint8_t &value);
template<>
typename std::enable_if<!std::is_enum<int8_t>::value, SafeStringStream&>::type SafeStringStream::operator <<(const int8_t &value);