#include "pch.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionCreateAction);

ActionCreateAction::ActionCreateAction()
{
}

void ActionCreateAction::Update(WorldState& state)
{
	state.mAction = this;
	
	if (!mPendingCreate.isEmpty() && mParent != nullptr)
	{
		pairType* pair = &mPendingCreate.Front();

		Action* newAction = Factory<Action>::Create(pair->first);
		newAction->SetName(const_cast<std::string&>(pair->second));

		mParent->Adopt(*newAction,"Actions");
		mPendingCreate.PopFront();
	}

// 	if (mPendingCreate.isEmpty())
// 		MarkForDelete();
}

void ActionCreateAction::PendCreateAction(const std::string& prototype, const std::string& name)
{
	mPendingCreate.PushBack(pairType(prototype, name));
}