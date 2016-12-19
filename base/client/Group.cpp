#include "Group.h"

namespace client
{

Group::Group()
{}

Group::~Group()
{
	for (auto iter : this->blocks)
		delete iter;
}

size_t Group::size() const
{
	return this->blocks.size();
}

void Group::next()
{
	GroupData *data = new GroupData;
	this->blocks.push_back(data);
}

const GroupData* Group::operator[](size_t index) const
{
	return this->blocks[index];
}

const GroupData* Group::at(size_t index) const
{
	return this->blocks[index];
}

const GroupData* Group::last() const
{
	return this->blocks.back();
}

}