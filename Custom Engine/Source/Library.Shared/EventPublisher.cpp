#include "pch.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(EventPublisher);

#pragma region CONSTRUCTORS

EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscribers, mutex& curMutex) :
	mCurSubscribers(&subscribers), mTime(timePair(timePoint(), milliseconds(0))),
	mCurMutex(&curMutex)
{
}

EventPublisher::EventPublisher(const EventPublisher& rhs) :
	mCurSubscribers(rhs.mCurSubscribers), mTime(rhs.mTime), mCurMutex(rhs.mCurMutex)
{
}

EventPublisher::EventPublisher(EventPublisher&& rhs) :
	mCurSubscribers(rhs.mCurSubscribers), mTime(rhs.mTime), mCurMutex(rhs.mCurMutex)
{
	rhs.mCurSubscribers = nullptr;
	rhs.mTime.first = timePoint();
	rhs.mTime.second = milliseconds(0);
	rhs.mCurMutex = nullptr;
}

EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
{
	if( this != &rhs)
	{
		mCurSubscribers = rhs.mCurSubscribers;
		mTime = rhs.mTime;
		mCurMutex = rhs.mCurMutex;
	}

	return *this;
}

EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
{
	if(this != &rhs)
	{
		mCurSubscribers = rhs.mCurSubscribers;
		mTime = rhs.mTime;
		mCurMutex = rhs.mCurMutex;

		rhs.mCurSubscribers = nullptr;
		rhs.mTime.first = timePoint();
		rhs.mTime.second = milliseconds(0);
		rhs.mCurMutex = nullptr;
	}

	return *this;
}

bool EventPublisher::operator==(const EventPublisher& rhs)
{
	return (mCurSubscribers == rhs.mCurSubscribers && mTime == rhs.mTime);
}

bool EventPublisher::operator!=(const EventPublisher& rhs)
{
	return !operator==(rhs);
}

#pragma endregion

#pragma region METHODS

void EventPublisher::SetTime(const timePoint& curTime, const milliseconds* delay)
{
	mTime.first = curTime;

	if (delay != nullptr)
		mTime.second = *delay;
	else
		mTime.second = milliseconds(0);
}

EventPublisher::timePoint EventPublisher::TimeEnqueued()
{
	return mTime.first;
}

EventPublisher::milliseconds EventPublisher::Delay()
{
	return mTime.second;
}

bool EventPublisher::isExpired(const timePoint curTime)
{
	return (curTime >= (mTime.first + mTime.second));
}

void EventPublisher::Deliver()
{
	vector<future<void>> futures;

	{
		lock_guard<mutex> lock(*mCurMutex);
		for (std::uint32_t i = 0; i < mCurSubscribers->Size(); ++i)
		{
			futures.emplace_back(async(launch::async, [=]()
			{
				mCurSubscribers->At(i)->Notify(*this);
			}));
		}
	}

	for (auto& f : futures)
	{
		try
		{
			f.get();
		}
		catch (exception ex)
		{
			throw;
		}
	}
}

#pragma endregion