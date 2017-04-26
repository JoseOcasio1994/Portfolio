#include "pch.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ReactionAttributed);
HashMap<std::string, Factory<ReactionAttributed>& >  Factory<ReactionAttributed>::mFactories;

ReactionAttributed::ReactionAttributed() :
	mSubtype(nullptr)
{
	Event<EventMessage>::Subscribe(*this);

	AddInternalAttribute(SubtypeKey, "Unknown", 1);
	mSubtype = Find(SubtypeKey);
}

void ReactionAttributed::AddSubtype(const std::string& type)
{
	if(mSubtype->Get<std::string>() == "Unknown")
		mSubtype->Set(type);
	else
		mSubtype->Pushback(type);
}

Datum* ReactionAttributed::GetSubtypes() const
{
	return mSubtype;
}

void ReactionAttributed::Notify(const EventPublisher& publisher)
{
	Event<EventMessage>* event = publisher.As<Event<EventMessage>>();

	if (event != nullptr)
	{
		EventMessage* message = event->Message();

		for (std::uint32_t i = 0; i < mSubtype->Size(); ++i)
		{
			if (mSubtype->Get<std::string>(i) == message->Subtype())
			{
				std::pair<std::string, Datum>* pair;
				for (std::uint32_t j = 0; j < message->Size(); ++j)
				{
					pair = message->GetPair(j);
					Append(pair->first) = pair->second;
				}

				Update(message->GetWorld().GetWorldState());
				break;
			}
		}

	}
}