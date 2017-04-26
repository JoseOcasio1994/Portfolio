#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class FooSubscriber : public EventSubscriber
	{

	public:

		int fooInt;

		FooSubscriber() :
			fooInt(0)
		{

		}

		~FooSubscriber()
		{
			Event<FooMessage>::unSubscribe(*this);
		}

		void Notify(const EventPublisher& publisher)
		{
			if (publisher.Is(Event<FooMessage>::TypeIdClass()))
			{
				++fooInt;
			}
		}
	};
}