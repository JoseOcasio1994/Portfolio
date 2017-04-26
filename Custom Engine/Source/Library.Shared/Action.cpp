#include "pch.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Action);

HashMap<std::string, Factory<Action>& >  Factory<Action>::mFactories(Entity::mNumFactories);

Action::Action() :
	mPendingDelete(false)
{
	AddExternalAttribute(NameKey, &EmptyName, 1);
}

std::string& Action::Name() 
{ 
	return mName; 
}

void Action::SetName(const std::string& name)
{
	if (name == "")
	{
		throw std::exception("Name Must Not Be Empty");
	}

	*this->Find(NameKey) = name;
	mName = name;
}

void Action::MarkForDelete()
{
	mPendingDelete = true;
}

bool Action::isPendingDelete()
{
	return mPendingDelete;
}