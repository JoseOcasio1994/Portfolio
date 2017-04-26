#include "pch.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionDestroyAction);

ActionDestroyAction::ActionDestroyAction()
{

}

void ActionDestroyAction::Update(WorldState& state)
{
	state.mAction = this;

	if (!mPendingDestroy.isEmpty() && mParent != nullptr)
	{
		Datum* actions = mParent->Find("Actions");
		Action* curAction;

		std::uint32_t size = actions->Size();

		for (std::uint32_t i = 0; i < size; ++i)
		{
			curAction = actions->Get<Scope*>(i)->As<Action>();

			if (curAction != nullptr && curAction->Name() == mPendingDestroy.Front())
			{
				curAction->MarkForDelete();
				break;
			}
		}

		mPendingDestroy.PopFront();
	}

// 	if (mPendingDestroy.isEmpty())
// 		MarkForDelete();
}



void ActionDestroyAction::PendDestroyAction(const std::string& name)
{
	mPendingDestroy.PushBack(name);
}