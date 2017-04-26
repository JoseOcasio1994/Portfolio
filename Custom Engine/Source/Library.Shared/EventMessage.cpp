#include "pch.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(EventMessage);

EventMessage::EventMessage() :
	mSubtype(""), mWorld(nullptr)
{

}

EventMessage::EventMessage(std::string& type, World* world) :
	mSubtype(type), mWorld(world)
{

}

EventMessage::EventMessage(const EventMessage& rhs) :
	mSubtype(rhs.mSubtype), mWorld(rhs.mWorld)
{

}

EventMessage& EventMessage::operator=(const EventMessage& rhs)
{
	if (this != &rhs)
	{
		mSubtype = rhs.mSubtype;
		mWorld = rhs.mWorld;
	}

	return *this;
}

std::string& EventMessage::Subtype()
{
	return mSubtype;
}

void EventMessage::SetSubtype(const std::string& type)
{
	mSubtype = const_cast<std::string&>(type);
}

World& EventMessage::GetWorld()
{
	return *mWorld;
}

void EventMessage::SetWorld(const World& world)
{
	mWorld = &const_cast<World&>(world);
}