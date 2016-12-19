#pragma once

#include "Enum.h"

#include <array>

template<class Type, class Enumerator, typename = typename std::is_enum<Enumerator>::type>
struct strict_array : public std::array<Type, static_cast<size_t>(Enumerator::MAX)>
{
	typedef std::array<Type, static_cast<size_t>(Enumerator::MAX)> super;
	typedef strict_array<Type, Enumerator> current;

public:
	typedef typename super::reference reference;
	typedef typename super::const_reference const_reference;
	typedef typename super::size_type size_type;

	strict_array()
	{
		this->fill(Type());
	}

	strict_array(std::initializer_list<Type> values):
		strict_array()
	{
		std::copy(values.begin(), values.end(), this->begin());
	}

	inline reference operator[](Enumerator index) noexcept
	{
		return super::operator[](static_cast<size_type>(index));
	}

	constexpr inline const_reference operator[](Enumerator index) const noexcept
	{
		return super::operator[](static_cast<size_type>(index));
	}

	inline reference operator[](size_type index) noexcept
	{
		return super::operator[](index);
	}

	inline constexpr const_reference operator[](size_type index) const noexcept
	{
		return super::operator[](index);
	}

	inline reference at(Enumerator index)
	{
		return super::at(static_cast<size_type>(index));
	}

	constexpr const_reference at(Enumerator index) const
	{
		return super::at(static_cast<size_type>(index));
	}

	inline reference at(size_type index)
	{
		return super::at(index);
	}

	constexpr const_reference at(size_type index) const
	{
		return super::at(index);
	}
};