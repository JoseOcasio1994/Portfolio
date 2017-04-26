#include "pch.h"
#include <chrono>
using namespace FieaGameEngine;
RTTI_DEFINITIONS(ActionEvent);

HashMap<std::string, Factory<ActionEvent>& >  Factory<ActionEvent>::mFactories;

ActionEvent::ActionEvent() :
	mSubtype(nullptr), mDelay(nullptr)
{
	AddInternalAttribute(SubtypeKey, "Unknown", 1);
	mSubtype = Find(SubtypeKey);

	AddInternalAttribute(DelayKey, 0, 1);
	mDelay = Find(DelayKey);
}

ActionEvent::ActionEvent(std::string& type, int delay) :
	mSubtype(nullptr), mDelay(nullptr)
{
	AddInternalAttribute(SubtypeKey, type, 1);
	mSubtype = Find(SubtypeKey);

	AddInternalAttribute(DelayKey, delay, 1);
	mDelay = Find(DelayKey);
}

void ActionEvent::SetSubType(const std::string& type)
{
	mSubtype->Set(type);
}

std::string ActionEvent::GetSubType()
{
	return mSubtype->Get<std::string>();
}

void ActionEvent::SetDelay(std::int32_t delay)
{
	mDelay->Set(delay);
}

std::int32_t ActionEvent::GetDelay()
{
	return mDelay->Get<std::int32_t>();
}

void ActionEvent::Update(WorldState& state)
{
	state.mAction = this;

	Event<EventMessage>* event = new Event<EventMessage>(*new EventMessage());
	EventMessage* message = event->Message();
	message->SetWorld(*state.mWorld);
	message->SetSubtype(mSubtype->Get<std::string>());

	// This And Name Not Marked As Prescribed?
	for (std::uint32_t i = AuxiliaryBegin() + 2; i < mSize; ++i)
	{
		PairType* pair = GetPair(i);
		message->Append(pair->first) = pair->second;
	}

	if (message->Size() != 0)
	{
		milliseconds ms = std::chrono::duration<std::int32_t>(mDelay->Get<std::int32_t>());
		state.mWorld->GetEventQueue()->Enqueue(*event, *state.GetGameTime(), &(ms /= 1000));
	}
}