#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class FooSubscriberSub : public EventSubscriber
	{

	public:

		GameTime timer;
		Vector<FooSubscriber*> subs;

		FooSubscriberSub() = default;

		~FooSubscriberSub()
		{
			for (std::uint32_t i = 0; i < subs.Size(); ++i)
			{
				Event<FooMessage>::unSubscribe(*subs[i]);
				delete subs[i];
			}

			Event<FooMessage>::unSubscribe(*this);
		}

		void Notify(const EventPublisher& publisher)
		{
			if (publisher.Is(Event<FooMessage>::TypeIdClass()))
			{
				subs.PushBack(new FooSubscriber());
				Event<FooMessage>::Subscribe(*subs.Back());
			}
		}
	};
}