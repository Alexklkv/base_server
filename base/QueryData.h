#pragma once

#include "NoCopy.h"

#include <string>

#include <libxml/tree.h>
#include <libxml/xpath.h>

class QueryData : private NoCopy
{
private:
	xmlDoc *doc;
	xmlXPathContext *xpath_context;

	char* get_content(const char *xpath) const;

public:
	QueryData();
	~QueryData();

	uint32_t get_uint32(const char *xpath) const;
	void get_string(const char *xpath, std::string &result) const;

	void load(const char *buffer, size_t size);
};