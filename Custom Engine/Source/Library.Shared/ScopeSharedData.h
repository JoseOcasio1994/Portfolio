#pragma once
#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	class Scope;

	class ScopeSharedData : public SharedData
	{
		RTTI_DECLARATIONS(ScopeSharedData, RTTI);

	public:

		ScopeSharedData& Clone();

		Scope scope;
	
	};
}