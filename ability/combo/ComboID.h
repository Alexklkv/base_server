#pragma once

struct ComboID
{
private:
	static const ComboID INVALID;

public:
	const uint32_t id;

	explicit ComboID(uint32_t id);
	ComboID(const ComboID &other);
	ComboID(ComboID &&other);

	bool valid() const;

	bool operator== (const ComboID &other) const;
	bool operator!= (const ComboID &other) const;
	bool operator< (const ComboID &other) const;

	static ComboID invalid();
};