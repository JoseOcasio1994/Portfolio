#include "pch.h"
#include "FooSharedData.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(FooSharedData);

FooSharedData::FooSharedData() :
	Health(0), Mana(0)
{
	mMasterPointer = nullptr;
	mDepth = 0;
}

FooSharedData::~FooSharedData()
{

}

FooSharedData& FooSharedData::Clone()
{
	FooSharedData* newFoo = new FooSharedData();

	return *newFoo;
}