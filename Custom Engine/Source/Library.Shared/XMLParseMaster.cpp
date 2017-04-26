#include "pch.h"
#include "XMLParseMaster.h"
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

using namespace FieaGameEngine;
RTTI_DEFINITIONS(XMLParseMaster);
RTTI_DEFINITIONS(SharedData);

#pragma region CONSTRUCTORS

XMLParseMaster::XMLParseMaster(const SharedData& Data) :
	mParser(XML_ParserCreate(nullptr)), mSharedData(const_cast<SharedData*>(&Data)), mHelpers(10), isClone(false), mCharData("")
{
	mSharedData->SetXMLParseMaster(this);

 	XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
 	XML_SetCharacterDataHandler(mParser, CharDataHandler);
	XML_SetUserData(mParser, mSharedData);
}

XMLParseMaster::~XMLParseMaster()
{
	if (isClone)
	{
		delete mSharedData;

		for each (XMLParseHelper* helper in mHelpers)
		{
			delete helper;
		}
	}

	XML_ParserFree(mParser);
}

XMLParseMaster& XMLParseMaster::Clone()
{
 	XMLParseMaster* newMaster = new XMLParseMaster(mSharedData->Clone());
 
	for each (XMLParseHelper* helper in mHelpers)
	{
		newMaster->AddHelper(helper->Clone());
	}
	newMaster->isClone = true;

	return *newMaster;
}

#pragma endregion

#pragma region METHODS

void XMLParseMaster::AddHelper(const XMLParseHelper& helper)
{
	if (!isClone)
		mHelpers.PushBack(const_cast<XMLParseHelper*>(&helper));
	else
		throw std::exception("Failed To Add Helper. This Object Is A Clone.");
}

bool XMLParseMaster::RemoveHelper(const XMLParseHelper& helper)
{
	std::uint32_t oldSize = mHelpers.Size();
	mHelpers.Remove(const_cast<XMLParseHelper*>(&helper));

	return mHelpers.Size() < oldSize;
}

void XMLParseMaster::Parse(const char* buffer, int length, bool lastChunk)
{
	for each (XMLParseHelper* helper in mHelpers)
	{
		if (!helper->GetInitialized())
		{
			helper->Initialize();
		}
	}

	XML_Parse(mParser, buffer, length, lastChunk);
}

void XMLParseMaster::ParseFromFile(const std::string& fileName)
{
	char* cFile = &const_cast<std::string&>(fileName)[0];
	FILE *file = fopen(cFile, "r");

	if (file == nullptr)
		throw std::exception("File Not Found!");

	else
	{
		mFile = fileName;

		char* buffer = (char*)malloc(BUFFERSIZE);

		while (fgets(buffer, BUFFERSIZE, file))
		{
			int length = static_cast<int>(strlen(buffer));

			if (buffer[length - 1] == '\n')
			{
				buffer[length - 1] = '\0';
				--length;
				Parse(buffer, length, false);
			}
			else
			{
				Parse(buffer, length, true);
			}
		} 
		
		fclose(file);
		delete buffer;
	}
}

std::string& XMLParseMaster::GetFileName()
{
	return mFile;
}

void XMLParseMaster::SetSharedData(const SharedData& data)
{
	if(!isClone)
	{
		if (mSharedData != nullptr)
			mSharedData->SetXMLParseMaster();

		mSharedData = const_cast<SharedData*>(&data);
		mSharedData->SetXMLParseMaster(this);
	}
	else
		throw std::exception("Failed To Set Data. This Object Is A Clone.");
}

SharedData* XMLParseMaster::GetSharedData()
{
	return mSharedData;
}

void XMLParseMaster::StartElementHandler(void *userData, const char *name, const char **attribute)
{
	SharedData* tempData = reinterpret_cast<SharedData*>(userData);
	XMLParseMaster* master = tempData->GetXMLParseMaster();

	std::uint32_t size = static_cast<std::uint32_t>(master->mCharData.length());
	if (size > 0)
	{
		for each (XMLParseHelper* helper in master->mHelpers)
		{
			if (helper->CharDataHandler(&master->mCharData[0], size, master->mSharedData))
				break;
		}
		master->mCharData.clear();
	}

	HashMap<std::string, std::string> tempHash;
	for (int i = 0; attribute[i] != nullptr; i+=2)
	{
		tempHash.Insert(std::pair<std::string, std::string>(attribute[i], attribute[i + 1]));
	}

	for each (XMLParseHelper* helper in master->mHelpers)
	{
		if(helper->StartElementHandler(name, tempHash, master->mSharedData))
			break;
	}

	tempData->IncrementDepth();
}

void XMLParseMaster::EndElementHandler(void *userData, const char *name)
{
	SharedData* tempData = reinterpret_cast<SharedData*>(userData);
	XMLParseMaster* master = tempData->GetXMLParseMaster();

	std::uint32_t size = static_cast<std::uint32_t>(master->mCharData.length());
	if (size > 0)
	{
		for each (XMLParseHelper* helper in master->mHelpers)
		{
			if (helper->CharDataHandler(&master->mCharData[0], size, master->mSharedData))
				break;
		}
		master->mCharData.clear();
	}

	for each (XMLParseHelper* helper in master->mHelpers)
	{
		if(helper->EndElementHandler(name, master->mSharedData))
			break;
	}

	tempData->DecrementDepth();
}

void XMLParseMaster::CharDataHandler(void *userData, const char *val, int len)
{
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		if (val[i] == ' ' || val[i] == '\t')
			count++;
	}

	if (count < len) // Skip Space And Tab
	{
		SharedData* tempData = reinterpret_cast<SharedData*>(userData);
		XMLParseMaster* master = tempData->GetXMLParseMaster();

		for (int i = 0; i < len; ++i)
			master->mCharData.push_back(val[i]);
	}
}

#pragma endregion

#pragma region SHARED_DATA

void SharedData::SetXMLParseMaster(const XMLParseMaster* master)
{
	mMasterPointer = const_cast<XMLParseMaster*>(master);
}

XMLParseMaster* SharedData::GetXMLParseMaster()
{
	return mMasterPointer;
}

void SharedData::IncrementDepth()
{
	++mDepth;
}

void SharedData::DecrementDepth()
{
	if (mDepth > 0)
	{
		--mDepth;
	}
}

std::uint32_t SharedData::Depth()
{
	return mDepth;
}

#pragma endregion
