#include "Log.h"

#include "Backtrace.h"
#include "Exception.h"

#include "base/util.h"

#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char RED_COLOR[] = "\033[0;31m";
static const char ORANGE_COLOR[] = "\033[0;33m";
static const char TEAL_COLOR[] = "\033[0;36m";
static const char MAGENTA_COLOR[] = "\033[0;95m";
static const char NORMAL_COLOR[] = "\033[0m";

using std::string;
using std::stringstream;
using std::vector;

std::unique_ptr<Log> Log::INSTANCE;

Log::Log(bool silent):
	stream(stdout), silent(silent)
{}

Log::~Log()
{
	if (this->stream != stdout)
		fclose(this->stream);
}

const Log* Log::instance()
{
	if (Log::INSTANCE == nullptr)
		throw Exception("Logger is not initialized, consider calling Log::init() on application start");

	return Log::INSTANCE.get();
}

void Log::init(bool silent, const char *filename)
{
	if (Log::INSTANCE.get() != nullptr)
		throw Exception("Calling Log::init on already initialized logger may cause memory corruption and therefore is prohibited");

	Log *instance = new Log(silent);

	if (filename != nullptr)
		instance->set_file(filename);

	Log::INSTANCE.reset(instance);
}

void Log::set_file(const char *file)
{
	this->stream = fopen(file, "a");
	if (this->stream == nullptr)
		exit(EXIT_FAILURE);
}

void Log::error(const char *message, ...) const
{
	va_list ap;
	va_start(ap, message);

	char *buffer = this->format(message, ap);
	this->print(RED_COLOR, "Error", buffer);
	fflush(this->stream);

	free(buffer);
	va_end(ap);

	// Do a segfault
	Log *null = nullptr;
	null->set_file(nullptr);
}

void Log::warning(const char *message, ...) const
{
	va_list ap;
	va_start(ap, message);

	char *buffer = this->format(message, ap);
	this->print(ORANGE_COLOR, "Warning", buffer);

#ifndef DEBUG
//	std::string trace = get_trace();
//	this->print(MAGENTA_COLOR, "Trace", trace.c_str());
#endif

	free(buffer);
	va_end(ap);
}

void Log::warning_notrace(const char *message, ...) const
{
	va_list ap;
	va_start(ap, message);

	char *buffer = this->format(message, ap);
	this->print(ORANGE_COLOR, "Warning", buffer);

	free(buffer);
	va_end(ap);
}

void Log::info(const char *message, ...) const
{
	va_list ap;
	va_start(ap, message);

	char *buffer = this->format(message, ap);
	this->print(NORMAL_COLOR, "Info", buffer);

	free(buffer);
	va_end(ap);
}

#ifdef DEBUG
void Log::debug(const char *message, ...) const
{
	va_list ap;
	va_start(ap, message);

	char *buffer = this->format(message, ap);
	this->print(TEAL_COLOR, "Debug", buffer);

	free(buffer);
	va_end(ap);
}
#endif

char* Log::format(const char *message, va_list &ap) const
{
	size_t size = 128;
	char *buffer = nullptr;

	va_list ac;
	while (1)
	{
		buffer = static_cast<char*>(realloc(buffer, size * sizeof(char)));
		if (buffer == nullptr)
			exit(EXIT_FAILURE);

		va_copy(ac, ap);

		size_t copied = vsnprintf(buffer, size, message, ac);

		va_end(ac);

		if (copied < size)
			return buffer;

		size = copied + 1;
	}
}

void Log::print(const char *color, const char *type, const char *buffer) const
{
	if (this->silent)
		return;

	time_t rawtime;
	tm info;

	time(&rawtime);
	localtime_r(&rawtime, &info);
	fprintf(this->stream, "%s[%02d.%02d %02d:%02d:%02d] %s: %s %s\n", color, info.tm_mday, info.tm_mon + 1, info.tm_hour, info.tm_min, info.tm_sec, type, buffer, NORMAL_COLOR);

#ifndef DEBUG
	fflush(this->stream);
#endif
}