#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class FooSubscriberEnqueue : public EventSubscriber
	{

	public:

		GameTime timer;
		FooMessage message;
		std::chrono::milliseconds Delay = std::chrono::duration<int>(1);
		EventQueue* q;

		FooSubscriberEnqueue() = delete;

		FooSubscriberEnqueue(EventQueue& queue) :
			q(&queue)
		{

		}

		~FooSubscriberEnqueue()
		{
			Event<FooMessage>::unSubscribe(*this);
		}

		void Notify(const EventPublisher& publisher)
		{
			if (publisher.Is(Event<FooMessage>::TypeIdClass()))
			{
				q->Enqueue(*new Event<FooMessage>(message), timer, &Delay);
			}
		}
	};
}