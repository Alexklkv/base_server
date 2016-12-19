#pragma once

#include "NoCopy.h"

#include <vector>

namespace client
{

class Group;

struct ReaderData
{
	enum Type : uint8_t
	{
		TYPE_STRING,
		TYPE_LONG,
		TYPE_FLOAT,
		TYPE_INT,
		TYPE_WORD,
		TYPE_BYTE,
		TYPE_GROUP,
		TYPE_BYTEARRAY
	};

	union
	{
		uint8_t B;
		uint16_t W;
		uint32_t I;
		float F;
		uint64_t L;
		const char *S;
		Group *G;
		const uint8_t *A;
	};

	Type type;

	ReaderData(const char *data);
	ReaderData(float data);
	ReaderData(uint64_t data);
	ReaderData(uint32_t data);
	ReaderData(uint16_t data);
	ReaderData(uint8_t data);
	ReaderData(Group *data);
	ReaderData(const uint8_t *data);

	void release();
};

class Reader : private NoCopy
{
private:
	std::vector<ReaderData> data;

public:
	virtual ~Reader();

	bool has(size_t size) const;
	size_t length() const;

	template<class T> void add(T data);

	inline const char* S(size_t index) const {return this->data[index].S;}
	inline float F(size_t index) const {return this->data[index].F;}
	inline uint64_t L(size_t index) const {return this->data[index].L;}
	inline uint32_t I(size_t index) const {return this->data[index].I;}
	inline uint16_t W(size_t index) const {return this->data[index].W;}
	inline uint8_t B(size_t index) const {return this->data[index].B;}
	inline const Group& G(size_t index) const {return *this->data[index].G;}
	inline const uint8_t* A(size_t index) const {return this->data[index].A;}
};

template<class T> void Reader::add(T data)
{
	ReaderData ref(data);
	this->data.push_back(ref);
}

}