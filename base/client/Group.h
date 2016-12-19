#pragma once

#include "NoCopy.h"
#include "Reader.h"

#include <vector>

namespace client
{

class GroupData : public Reader
{};

class Group : private NoCopy
{
private:
	std::vector<GroupData*> blocks;

public:
	Group();
	~Group();

	size_t size() const;

	template<class T> void add(T value);

	void next();

	const GroupData* operator[](size_t index) const;
	const GroupData* at(size_t index) const;
	const GroupData* last() const;
};

template<class T> void Group::add(T value)
{
	GroupData *data = this->blocks.back();
	data->add(value);
}

}