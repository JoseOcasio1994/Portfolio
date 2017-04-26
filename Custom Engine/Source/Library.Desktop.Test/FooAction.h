#pragma once
#include <cstdint>
#include "pch.h"

namespace FieaGameEngine
{
	class FooAction : public Action
	{
		
	public:

		int fooInt = 0;

		void Update(WorldState& state)
		{
			state.mAction = this;
			++fooInt;
		}
	};

	ConcreteFactory(Action, FooAction);
}