#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class FooSubscriberClearQ : public EventSubscriber
	{

	public:

		GameTime timer;
		EventQueue* q;

		FooSubscriberClearQ() = delete;

		FooSubscriberClearQ(EventQueue& queue) :
			q(&queue)
		{

		}


		~FooSubscriberClearQ()
		{
			Event<FooMessage>::unSubscribe(*this);
		}

		void Notify(const EventPublisher& publisher)
		{
			if (publisher.Is(Event<FooMessage>::TypeIdClass()))
			{
				q->Clear();
			}
		}
	};
}