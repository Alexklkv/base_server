#include "Exception.h"

Exception::Exception(const char *message):
	message(message)
{}

Exception::Exception(const std::string &message):
	message(message)
{}

Exception::Exception(std::string &&message):
	message(std::move(message))
{}

Exception::Exception(const Exception &exception):
	message(exception.message), backtrace_storage(exception.backtrace_storage)
{}

const char* Exception::what() const noexcept
{
	return this->message.c_str();
}

const Backtrace& Exception::backtrace() const noexcept
{
	return this->backtrace_storage;
}