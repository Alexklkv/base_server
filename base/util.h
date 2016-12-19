#pragma once

#include <string>
#include <vector>

#include <time.h>

char* md5_get(const char *buffer);
char* sha1_get(const char *buffer, size_t length, bool format = true);
char* sha256_get(const char *buffer, const char *key);
char* base64_get(char *buffer, size_t length);
char* unbase64_get(const char *buffer);
char* format(const char *message, ...);
wchar_t* strdup_utf(const char *src);
char* strdup_clean(const char *buffer);
size_t strlen_utf(const char *src);
std::string utf_to_ncr(const char *text);
std::string escape(const char *text);
std::string join(const std::vector<uint64_t> *values);
struct tm localtime_threadsafe(time_t timestamp);
struct tm gmtime_threadsafe(time_t timestamp);
std::string get_trace();