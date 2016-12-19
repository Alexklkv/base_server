#pragma once

#include "SafeStringStream.h"

class DatabasePacker
{
public:
	explicit DatabasePacker(const char *prefix = "", const char *postfix = "");

	template<typename... Ts>
	void pack(const Ts&... args);

	std::string str() const;
	bool empty() const;
	bool exists() const;

	std::string description() const;

private:
	SafeStringStream stream;
	bool is_empty;

	std::string prefix;
	std::string postfix;

	template<typename T, typename... Ts>
	void internal_pack(bool first, const T &current, const Ts&... args);
	void internal_pack(bool first);
};

template<typename... Ts>
void DatabasePacker::pack(const Ts&... args)
{
	if (!this->is_empty)
		this->stream << ",";

	this->is_empty = false;

	this->stream << "(";
	this->internal_pack(true, args...);
}

template<typename T, typename... Ts>
void DatabasePacker::internal_pack(bool first, const T &current, const Ts& ... args)
{
	if (!first)
		this->stream << ",";

	this->stream << current;
	this->internal_pack(false, args...);
}