#pragma once

class NoCopy
{
private:
	NoCopy(const NoCopy &) = delete;
	void operator=(const NoCopy &) = delete;

public:
	NoCopy();
	virtual ~NoCopy();
};