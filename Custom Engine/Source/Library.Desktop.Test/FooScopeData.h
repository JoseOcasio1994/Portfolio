#pragma once
#include "pch.h"

namespace FieaGameEngine
{
	class FooScopeData : public ScopeSharedData
	{
		RTTI_DECLARATIONS(FooScopeData, ScopeSharedData);

	public:
		FooScopeData& Clone();
	};
}