#pragma once

#include "Updatable.h"

#include <type_traits>

template<typename Owner>
class Owned : public Updatable
{
protected:
	typedef Owner* owner_ptr;
	typedef const Owner* const_owner_ptr;

	owner_ptr parent()
	{
		return static_cast<owner_ptr>(this->owner);
	}
	const_owner_ptr parent() const
	{
		return static_cast<const_owner_ptr>(this->owner);
	}

public:
	explicit Owned(Owner *owner): Updatable(owner)
	{}
	virtual ~Owned()
	{}
};