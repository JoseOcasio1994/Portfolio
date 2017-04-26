#include "pch.h"
#include "XMLTableParser.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(XMLTableParser);

void XMLTableParser::Initialize()
{
	if(!mIsInitialized)
	{
		mIsInitialized = true;
		curScope = nullptr;
		mState = None;
	}
}

bool XMLTableParser::StartElementHandler(const std::string & name, const xmlHashMap & attributes, SharedData* data)
{
	bool handles = false;

	if (mIsInitialized && data->Is(ScopeSharedData::TypeIdClass()))
	{
		if (curScope == nullptr)
			curScope = &data->As<ScopeSharedData>()->scope;

		if (name == "Integer")
			handles = IntHandler(attributes);

		else if (name == "Float")
			handles = FloatHandler(attributes);

		else if (name == "Vector")
			handles = VectorHandler(attributes);

		else if (name == "Matrix")
			handles = MatrixHandler(attributes);

		else if (name == "String")
			handles = StringHandler(attributes);

		else if (name == "Scope" || name == "Table")
			handles = ScopeHandler(attributes);

		else if (name == "World")
			handles = WorldHandler(attributes, data->Depth());

		else if (name == "Sector")
			handles = SectorHandler(attributes);

		else if (name == "Entity")
			handles = EntityHandler(attributes);

		else if (name == "Action")
			handles = ActionHandler(attributes);

		else if (name == "If" || name == "Then" || name == "Else")
			handles = ActionIfHandler(name, attributes);

		else if (name == "Condition" && mState == If)
			mState = Condition;

	}

	return handles;
}

bool XMLTableParser::EndElementHandler(const std::string& name, SharedData* data)
{
	bool handles = false;

	if (mIsInitialized &&data->Is(ScopeSharedData::TypeIdClass()))
	{
		if (name == "Scope" || name == "Table" || name == "World" || name == "Sector" || 
			name == "Entity" || name == "Action" || name == "If" || name == "Then" || name == "Else")
		{
			curScope = curScope->GetParent();
		}

		handles = true;
	}
	
	if (name == "If" && mState == If)
		mState = None;

	else if (name == "Condition" && mState == Condition)
		mState = If;

	else if (name == "Then" && mState == Then)
		mState = If;

	else if (name == "Else" && mState == Else)
		mState = If;

	return handles;
}

bool XMLTableParser::CharDataHandler(const char* buffer, const std::uint32_t length, SharedData* data)
{
	UNREFERENCED_PARAMETER(data);

	bool Handles = false;

	std::string value = "";
	value.append(buffer, length);

	if (mState == Condition)
	{
		ActionListIf* IfAction = curScope->As<ActionListIf>();
		if (IfAction != nullptr)
			IfAction->InitializeCondition(stoi(value));
	}

	return Handles;
}

XMLParseHelper& XMLTableParser::Clone()
{
	XMLTableParser* newHelper = new XMLTableParser();
	return *newHelper;
}

bool XMLTableParser::IntHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr, *valuePtr = nullptr;
	bool Handles = false;

	if(attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if(attributes.ContainsKey("Value"))
		valuePtr = &attributes.At("Value");

	if (namePtr != nullptr && valuePtr != nullptr)
	{
		Handles = true;
		Datum* ref = &curScope->Append(*namePtr);
		ref->SetType(Datum::DatumType::Integer);
		ref->SetFromString(*valuePtr);
	}

	return Handles;
}

bool XMLTableParser::FloatHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr, *valuePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (attributes.ContainsKey("Value"))
		valuePtr = &attributes.At("Value");

	if (namePtr != nullptr && valuePtr != nullptr)
	{
		Handles = true;
		Datum* ref = &curScope->Append(*namePtr);
		ref->SetType(Datum::DatumType::Float);
		ref->SetFromString(*valuePtr);
	}

	return Handles;
}

bool XMLTableParser::VectorHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr, *xPtr = nullptr, *yPtr = nullptr, *zPtr = nullptr, *wPtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (attributes.ContainsKey("X"))
		xPtr = &attributes.At("X");

	if (attributes.ContainsKey("Y"))
		yPtr = &attributes.At("Y");

	if (attributes.ContainsKey("Z"))
		zPtr = &attributes.At("Z");

	if (attributes.ContainsKey("W"))
		wPtr = &attributes.At("W");

	if (namePtr != nullptr && xPtr != nullptr && yPtr != nullptr && zPtr != nullptr && wPtr != nullptr)
	{
		Handles = true;
		Datum* ref = &curScope->Append(*namePtr);
		ref->SetType(Datum::DatumType::Vector);

		std::string str = *xPtr + " " + *yPtr + " " + *zPtr + " " + *wPtr;
		ref->SetFromString(str);
	}

	return Handles;
}

bool XMLTableParser::MatrixHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr, *row1Ptr = nullptr, *row2Ptr = nullptr, *row3Ptr = nullptr, *row4Ptr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (attributes.ContainsKey("Row1"))
		row1Ptr = &attributes.At("Row1");

	if (attributes.ContainsKey("Row2"))
		row2Ptr = &attributes.At("Row2");

	if (attributes.ContainsKey("Row3"))
		row3Ptr = &attributes.At("Row3");

	if (attributes.ContainsKey("Row4"))
		row4Ptr = &attributes.At("Row4");

	if (namePtr != nullptr && row1Ptr != nullptr && row2Ptr != nullptr && row3Ptr != nullptr && row4Ptr != nullptr)
	{
		Handles = true;
		Datum* ref = &curScope->Append(*namePtr);
		ref->SetType(Datum::DatumType::Matrix);

		std::string str = *row1Ptr + " " + *row2Ptr + " " + *row3Ptr + " " + *row4Ptr;
		ref->SetFromString(str);
	}

	return Handles;
}

