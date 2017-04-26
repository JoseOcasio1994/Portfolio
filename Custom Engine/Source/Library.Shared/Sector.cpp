#include "pch.h"
#include "Sector.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Sector);

Sector::Sector() :
	mName(""), mWorld(nullptr)
{
	AddInternalAttribute(NameKey, mName, 1);
	AddScope(EntityKey, *new Scope());
	AddScope(ActionKey, *new Scope());

	mEntities = Find(EntityKey);
	mActions = Find(ActionKey);

	delete mEntities->Get<Scope*>();
	delete mActions->Get<Scope*>();
}

Sector::Sector(const std::string name, World* world) :
	mName(""), mWorld(nullptr)
{
	AddInternalAttribute(NameKey, mName, 1);
	SetName(name);
	AddScope(EntityKey, *new Scope());
	AddScope(ActionKey, *new Scope());

	mEntities = Find(EntityKey);
	mActions = Find(ActionKey);

	delete mEntities->Get<Scope*>();
	delete mActions->Get<Scope*>();

	if(world != nullptr)
		SetWorld(*world);

}

Sector::~Sector()
{
}

std::string& Sector::Name()
{
	return mName;
}

void Sector::SetName(const std::string & name)
{
	if (name == "")
	{
		throw std::exception("Name Can Not Be Empty");
	}

	*this->Find(NameKey) = name;
	mName = name;
}

World* Sector::GetWorld() const
{
	return mWorld;
}

void Sector::SetWorld(World& world)
{
	mWorld = &world;
}

Datum* Sector::Entities()
{
	return mEntities;
}

Datum* Sector::Actions()
{
	return mActions;
}

Entity& Sector::CreateEntity(const std::string& className, const std::string& instanceName)
{
	Entity* newEntity = Factory<Entity>::Create(className);
	newEntity->SetName(instanceName);
	newEntity->SetSector(*this);

	Adopt(*newEntity, EntityKey);

	return *newEntity;
}

Action& Sector::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* newAction = Factory<Action>::Create(className);
	newAction->SetName(const_cast<std::string&>(instanceName));

	Adopt(*newAction, ActionKey);

	return *newAction;
}

void Sector::Update(WorldState& state)
{
	state.mSector = this;

	Scope* curScope;
	std::uint32_t size = mActions->Size();

	// Actions First
	for (std::uint32_t i = 0; i < size; ++i)
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
			throw std::exception("A Non-Action Type Object Found In Entities Reference");
	}

	// Entities Second
	size = mEntities->Size();
	for (std::uint32_t i = 0; i < size; ++i)
	{
		curScope = mEntities->Get<Scope*>(i);

		if (curScope->Is(Entity::TypeIdClass()))
			curScope->As<Entity>()->Update(state);
		else
			throw std::exception("A Non-Entity Type Object Found In Entities Reference");
	}

}
