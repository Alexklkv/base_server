//aKolk пока что пустой класс будет заполнен в 16.12.2016
#pragma once

#include "NoCopy.h"
#include "enums.h"
#include <array>

class Pointers : private NoCopy
{
	
private:
	std::array<uint16_t, PointerID::POINTER_MAX_ID> pointers;

public:
	Pointers();

	uint16_t get(PointerID point) const;
	void set(PointerID point, uint16_t value);
};