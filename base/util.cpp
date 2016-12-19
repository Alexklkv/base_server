#include "util.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Log.h"

#include <boost/lexical_cast.hpp>

#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

#include <sys/wait.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <fcntl.h>
#include <unistd.h>

using boost::lexical_cast;
using std::string;

inline static char get_char(unsigned char code)
{
	return (code < 10) ? (code + '0') : (code - 10 + 'a');
}

char* md5_get(const char *buffer)
{
	size_t size = strlen(buffer);
	unsigned char *digest = static_cast<unsigned char*>(malloc((MD5_DIGEST_LENGTH * 2 + 1) * sizeof(unsigned char)));

	MD5(reinterpret_cast<const unsigned char*>(buffer), size, digest);

	for (int i = MD5_DIGEST_LENGTH - 1; i >= 0; i--)
	{
		digest[i * 2 + 1] = get_char(digest[i] & 0x0F);
		digest[i * 2] = get_char((digest[i] >> 4) & 0x0F);
	}

	digest[MD5_DIGEST_LENGTH * 2] = 0;

	return reinterpret_cast<char*>(digest);
}

char* sha1_get(const char *buffer, size_t length, bool format)
{
	char *digest = static_cast<char*>(malloc((SHA_DIGEST_LENGTH * (format ? 2 : 1) + 1) * sizeof(char)));

	SHA1(reinterpret_cast<const unsigned char*>(buffer), length, reinterpret_cast<unsigned char*>(digest));

	if (!format)
	{
		digest[SHA_DIGEST_LENGTH] = 0;
		return digest;
	}

	for (int i = SHA_DIGEST_LENGTH - 1; i >= 0; i--)
	{
		digest[i * 2 + 1] = get_char(digest[i] & 0x0F);
		digest[i * 2] = get_char((digest[i] >> 4) & 0x0F);
	}

	digest[SHA_DIGEST_LENGTH * 2] = 0;

	return digest;
}

char* sha256_get(const char *buffer, const char *key)
{
	unsigned int digest_length = SHA256_DIGEST_LENGTH * 2 + 1;
	unsigned char *digest = static_cast<unsigned char*>(malloc(digest_length * sizeof(unsigned char)));

	size_t size = strlen(buffer);
	int key_length = strlen(key);
	HMAC(EVP_sha256(), key, key_length, reinterpret_cast<const unsigned char*>(buffer), size, digest, &digest_length);

	for (int i = SHA256_DIGEST_LENGTH - 1; i >= 0; i--)
	{
		digest[i * 2 + 1] = get_char(digest[i] & 0x0F);
		digest[i * 2] = get_char((digest[i] >> 4) & 0x0F);
	}

	digest[SHA256_DIGEST_LENGTH * 2] = 0;

	return reinterpret_cast<char*>(digest);
}

char* base64_get(char *buffer, size_t length)
{
	BIO *b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	BIO *bmem = BIO_new(BIO_s_mem());

	BIO_push(b64, bmem);

	BIO_write(b64, static_cast<void*>(buffer), static_cast<int>(length));
	BIO_ctrl(b64, BIO_CTRL_FLUSH, 0, nullptr);

	char *data;
	length = BIO_get_mem_data(bmem, &data);

	char *text = static_cast<char*>(malloc(length + 1));
	memcpy(text, data, length);
	text[length] = 0;

	BIO_free_all(b64);

	return text;
}

char* unbase64_get(const char *buffer)
{
	size_t length = strlen(buffer);

	BIO *b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	BIO *bmem = BIO_new_mem_buf(const_cast<char*>(buffer), length);

	bmem = BIO_push(b64, bmem);

	unsigned char *digest = static_cast<unsigned char*>(malloc((length) * sizeof(unsigned char)));
	size_t digest_len = BIO_read(bmem, static_cast<void*>(digest), static_cast<int>(length));

	BIO_free_all(bmem);

	digest = static_cast<unsigned char*>(realloc(digest, (digest_len * 2 + 1) * sizeof(unsigned char)));
	for (int i = digest_len - 1; i >= 0; i--)
	{
		digest[i * 2 + 1] = get_char(digest[i] & 0x0F);
		digest[i * 2] = get_char((digest[i] >> 4) & 0x0F);
	}
	digest[digest_len * 2] = 0;

	return reinterpret_cast<char*>(digest);
}

char* format(const char *message, ...)
{
	size_t size = 128;
	char *buffer = nullptr;

	while (1)
	{
		buffer = static_cast<char*>(realloc(buffer, size * sizeof(char)));
		if (buffer == nullptr)
			exit(EXIT_FAILURE);

		va_list ap;
		va_start(ap, message);

		size_t copied = vsnprintf(buffer, size, message, ap);

		va_end(ap);

		if (copied < size)
			return buffer;

		size = copied + 1;
	}
}

wchar_t* strdup_utf(const char *src)
{
	size_t size = mbstowcs(nullptr, src, 0);
	if (size == static_cast<size_t>(-1))
		return nullptr;

	size++;

	wchar_t *dest = static_cast<wchar_t*>(malloc(size * sizeof(wchar_t)));
	size_t length = mbstowcs(dest, src, size);
	dest[length] = L'\0';

	return dest;
}

size_t strlen_utf(const char *src)
{
	size_t len = mbstowcs(nullptr, src, 0);
	if (len == static_cast<size_t>(-1))
		return 0;

	return len;
}

