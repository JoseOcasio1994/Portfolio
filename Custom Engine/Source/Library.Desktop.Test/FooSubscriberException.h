#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class FooSubscriberException : public EventSubscriber
	{

	public:

		FooSubscriberException()
		{

		}

		~FooSubscriberException()
		{
			Event<FooMessage>::unSubscribe(*this);
		}

		void Notify(const EventPublisher& publisher)
		{
			if (publisher.Is(Event<FooMessage>::TypeIdClass()))
			{
				throw std::exception("Foo Exception");
			}
		}
	};
}