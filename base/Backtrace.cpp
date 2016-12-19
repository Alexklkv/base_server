#include "Backtrace.h"

#include <execinfo.h>

Backtrace::Backtrace()
{
	this->generate();
}

Backtrace::Backtrace(const Backtrace &other):
	size(other.size)
{
	this->backtrace = new void*[BACKTRACE_DEPTH];

	for (size_t i = 0; i < BACKTRACE_DEPTH; i++)
		this->backtrace[i] = other.backtrace[i];
}

Backtrace::~Backtrace()
{
	delete [] this->backtrace;
}

void Backtrace::generate()
{
	this->backtrace = new void*[BACKTRACE_DEPTH];
	int size = ::backtrace(this->backtrace, BACKTRACE_DEPTH);

	this->size = std::max(0, size);
}

void Backtrace::write_to(int fd) const
{
	backtrace_symbols_fd(this->backtrace, this->size, fd);
}

std::vector<std::string> Backtrace::strings() const
{
	std::vector<std::string> result;
	if (this->size == 0 || this->backtrace == nullptr)
		return result;

	char** raw = backtrace_symbols(this->backtrace, this->size);

	if (raw == nullptr)
		return result;

	for (size_t i = 0; i < this->size; i++)
		result.emplace_back(raw[i]);

	free(raw); // backtrace manual says there's no need to cleanup strings inside raw

	return result;
}