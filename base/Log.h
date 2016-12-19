#pragma once

#include "Exception.h"
#include "NoCopy.h"

#include <memory>

#include <stdarg.h>
#include <stdio.h>

class Log : private NoCopy
{
private:
	static std::unique_ptr<Log> INSTANCE;

	FILE *stream;
	bool silent;

	char* format(const char *message, va_list &ap) const;
	void print(const char *color, const char *type, const char *buffer) const;

public:
	static const Log* instance();
	static void init(bool silent, const char *filename = nullptr);

	Log(bool silent);
	~Log();

	void error(const char *message, ...) const __attribute__((format (printf, 2, 3)));
	void warning(const char *message, ...) const __attribute__((format (printf, 2, 3)));
	void warning_notrace(const char *message, ...) const __attribute__((format (printf, 2, 3)));
	void info(const char *message, ...) const __attribute__((format (printf, 2, 3)));

#ifndef DEBUG
	void debug(const char *, ...) const __attribute__((format (printf, 2, 3))) {}
#else
	void debug(const char *message, ...) const __attribute__((format (printf, 2, 3)));
#endif

	void set_file(const char *file);
};

inline const Log* logger()
{
	return Log::instance();
}