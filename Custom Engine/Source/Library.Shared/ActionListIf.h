#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{

	class ActionListIf : public Action
	{
		RTTI_DECLARATIONS(ActionListIf, Action);

	private:

		const std::string ConditionKey = "Condition";

		std::int32_t mInitCondition;
		ActionList* ifActions, *elseActions;

	public:

		ActionListIf();

		void Update(WorldState& state);

		void InitializeCondition(std::int32_t value);

		void SetCondition(std::int32_t value);

		ActionList* GetIfActions();

		ActionList* GetElseActions();
	};
}