#include "pch.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Entity);

HashMap<std::string, Factory<Entity>& >  Factory<Entity>::mFactories(Entity::mNumFactories);

Entity::Entity() :
	mName(""), mSector(nullptr), mActions(nullptr)
{
	AddInternalAttribute(NameKey, mName, 1);
	AddScope(ActionKey, *new Scope());
	mActions = Find(ActionKey);
	delete mActions->Get<Scope*>();
}

Entity::Entity(const std::string& name, Sector* sector) :
	mName(""), mSector(nullptr), mActions(nullptr)
{
	AddInternalAttribute(NameKey, mName, 1);
	SetName(name);

	AddScope(ActionKey, *new Scope());
	mActions = Find(ActionKey);
	delete mActions->Get<Scope*>();

	if(sector != nullptr)
		SetSector(*sector);
}

Entity::~Entity()
{
}

std::string& Entity::Name()
{
	return mName;
}

void Entity::SetName(const std::string& name)
{
	if (name == "")
	{
		throw std::exception("Name Can Not Be Empty");
	}

	*this->Find(NameKey) = name;

	mName = name;
}

Sector* Entity::GetSector() const
{
	return mSector;
}

void Entity::SetSector(Sector& sector)
{
	mSector = &sector;
}

Datum* Entity::Actions()
{
	return mActions;
}

Action& Entity::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* newAction = Factory<Action>::Create(className);
	newAction->SetName(const_cast<std::string&>(instanceName));

	Adopt(*newAction, ActionKey);

	return *newAction;
}

void Entity::Update(WorldState& state)
{
	state.mEntity = this;

	Scope* curScope;

	for (std::uint32_t i = 0; i < mActions->Size(); ++i)
	{
		curScope = mActions->Get<Scope*>(i);

		if (curScope->Is(Action::TypeIdClass()))
		{
			Action* curAction = curScope->As<Action>();
			curAction->Update(state);

			if (curAction->isPendingDelete())
			{
				delete curAction;
				--i;
			}
		}
		else
			throw std::exception("A Non-Entity Type Object Found In Entities Reference");
	}
}