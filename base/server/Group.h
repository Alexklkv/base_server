#pragma once

#include "Writer.h"

namespace server
{

class Group : public Writer
{
private:
	uint16_t length;

public:
	Group();

	void next();
	uint16_t get_length() const;
};

}