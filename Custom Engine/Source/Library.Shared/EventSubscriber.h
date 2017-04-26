#pragma once
#include "pch.h"
#include <cstdint>

using namespace std;

namespace FieaGameEngine
{
	class EventPublisher;

	class EventSubscriber
	{

	protected:

		mutable mutex mMutex;

	public:

		/* Pure Virtual. React To A Received Event.
		@param publisher a relatable event to check and possibly react to
		*/
		virtual void Notify(const EventPublisher& publisher) = 0;

	};
}