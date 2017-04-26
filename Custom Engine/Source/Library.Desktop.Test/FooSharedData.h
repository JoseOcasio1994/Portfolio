#pragma once

#include "pch.h"

namespace FieaGameEngine
{
	class FooSharedData : public SharedData
	{
		RTTI_DECLARATIONS(FooSharedData, RTTI);

	public:

		FooSharedData();
		~FooSharedData();
		FooSharedData& Clone();
		int Health, Mana;
	};
}