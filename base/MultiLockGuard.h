#pragma once

#include <mutex>
#include <tuple>

template<class ...Mutexes>
class MultiLockGuard
{
public:
	typedef std::tuple<Mutexes&...> mutexes_t;
	mutexes_t mutexes;

	MultiLockGuard(Mutexes &...mutexes):
		mutexes(mutexes...)
	{
		std::lock(mutexes...);
	}

	~MultiLockGuard() noexcept
	{
		this->unlock();
	}

private:
	inline void unlock() noexcept
	{
		constexpr size_t last = std::tuple_size<mutexes_t>::value - 1;
		Unlocker<last, mutexes_t>::unlock(this->mutexes);
	}

	template<size_t index, class M>
	struct Unlocker
	{
		inline static void unlock(M &mutexes) noexcept
		{
			std::get<index>(mutexes).unlock();
			Unlocker<index - 1, mutexes_t>::unlock(mutexes);
		}
	};

	template<class M>
	struct Unlocker<0, M>
	{
		inline static void unlock(M &mutexes) noexcept
		{
			std::get<0>(mutexes).unlock();
		}
	};
};