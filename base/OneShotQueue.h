#pragma once

#include "NoCopy.h"

#include <list>
#include <queue>

template<typename T>
class OneShotQueue : private NoCopy, private std::queue<T, std::list<T>>
{
public:
	OneShotQueue()
	{}

	OneShotQueue(OneShotQueue &&other) = delete;

	using std::queue<T, std::list<T>>::push;
	using std::queue<T, std::list<T>>::empty;
	using std::queue<T, std::list<T>>::swap;

	T pop()
	{
		T &tmp_ref = this->front();
		T tmp_move = std::move(tmp_ref);
		this->std::queue<T, std::list<T>>::pop();
		return std::move(tmp_move);
	}

	void clear()
	{
		OneShotQueue<T> tmp;
		this->swap(tmp);
	}
};