bool XMLTableParser::StringHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr, *valuePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (attributes.ContainsKey("Value"))
		valuePtr = &attributes.At("Value");

	if (namePtr != nullptr && valuePtr != nullptr)
	{
		Handles = true;
		Datum* ref = &curScope->Append(*namePtr);
		ref->SetType(Datum::DatumType::String);
		ref->SetFromString(*valuePtr);
	}

	return Handles;
}

bool XMLTableParser::ScopeHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (namePtr != nullptr)
	{
		Handles = true;
		curScope = &curScope->AppendScope(*namePtr);
	}

	return Handles;
}

bool XMLTableParser::WorldHandler(const xmlHashMap& attributes, const std::uint32_t depth)
{
	if (depth > 1)
		throw std::exception("World Must Be The Root Tag.");

	const std::string* namePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (namePtr != nullptr)
	{
		Handles = true;
		curScope->Adopt(*new World(*namePtr), "Worlds");
		curScope = curScope->Find("Worlds")->Get<Scope*>();
	}

	return Handles;
}

bool XMLTableParser::SectorHandler(const xmlHashMap& attributes)
{
	const std::string* namePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (namePtr != nullptr)
	{
		Handles = true;

		World* world = curScope->As<World>();

		if (world != nullptr)
		{
			world->CreateSector(*namePtr);
			curScope = world->Sectors()->Get<Scope*>(world->Sectors()->Size() - 1);
		}
		else
		{
			curScope->Adopt(*new Sector(*namePtr), "Sectors");
			curScope = curScope->Find(*namePtr)->Get<Scope*>();
		}
	}

	return Handles;
}

bool XMLTableParser::EntityHandler(const xmlHashMap& attributes)
{
	const std::string* classPtr = nullptr, *namePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (attributes.ContainsKey("Class"))
		classPtr = &attributes.At("Class");

	if (namePtr != nullptr && classPtr != nullptr)
	{
		Handles = true;

		Sector* sector = curScope->As<Sector>();
		Datum* datum;

		if (sector != nullptr)
		{
			sector->CreateEntity(*classPtr, *namePtr);

			datum = sector->Entities();
			curScope = datum->Get<Scope*>(datum->Size()-1);
		}
		else
		{
			Entity* newEntity = Factory<Entity>::Create(*classPtr);
			newEntity->SetName(*namePtr);

			curScope->Adopt(*newEntity, "Entities");

			datum = curScope->Find("Entities");
			curScope = datum->Get<Scope*>(datum->Size()-1);
		}
	}

	return Handles;
}

bool XMLTableParser::ActionHandler(const xmlHashMap& attributes)
{
	const std::string* classPtr = nullptr, *namePtr = nullptr, *typePtr = nullptr;
	bool Handles = false;

	if (attributes.ContainsKey("Name"))
		namePtr = &attributes.At("Name");

	if (attributes.ContainsKey("Class"))
		classPtr = &attributes.At("Class");

	if (attributes.ContainsKey("Type"))
		typePtr = &attributes.At("Type");

	// Any Action
	if (namePtr != nullptr && classPtr != nullptr && typePtr == nullptr)
	{
		Handles = true;

		Action* newAction = Factory<Action>::Create(*classPtr);
		newAction->SetName(const_cast<std::string&>(*namePtr));

		curScope->Adopt(*newAction, "Actions");

		Datum* datum = curScope->Find("Actions");
		curScope = datum->Get<Scope*>(datum->Size() - 1);
	}
	
	// Action Create Action
	else if (namePtr != nullptr && classPtr != nullptr && typePtr != nullptr && *typePtr == "Create")
	{
		Handles = true;

		ActionCreateAction* temp = new ActionCreateAction();
		temp->SetName("ActionCreateAction");
		temp->PendCreateAction(*classPtr, *namePtr);
		curScope->Adopt(*temp, "Actions");
		curScope = temp;
	}

	// Action Destroy Action
	else if (namePtr != nullptr && typePtr != nullptr && *typePtr == "Destroy")
	{
		Handles = true;

		ActionDestroyAction* temp = new ActionDestroyAction();
		temp->SetName("ActionDestroyAction");
		temp->PendDestroyAction(*namePtr);
		curScope->Adopt(*temp, "Actions");
		curScope = temp;
	}

	return Handles;
}

bool XMLTableParser::ActionIfHandler(const std::string& name, const xmlHashMap& attributes)
{
	UNREFERENCED_PARAMETER(attributes);
	bool Handles = true;

	mState = If;

	if(name == "If")
	{
		ActionListIf* ifAction = new ActionListIf();

		if (attributes.ContainsKey("Name"))
			ifAction->SetName(attributes.At("Name"));
		else
			ifAction->SetName("IfAction");

		curScope->Adopt(*ifAction, "Actions");
		curScope = ifAction;
	}

	else if (name == "Then")
	{
		ActionListIf* ifAction = curScope->As<ActionListIf>();

		if(ifAction != nullptr)
		{
			mState = Then;
			curScope = ifAction->GetIfActions();
		}

		else
		{
			Handles = false;
		}
	}

	else if (name == "Else")
	{
		ActionListIf* ifAction = curScope->As<ActionListIf>();

		if (ifAction != nullptr)
		{
			mState = Else;
			curScope = ifAction->GetElseActions();
		}

		else
		{
			Handles = false;
		}
	}

	return Handles;
}