string utf_to_ncr(const char *text)
{
	char *cur_locale = setlocale(LC_CTYPE, nullptr);
	setlocale(LC_CTYPE, config()->LOCALE);

	string result;

	wchar_t *text_utf = strdup_utf(text);
	if (text_utf == nullptr)
		return result;

	size_t length_utf = wcslen(text_utf);

	for (size_t i = 0; i < length_utf; i++)
	{
		wchar_t sym = text_utf[i];

		if (sym <= 0x7F)
		{
			result += static_cast<char>(sym);
			continue;
		}

		result += "&#" + lexical_cast<string>(static_cast<unsigned int>(sym)) + ";";
	}

	free(text_utf);

	setlocale(LC_CTYPE, cur_locale);

	return result;
}

string escape(const char *text)
{
	string result;

	size_t length = strlen(text);

	for (size_t i = 0; i < length; i++)
	{
		char sym = text[i];

		if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || (sym >= '0' && sym <= '9') || sym == '-' || sym == '.' || sym == '_' || sym == '~')
			result += static_cast<char>(sym);
		else
			result += string("%") + get_char((sym >> 4) & 0x0F) + get_char(sym & 0x0F);
	}

	return result;
}

// Русский алфавит Ё, ё, А-я
inline static bool allowed_symbol(uint32_t symbol)
{
	return (symbol == 0xD081 || symbol == 0xD191 || (symbol >= 0xD090 && symbol <= 0xD18F));
}

inline static bool allowed_byte(uint8_t byte)
{
	return (byte == ' ' || byte == '(' || byte == ')' || (byte >= '0' && byte <= '9') || (byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z'));
}

inline static void save_symbol(const char *buffer, char *&result, uint8_t length)
{
	if (length == 0)
		return;

	uint32_t symbol = 0;
	for (uint8_t j = length; j > 0; j--)
	{
		symbol <<= 8;
		symbol |= *reinterpret_cast<const uint8_t*>(buffer - j);
	}

	if (!allowed_symbol(symbol))
		return;

	for (uint8_t j = length; j > 0; j--)
	{
		*result = *(buffer - j);
		result++;
	}
}

inline static void trim(char *buffer)
{
	char *start = buffer;
	char *p = buffer;

	while (*p == ' ')
		p++;

	while (*p != '\0')
		*buffer++ = *p++;

	*buffer = '\0';

	if (*start == '\0')
		return;

	while (*--buffer == ' ')
		*buffer = '\0';
}

char* strdup_clean(const char *buffer)
{
	size_t buffer_length = strlen(buffer);

	const char *buffer_end = buffer + buffer_length;

	char *result_begin = static_cast<char*>(malloc(buffer_length + 1));
	char *result = result_begin;

	uint8_t symbol_length = 0;

	for (; buffer != buffer_end; buffer++)
	{
		uint8_t current_symbol = *buffer;

		if (current_symbol < 0x80)
		{
			save_symbol(buffer, result, symbol_length);

			if (allowed_byte(current_symbol))
			{
				*result = *buffer;
				result++;
			}

			symbol_length = 0;
			continue;
		}

		if (current_symbol >= 0xC0)
		{
			save_symbol(buffer, result, symbol_length);

			symbol_length = 1;
			continue;
		}

		symbol_length++;
	}

	save_symbol(buffer, result, symbol_length);
	*result = '\0';

	trim(result_begin);

	if (*result_begin != '\0')
		return result_begin;

	free(result_begin);
	return strdup("Без имени");
}

string join(const std::vector<uint64_t> *values)
{
	string joined = "";

	for (auto iter = values->begin(); iter != values->end(); ++iter)
	{
		if (iter != values->begin())
			joined += ",";
		joined += lexical_cast<string>(*iter);
	}

	return joined;
}

struct tm localtime_threadsafe(time_t timestamp)
{
	struct tm result;
	localtime_r(&timestamp, &result);
	return result;
}

struct tm gmtime_threadsafe(time_t timestamp)
{
	struct tm result;
	gmtime_r(&timestamp, &result);
	return result;
}

std::string get_trace()
{
	char pid_buf[32] = {0};
	snprintf(pid_buf, 32, "%d", getpid());

	char thread_buf[64] = {0};
	snprintf(thread_buf, 64, "thread %lu", pthread_self());

	int link[2];
	if (pipe(link) == -1)
		return "";

	fcntl(link[0], F_SETPIPE_SZ, 1024 * 1024);
	fcntl(link[1], F_SETPIPE_SZ, 1024 * 1024);

	int child_pid = fork();
	if (child_pid == -1)
		return "";

	if (child_pid != 0)
	{
		close(link[1]);

		string ret;

		char *buffer = static_cast<char*>(malloc(64 * 1024));

		while (true)
		{
			int readed = read(link[0], buffer, 64 * 1024);
			if (readed == -1)
				return "";
			if (readed == 0)
				break;

			buffer[readed] = '\0';

			ret += string(buffer);
		}

		waitpid(child_pid, NULL, 0);

		free(buffer);

		close(link[0]);

		return ret;
	}

	close(link[0]);

	dup2(link[1], STDOUT_FILENO);
	dup2(link[1], STDERR_FILENO);

//	execl("/bin/ls", "/", NULL);
	execl("/usr/bin/gdb", "/usr/bin/gdb", "--batch", "-n", "--pid", pid_buf, "-ex", thread_buf, "-ex", "bt full", NULL);
	exit(EXIT_FAILURE);
}