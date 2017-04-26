#include "pch.h"
#include "FooXMLHelper.h"
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

using namespace FieaGameEngine;
RTTI_DEFINITIONS(FooXMLHelper);

FooXMLHelper::~FooXMLHelper()
{
}

void FooXMLHelper::Initialize()
{
	mIsInitialized = true;
}

bool FooXMLHelper::StartElementHandler(const std::string & name, const xmlHashMap & attributes, SharedData* data)
{
	bool Handles = false;
	if (mIsInitialized && 
		data->TypeIdInstance() == FooSharedData::TypeIdClass() && 
		name == "Integer")
	{
		FooSharedData* temp = dynamic_cast<FooSharedData*>(data);

		for each(std::pair<std::string, std::string> pair in attributes)
		{
 			if (pair.first == "Health")
 			{
 				temp->Health = stoi(pair.second);
 			}
		}

		Handles = true;
	}
	
	return Handles;
}

bool FooXMLHelper::EndElementHandler(const std::string& name, SharedData* data)
{
	bool Handles = false;

	if (mIsInitialized && data->TypeIdInstance() == FooSharedData::TypeIdClass())
	{
		if(name == "Integer" || name == "Mana")
			Handles = true;
	}
	return Handles;
}

bool FooXMLHelper::CharDataHandler(const char* buffer, const std::uint32_t length, SharedData* data)
{
	bool Handles = false;

	if (mIsInitialized && data->TypeIdInstance() == FooSharedData::TypeIdClass())
	{
		FooSharedData* temp = dynamic_cast<FooSharedData*>(data);
		std::string tempStr;

		tempStr.reserve(length + 1);
		strncpy(&tempStr[0], buffer, length);

		temp->Mana = stoi(tempStr);
		Handles = true;
	}

	return Handles;
}

XMLParseHelper& FooXMLHelper::Clone()
{
	FooXMLHelper* newHelper = new FooXMLHelper();
	return *newHelper;
}
