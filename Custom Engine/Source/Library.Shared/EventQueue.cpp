#include "pch.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(EventQueue);

EventQueue::EventQueue() :
	mIsUpdating(false), mClearCalled(false), mQueue(50), mTempQueue(10)
{
}

EventQueue::~EventQueue()
{
	Clear();
}

void EventQueue::Enqueue(EventPublisher& publisher, GameTime& time, const milliseconds* delay)
{
	if(delay == nullptr)
		publisher.SetTime(time.CurrentTime(), 0);
	else
		publisher.SetTime(time.CurrentTime(), delay);

	if (mIsUpdating)
	{
		lock_guard<mutex> lock(mMutex);
		mTempQueue.PushBack(&publisher);
	}
	else
		mQueue.PushBack(&publisher);
}

void EventQueue::Send(EventPublisher& publisher)
{
	publisher.Deliver(); 
}

void EventQueue::Update(const GameTime& time)
{
	mIsUpdating = true;
	std::chrono::time_point<std::chrono::steady_clock> curTime = time.CurrentTime();
	EventPublisher* curEvent;

	vector<future<void>> futures;
	Vector<EventPublisher*> expired;

	// Move Events In Temp Queue To Main Queue
	if (!mTempQueue.isEmpty())
	{
		lock_guard<mutex> lock(mMutex);
		for (std::int32_t i = (std::int32_t)mTempQueue.Size() - 1; i >= 0; --i)
		{
			mQueue.PushBack(mTempQueue[i]);
			mTempQueue[i] = nullptr;
			mTempQueue.PopBack();
		}
	}

	// Send Expired Events In Main Queue
	for (std::uint32_t i = 0; i < mQueue.Size(); ++i)
	{
		if (mQueue[i]->isExpired(curTime))
		{
			{
				lock_guard<mutex> lock(mMutex);
				curEvent = mQueue[i];
				mQueue.Remove(curEvent);
			}
			expired.PushBack(curEvent);
			--i;

			futures.emplace_back(async(launch::async, [=]()
			{
				Send(*curEvent);
			}));
		}
	}

	// Wait For Events To Finish Before Deleting
	for (auto& f : futures)
	{
		try
		{
			f.get();
		}
		catch (exception ex)
		{
			mIsUpdating = false;
			mClearCalled = false;
			Clear();
			ClearExpired(&expired);
			
			throw std::exception(ex.what());
		}
	}

	// Delete Expired Events
	ClearExpired(&expired);

	mIsUpdating = false;

	// Clear If Clear() Was Called During Update
	if (mClearCalled == true)
	{
		mClearCalled = false;
		Clear();
	}
}

void EventQueue::Clear()
{
	if (mIsUpdating)
	{
		mClearCalled = true;
	}

	else
	{
		lock_guard<mutex> lock(mMutex);

		for (std::int32_t i = (std::int32_t)mTempQueue.Size() - 1; i >= 0; --i)
		{
			delete mTempQueue[i];
			mTempQueue.PopBack();
		}

		for (std::int32_t i = (std::int32_t)mQueue.Size() - 1; i >= 0; --i)
		{
			delete mQueue[i];
			mQueue.PopBack();
		}
	}
}

void EventQueue::ClearExpired(Vector<EventPublisher*>* expired)
{
	for (std::int32_t i = (std::int32_t)expired->Size() - 1; i >= 0; --i)
	{
		delete expired->At(i);
		expired->PopBack();
	}
}

bool EventQueue::isEmpty()
{
	lock_guard<mutex> lock(mMutex);
	return mQueue.isEmpty() && mTempQueue.isEmpty();
}

std::uint32_t EventQueue::Size()
{
	lock_guard<mutex> lock(mMutex);
	return mQueue.Size() + mTempQueue.Size();
}