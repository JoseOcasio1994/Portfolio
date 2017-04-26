#include "pch.h"
#include "FooSharedData.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(FooScopeData);

FooScopeData& FooScopeData::Clone()
{
	FooScopeData* newFoo = new FooScopeData();

	return *newFoo;
}