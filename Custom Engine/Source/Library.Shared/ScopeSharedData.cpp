#include "pch.h"
#include "ScopeSharedData.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ScopeSharedData);

ScopeSharedData& ScopeSharedData::Clone()
{
	ScopeSharedData* newFoo = new ScopeSharedData();

	return *newFoo;
}