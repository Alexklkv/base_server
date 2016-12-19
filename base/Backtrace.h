#pragma once

#include <string>
#include <vector>

class Backtrace
{
	static const size_t BACKTRACE_DEPTH = 20;

	void **backtrace;
	size_t size;

	void generate();

public:
	Backtrace();
	Backtrace(const Backtrace &other);
	virtual ~Backtrace();

	void write_to(int fd) const;
	std::vector<std::string> strings() const;
};