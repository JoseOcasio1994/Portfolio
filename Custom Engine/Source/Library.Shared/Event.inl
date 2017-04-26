
template <class T>
RTTI_DEFINITIONS(Event<T>);

template <class T>
Vector<EventSubscriber*> Event<T>::mSubscribers;

template <class T>
mutex Event<T>::mMutex;

#pragma region CONSTRUCTORS 

template <class T>
Event<T>::Event(T& message) :
	EventPublisher(mSubscribers, mMutex), mMessage(&message)
{
}

template <class T>
Event<T>::~Event()
{
	if (this->Is(Event<EventMessage>::TypeIdClass()))
		delete Message();
}

template <class T>
Event<T>::Event(const Event& rhs) :
	EventPublisher(rhs), mMessage(rhs.mMessage)
{
}

template <class T>
Event<T>::Event(Event&& rhs) :
	EventPublisher(std::move(rhs)), mMessage(rhs.mMessage)
{
	rhs.mMessage = nullptr;
}

template <class T>
Event<T>& Event<T>::operator=(const Event& rhs)
{
	if(this != &rhs)
	{
		EventPublisher::operator=(rhs);
		mMessage = rhs.mMessage;
	}

	return *this;
}

template <class T>
Event<T>& Event<T>::operator=(Event&& rhs)
{
	if(this != &rhs)
	{
		EventPublisher::operator=(std::move(rhs));
		mMessage = rhs.mMessage;

		rhs.mMessage = nullptr;
	}

	return *this;
}

template <class T>
bool Event<T>::operator==(const Event& rhs)
{
	return (EventPublisher::operator==(rhs) && mMessage == rhs.mMessage);
}

template <class T>
bool Event<T>::operator!=(const Event& rhs)
{
	return (EventPublisher::operator!=(rhs) || mMessage != rhs.mMessage);
}

#pragma endregion

#pragma region METHODS

template <class T>
void Event<T>::Subscribe(const EventSubscriber& subscriber)
{
	lock_guard<mutex> lock(mMutex);
	if(mSubscribers.Find(const_cast<EventSubscriber*>(&subscriber)) == mSubscribers.end())
		mSubscribers.PushBack(const_cast<EventSubscriber*>(&subscriber));
}

template <class T>
void Event<T>::unSubscribe(const EventSubscriber& subscriber)
{
	lock_guard<mutex> lock(mMutex);
	mSubscribers.Remove(const_cast<EventSubscriber*>(&subscriber));
}

template <class T>
void Event<T>::UnSubscribeAll()
{
	std::uint32_t size = mSubscribers.Size();

	if(size != 0)
	{
		lock_guard<mutex> lock(mMutex);
		for (std::uint32_t i = size - 1; i > 0; --i)
		{
			mSubscribers[i] = nullptr;
			mSubscribers.PopBack();
		}

		mSubscribers[0] = nullptr;
		mSubscribers.PopBack();
	}
}

template <class T>
T* Event<T>::Message()
{
	return mMessage;
}

#pragma endregion