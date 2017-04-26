#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	template <class T>
	class Event : public EventPublisher
	{

		RTTI_DECLARATIONS(Event<T>, EventPublisher);

	private:

		T* mMessage;
		static mutex mMutex;

	public:

		static Vector<EventSubscriber*> mSubscribers;

		Event() = delete;

		/*Constructor. Takes A Message Argument that is the event object to send to subscribers
		*/
		Event( T& message);
		virtual ~Event();

		/* Copy / Move COnstructors
		*/
		Event(const Event& rhs);
		Event(Event&& rhs);

		/* Copy / Move Operators
		*/
		Event& operator=(const Event& rhs);
		Event& operator=(Event&& rhs);

		/* Equality Operators
		*/
		bool operator==(const Event& rhs);
		bool operator!=(const Event& rhs);

		/* Add subscriber to the list
		@param subscriber the subscriber to add
		*/
		static void Subscribe(const EventSubscriber& subscriber);

		/* Remove subscriber from the list
		@param subscriber the subscriber to remove
		*/
		static void unSubscribe(const EventSubscriber& subscriber);

		/* Remove all subscribers from the list
		*/
		static void UnSubscribeAll();

		/* Return the message/event object
		@return the message/event object
		*/
		T* Message();
	};

#include "Event.inl"
}