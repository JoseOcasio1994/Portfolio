#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class EventQueue : public RTTI
	{

		RTTI_DECLARATIONS(EventQueue, RTTI);

	private:

		typedef std::chrono::milliseconds milliseconds;

		Vector<EventPublisher*> mQueue;
		Vector<EventPublisher*> mTempQueue;
		mutex mMutex;
		bool mIsUpdating, mClearCalled;

		void ClearExpired(Vector<EventPublisher*>* expired);

	public:

		EventQueue();
		~EventQueue();

		EventQueue(const EventQueue& rhs) = delete;
		EventQueue(EventQueue&& rhs) = delete;

		EventQueue& operator=(const EventQueue& rhs) = delete;
		EventQueue& operator=(EventQueue&& rhs) = delete;

		/* Add An Event To A Singleton Event Queue. Events must be on the heap.
		@param publisher the event to enqueue
		@param time a GameTime& to check the current time
		@param delay an optional time in milliseconds to delay the event
		*/
		void Enqueue( EventPublisher& publisher, GameTime& time, const milliseconds* delay = nullptr);

		/* Send a message to all subscribers subscribed to this publisher
		@param publisher the event to send out
		*/
		void Send(EventPublisher& publisher);

		/* Send any expired events
		@param time GameTime& used to get the current time to check for expired events
		*/
		void Update(const GameTime& time);

		/* Clear the queue while sending expired events
		@param time GameTime& used to get the current time to check for expired events
		*/
		void Clear();

		/* Return if the Queue is empty
		@return if the queue is empty
		*/
		bool isEmpty();

		/* Return size of the Queue
		@return the size of the queue
		*/
		std::uint32_t Size();
	};
}