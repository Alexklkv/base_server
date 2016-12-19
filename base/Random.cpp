#include "Random.h"

Random::Random()
{}

// distribution [0, std::numeric_limits<uint32_t>::max()]
uint32_t Random::uint() noexcept
{
	uint_distribution_t distribution;
	return distribution(engine);
}

// distribution [0, max)
uint32_t Random::uint(uint32_t max) noexcept
{
	if (max <= 1)
		return 0;

	uint_distribution_t distribution(0, max - 1);
	return distribution(engine);
}

// distribution [min, max)
uint32_t Random::uint(uint32_t min, uint32_t max) noexcept
{
	if (max <= min + 1)
		return min;

	uint_distribution_t distribution(min, max - 1);
	return distribution(engine);
}

// distribution [0.0f, 1.0f]
float Random::real() noexcept
{
	real_distribution_t distribution(0.0f, 1.0f);
	return distribution(engine);
}

// distribution [0, max]
float Random::real(float max) noexcept
{
	if (max <= 0.0f)
		return 0.0f;

	real_distribution_t distribution(0.0f, max);
	return distribution(engine);
}

// distribution [min, max]
float Random::real(float min, float max) noexcept
{
	if (max <= min)
		return min;

	real_distribution_t distribution(min, max);
	return distribution(engine);
}

// distribution [false, true]
bool Random::chance(float percents) noexcept
{
	if (percents <= 0.0f)
		return false;

	if (percents >= 100.0f)
		return true;

	return percents >= Random::real(100.0f);
}

thread_local Random::engine_t Random::engine = engine_t(random());