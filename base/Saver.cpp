#include "Saver.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Log.h"
#include "Savable.h"

Saver::Saver():
	Thread("Saver", config()->SAVER_SAVE_TIMEOUT)
{}

Saver::~Saver()
{
	const size_t total = this->objects.unsafe_size();
	atomic<int> count;

	count = 0;

	#pragma omp parallel
	{
		Savable *object = nullptr;
		while (this->objects.try_pop(object))
		{
			object->save();
			int current = ++count;

			if (current % 100 != 0)
				continue;

			logger()->info("%lu from %lu objects left in saver", this->objects.unsafe_size(), total);
		}
	}
}
void Saver::add(Savable *object)
{
	this->objects.push(object);
}

void Saver::on_timeout()
{
	size_t saved = 0, total = this->objects.unsafe_size();

	Savable *object;
	while (this->objects.try_pop(object))
	{
		if (!object->is_expired())
		{
			this->objects.push(object);
			break;
		}

		object->save();
		saved++;

		if (this->is_stopped())
			break;
	}

	logger()->info("Saved %lu of %lu objects", saved, total);
}