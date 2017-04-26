
#include "pch.h"
#include "Scope.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Scope);

#pragma region CONSTRUCTORS_AND_OPERATORS

Scope::Scope(std::uint32_t size) :
	mSize(0),mTable(size), mTablePointers(size), mParent(nullptr)
{
}

Scope::Scope(const Scope& Original) :
	mSize(0), mTable(defaultHashSize), mTablePointers(defaultHashSize), mParent(nullptr)
{
	operator=(Original);
}

Scope::Scope(Scope&& Original) :
	mSize(Original.mSize), mTable(std::move(Original.mTable)), mTablePointers(std::move(Original.mTablePointers)), mParent(Original.mParent)
{
	Original.mSize = 0;
	Original.mParent = nullptr;
}

Scope& Scope::operator=(const Scope& Original)
{
	if (this != &Original)
	{
		Clear();
		mTablePointers.Reserve(Original.mSize);

		for (std::uint32_t i = 0; i < Original.mSize; ++i)
		{
			PairType pair = *Original.mTablePointers[i];

			if (pair.second.Type() != Datum::Table)
			{
				Datum& datum = Append(pair.first);
				datum = pair.second;
			}

			else
			{
				AppendScope(pair.first) = *pair.second.Get<Scope*>();
			}
		}
	}

	return *this;
}

Scope& Scope::operator=(Scope&& Original)
{
	if (this != &Original)
	{
		Clear();

		mSize = Original.mSize;
		mTable = std::move(Original.mTable);
		mTablePointers = std::move(Original.mTablePointers);

		Reparent(Original);
		mParent = Original.mParent;

		for (PairType* pair : mTablePointers)
		{
			if (pair->second.Type() == Datum::Table)
			{
				for (std::uint32_t i = 0; i < pair->second.Size(); ++i)
				{
					pair->second[i].mParent = this;
				}
			}
		}

		Original.mSize = 0;
		Original.mParent = nullptr;
	}

	return *this;
}

Scope::~Scope()
{
	Orphan();
	Clear();
}

Datum& Scope::operator[](const std::string name)
{
	return Append(name);
}

Datum& Scope::operator[](const std::uint32_t index)
{
	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");
	
	return mTablePointers[index]->second;
}

bool Scope::operator==(const Scope& rhs)
{
	std::uint32_t size = Size();

	if ( size != rhs.Size() )
		return false;

	for (std::uint32_t i = 0; i < size; ++i)
		if (*mTablePointers[i] != *rhs.mTablePointers[i])
			return false;

	return true;
}

bool Scope::operator!=(const Scope& rhs)
{
	return !(operator==(rhs));
}

#pragma endregion

#pragma region METHODS

std::uint32_t Scope::Size() const
{
	return mSize;
}

Datum* Scope::Find(const std::string name) const
{

	for (std::uint32_t i = 0; i < mSize; ++i)
	{
		if (mTablePointers[i]->first == name)
			return &mTablePointers[i]->second;
	}

	return nullptr;
}

Datum* Scope::Search(const std::string name, Scope** scope) const
{
	Datum* ptr = Find(name);

	if (ptr == nullptr && mParent != nullptr)
		ptr = mParent->Search(name, scope);
	else
		if(scope != nullptr)
			*scope = const_cast<Scope*>(this);

	return ptr;
}

Datum& Scope::Append(const std::string name)
{
	Datum* datum = Find(name);

	if (datum != nullptr)
		return *datum;

	// Resize mTablePointers
	if ( mSize  == mTablePointers.Capacity() )
		mTablePointers.Reserve(mSize + 3);

	mTablePointers.PushBack(&*mTable.Insert( PairType(name, Datum()) ) );
	return mTablePointers[mSize++]->second;
}

Scope& Scope::AppendScope(const std::string name) 
{
	std::uint32_t i = 0;
	Scope *scope = new Scope();
	scope->mParent = this;

	// Find Index Of Existing Entry
	for (0; i < mSize; ++i)
	{
		if (mTablePointers[i]->first == name)
			break;
	}

	// Found Entry
	if (i != mSize)
	{
		Datum* datum = &mTablePointers[i]->second;

		// Exception If Found Existing Element Of Non-Table
		if (datum->Type() != Datum::Table)
		{
			delete scope;
			throw std::exception("Existing Non-Scope Element Found");
		}

		// Append Existing Entry To New Table
		scope->Append(name) = datum->Get<Scope*>();
		datum->Get<Scope*>()->mParent = scope;
	}
	else
	{
		mTablePointers.PushBack(&*mTable.Insert(PairType(name, Datum())));
		++mSize;
	}

	mTablePointers[i]->second = scope;
	return mTablePointers[i]->second[0];
}

Scope* Scope::GetParent() const
{
	return mParent;
}

std::string Scope::FindName(const Scope& scope) const
{
	std::uint32_t size = Size();
	std::string str = "";

	for (std::uint32_t i = 0; i < size; ++i)
	{
		if (mTablePointers[i]->second.Type() == Datum::Table && mTablePointers[i]->second[0] == scope)
		{
			str = mTablePointers[i]->first;
			break;
		}
	}

	return str;
}

void Scope::Clear()
{
	for (std::uint32_t i = 0; i < mSize; ++i)
	{
		Datum* curDatum = &mTablePointers[i]->second;
		if (curDatum->Type() == Datum::Table)
			for (std::int32_t j = (std::int32_t)curDatum->Size()-1; j >= 0; --j)
			{
				Scope* temp = curDatum->Get<Scope*>(j);
				delete temp;
			}

		mTable.Remove(mTablePointers[i]->first);
	}

	mTablePointers.Clear();
	mSize = 0;
}

void Scope::Adopt(Scope& scope, const std::string name)
{
	scope.Orphan();
	scope.mParent = this;
	Append(name).Pushback(&scope);
}

void Scope::Orphan()
{
	if (mParent != nullptr)
	{
		std::uint32_t size = mParent->Size(), i = 0;
		Datum* datum = nullptr;

		for (; i < size; ++i)
		{
			datum = &(mParent->mTablePointers[i]->second);

			if (datum->RemoveTable(this))
				break;
		}

		mParent = nullptr;
	}

}

void Scope::Reparent(Scope& scope)
{
	if (scope.mParent != nullptr)
	{
		std::string name = scope.mParent->FindName(scope);
		Datum* datum = scope.mParent->Find(name);

		for (std::uint32_t i = 0; i < datum->Size(); ++i)
		{
			if (datum->Get<Scope*>(i) == &scope)
			{
// 				datum->Set(this,i);
			}
		}
	}
}

Scope::PairType* Scope::GetPair(std::uint32_t i)
{
	if (i >= mSize)
		throw std::exception("Out Of Range");

	return mTablePointers[i];
}

#pragma endregion
