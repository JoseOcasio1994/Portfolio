#include "pch.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ActionListIf);

ActionListIf::ActionListIf() :
	mInitCondition(0), ifActions(new ActionList("IfActions")), elseActions(new ActionList("ElseActions"))
{
	AddInternalAttribute(ConditionKey, mInitCondition, 1);
	Adopt(*ifActions, ifActions->Name());
	Adopt(*elseActions, elseActions->Name());
}

void ActionListIf::Update(WorldState& state)
{
	ActionList* curAction;

	if (mInitCondition == Find(ConditionKey)->Get<std::int32_t>())
	{
		if (ifActions->Size() == 0)
			throw std::exception("Must Have An If Statement");

		curAction = ifActions;
	}

	else
	{
		curAction = elseActions;
	}


	if (curAction != nullptr)
	{
		curAction->Update(state);
	}
}

void ActionListIf::InitializeCondition(std::int32_t value)
{
	mInitCondition = value;
	this->operator[](ConditionKey).Set(value);
}

void ActionListIf::SetCondition(std::int32_t value)
{
	Find(ConditionKey)->Set(value);
}

ActionList* ActionListIf::GetIfActions()
{
	return ifActions;
}

ActionList* ActionListIf::GetElseActions()
{
	return elseActions;
}