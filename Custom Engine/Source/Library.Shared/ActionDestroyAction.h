#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{

	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action);

	private:

		SList<std::string> mPendingDestroy;

	public:

		ActionDestroyAction();

		void Update(WorldState& state);

		void PendDestroyAction(const std::string& name);

	};
}