#include "pch.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(World);

World::World() :
	mName(""), mActions(nullptr), mSectors(nullptr), mState(), mQueue(nullptr)
{
	mQueue = new EventQueue();
	mState.SetGameTime(mGameTime);
	mGameTime.SetCurrentTime(std::chrono::steady_clock::now());

	AddInternalAttribute(NameKey, mName, 1);
	AddScope(SectorKey, *new Scope());
	AddScope(ActionKey, *new Scope());

	mActions = Find(ActionKey);
	mSectors = Find(SectorKey);

	delete mActions->Get<Scope*>();
	delete mSectors->Get<Scope*>();
}

World::World(const std::string name) :
	mName(""), mActions(nullptr), mSectors(nullptr), mState(), mQueue(nullptr)
{
	mQueue = new EventQueue();
	mState.SetGameTime(mGameTime);
	mGameTime.SetCurrentTime(std::chrono::steady_clock::now());

	AddInternalAttribute(NameKey, mName, 1);
	SetName(name);
	AddScope(SectorKey, *new Scope());
	AddScope(ActionKey, *new Scope());

	mActions = Find(ActionKey);
	mSectors = Find(SectorKey);

	delete mActions->Get<Scope*>();
	delete mSectors->Get<Scope*>();
}

World::~World()
{
	delete mQueue;
}

std::string& World::Name()
{
	return mName;
}

void World::SetName(const std::string& name)
{
	if (name == "")
	{
		throw std::exception("Name Can Not Be Empty");
	}

	*this->Find(NameKey) = name;

	mName = name;
}

Datum* World::Sectors()
{
	return mSectors;
}

Datum* World::Actions()
{
	return mActions;
}

Sector& World::CreateSector(const std::string& instanceName)
{
	Sector* newSector = new Sector(instanceName, this);

	Adopt(*newSector, SectorKey);

	return *newSector;
}

Action& World::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* newAction = Factory<Action>::Create(className);
	newAction->SetName(const_cast<std::string&>(instanceName));

	Adopt(*newAction, ActionKey);

	return *newAction;
}

void World::Update()
{
	mState.mWorld = this;

	Scope* curScope;

	// Actions First
	for (std::uint32_t i = 0; i < mActions->Size(); ++i)
	{
		curScope = mActions->Get<Scope*>(i);
		if (curScope->Is(Action::TypeIdClass()))
		{
			Action* curAction = curScope->As<Action>();
			curAction->Update(mState);

			if (curAction->isPendingDelete())
			{
				delete curAction;
				--i;
			}
		}
		else
			throw std::exception("A Non-Action Type Object Found In Entities Reference");
	}

	// Sectors Second
	std::uint32_t size = mSectors->Size();
	for (std::uint32_t i = 0; i < size; ++i)
	{
		curScope = mSectors->Get<Scope*>(i);
		if (curScope->Is(Sector::TypeIdClass()))
			curScope->As<Sector>()->Update(mState);
		else
			throw std::exception("A Non-Entity Type Object Found In Entities Reference");
	}
}

WorldState& World::GetWorldState()
{
	return mState;
}

EventQueue* World::GetEventQueue()
{
	return mQueue;
}