#include "pch.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ActionList);

ActionList::ActionList() :
	Action(), mActions(nullptr)
{
	AddScope(ActionKey, *new Scope);
	mActions = Find(ActionKey);
	delete mActions->Get<Scope*>();
}

ActionList::ActionList(const std::string& name) :
	Action(), mActions(nullptr)
{
	SetName(name);

	AddScope(ActionKey, *new Scope);
	mActions = Find(ActionKey);
	delete mActions->Get<Scope*>();
}

void ActionList::Update(WorldState& state)
{
	state.mAction = this;

	Scope* curScope;
	std::uint32_t size = mActions->Size();

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
			throw std::exception("A Non-Entity Type Object Found In Entities Reference");
	}
}

Datum* ActionList::Actions()
{
	return mActions;
}

Action& ActionList::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* newAction = Factory<Action>::Create(className);
	newAction->SetName(const_cast<std::string&>(instanceName));

	Adopt(*newAction, ActionKey);

	return *newAction;
}
