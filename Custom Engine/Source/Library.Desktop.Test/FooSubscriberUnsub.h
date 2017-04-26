#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class FooSubscriberUnsub : public EventSubscriber
	{

	public:

		GameTime timer;

		FooSubscriberUnsub() = default;

		~FooSubscriberUnsub()
		{
			Event<FooMessage>::unSubscribe(*this);
		}

		void Notify(const EventPublisher& publisher)
		{
			if (publisher.Is(Event<FooMessage>::TypeIdClass()))
			{
				Event<FooMessage>::UnSubscribeAll();
			}
		}
	};
}