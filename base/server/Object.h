#pragma once

namespace server
{

class Writer;

struct Object
{
	Object();
	Object(const Object&);
	virtual ~Object();

	Object& operator= (const Object &right) = default;

	virtual void write(Writer *writer) const = 0;
};

}