#pragma once

#include "Backtrace.h"

#include <exception>
#include <string>

class Exception : public std::exception
{
	const std::string message;
	Backtrace backtrace_storage;

public:
	explicit Exception(const char *message);
	explicit Exception(const std::string &message);
	explicit Exception(std::string &&message);
	Exception(const Exception &exception);

	virtual ~Exception() = default;

	virtual const char* what() const noexcept override;

	const Backtrace& backtrace() const noexcept;
};