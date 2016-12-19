#pragma once

#include <random>

class Random
{
public:
	typedef std::uniform_int_distribution<uint32_t> uint_distribution_t;
	typedef std::uniform_real_distribution<float> real_distribution_t;
	typedef std::mt19937 engine_t;

private:
	Random();
	thread_local static engine_t engine;

public:

	static uint32_t uint() noexcept;
	static uint32_t uint(uint32_t max) noexcept;
	static uint32_t uint(uint32_t min, uint32_t max) noexcept;

	static float real() noexcept;
	static float real(float max) noexcept;
	static float real(float min, float max) noexcept;

	static bool chance(float percents) noexcept;

	template<class Container, class Type>
	static Type item(const Container &items, const Type &invalid) noexcept
	{
		size_t count = items.size();

		if (count == 0)
			return invalid;

		return *std::next(items.begin(), Random::uint(count));
	}

	template<class Index = uint32_t, class Weights>
	static Index weighted(const Weights &weights, Index incorrect);

	template<class Index = uint32_t, class Weights>
	static Index fixed_weighted(const Weights &weights, float summary_weight, Index incorrect);
};

template<class Index, class Weights>
Index Random::weighted(const Weights &weights, Index incorrect)
{
	if (std::begin(weights) == std::end(weights))
		return incorrect;

	float summary_weight = 0.0f;

	for (auto &chance : weights)
		summary_weight += chance;

	return fixed_weighted(weights, summary_weight, incorrect);
}

template<class Index, class Weights>
Index Random::fixed_weighted(const Weights &weights, float summary_weight, Index incorrect)
{
	if (std::begin(weights) == std::end(weights) || summary_weight <= 0.0f)
		return incorrect;

	Index item = incorrect;
	size_t index = 0;

	float current_chance = real(summary_weight);

	for (auto &chance : weights)
	{
		if (current_chance <= chance)
		{
			item = static_cast<Index>(index);
			break;
		}

		current_chance -= chance;
		index++;
	}

	return item;
}