#pragma once
#include "pch.h"
#include <cstdint>

using namespace std;

namespace FieaGameEngine
{
	class EventPublisher : public RTTI
	{

		RTTI_DECLARATIONS(EventPublisher, RTTI);

	protected:
		typedef std::chrono::high_resolution_clock::time_point timePoint;
		typedef std::chrono::milliseconds milliseconds;
		typedef std::pair<timePoint, milliseconds> timePair;

		Vector<EventSubscriber*>* mCurSubscribers;
		timePair mTime;
		mutex* mCurMutex;

	public:
		
		EventPublisher() = delete;

		/* Default Constructor Takes in a reference to a list of subscribers
		@param subscribers the list of subscribers to receive this event
		*/
		explicit EventPublisher(Vector<EventSubscriber*>& subscribers, mutex& curMutex);
		virtual ~EventPublisher() = default;

		/* Copy / Move Constructors
		*/
		EventPublisher(const EventPublisher& rhs);
		EventPublisher(EventPublisher&& rhs);

		/* Copy / Move Assignment Operators
		*/
		EventPublisher& operator=(const EventPublisher& rhs);
		EventPublisher& operator=(EventPublisher&& rhs);

		/* Equality Operators
		*/
		bool operator==(const EventPublisher& rhs);
		bool operator!=(const EventPublisher& rhs);

		/* Set the time this event was created and an optional delay to be sent
		@param curTime chrono timepoint& used to get the current time
		@param delay optional time in milliseconds to delay the sending of this event
		*/
		void SetTime(const timePoint& curTime, const milliseconds* delay = nullptr);

		/* Return the time event was created / enqueued
		@return the time event was created / enqueued
		*/
		timePoint TimeEnqueued();

		/* Return the time delay of this event
		@return the time delay of this event
		*/
		milliseconds Delay();

		/* Return if this event expired (current time > created time + delay)
		@return if this event expired (current time > created time + delay)
		*/
		bool isExpired(const timePoint curTime);

		/* Notify all subscribers of this event
		*/
		void Deliver();

	};
}