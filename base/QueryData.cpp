#include "QueryData.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Log.h"

QueryData::QueryData():
	doc(nullptr), xpath_context(nullptr)
{}

QueryData::~QueryData()
{
	if (this->xpath_context != nullptr)
		xmlXPathFreeContext(xpath_context);
	if (this->doc != nullptr)
		xmlFreeDoc(doc);
}

char* QueryData::get_content(const char *xpath) const
{
	if (this->xpath_context == nullptr)
		return nullptr;

	xmlXPathObject *xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath), this->xpath_context);
	if (xpathObj == nullptr)
	{
		logger()->warning("Failed to evaluate XPath expression");
		return nullptr;
	}

	xmlNodeSet *nodes = xpathObj->nodesetval;

	if (nodes == nullptr || nodes->nodeNr != 1)
	{
		xmlXPathFreeObject(xpathObj);
		return nullptr;
	}

	char *content = reinterpret_cast<char*>(xmlNodeGetContent(nodes->nodeTab[0]));

	xmlXPathFreeObject(xpathObj);

	return content;
}

uint32_t QueryData::get_uint32(const char *xpath) const
{
	char *content = this->get_content(xpath);
	if (content == nullptr)
		return 0;

	uint32_t value = atoi(content);

	xmlFree(content);

	return value;
}

void QueryData::get_string(const char *xpath, std::string &result) const
{
	char *content = this->get_content(xpath);

	result.clear();

	if (content == nullptr)
		return;

	result = content;

	xmlFree(content);
}

void QueryData::load(const char *buffer, size_t size)
{
	this->doc = xmlReadMemory(buffer, size, "answer", nullptr, 0);

	if (this->doc == nullptr)
	{
		logger()->warning("Failed to parse XML '%s'", buffer);
		return;
	}

	this->xpath_context = xmlXPathNewContext(this->doc);
	if (this->xpath_context == nullptr)
	{
		logger()->warning("Failed to create XPath context");
		return;
	}
}