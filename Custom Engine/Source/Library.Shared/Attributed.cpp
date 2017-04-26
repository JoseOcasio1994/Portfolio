#include "pch.h"
#include "Attributed.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Attributed);

Attributed::attrHash Attributed::mPrescribedAttributes(10);

#pragma region CONSTRUCTORS_AND_OPERATORS

Attributed::Attributed()
{
	RTTI* ptr = this;
	AddInternalAttribute("this", &ptr, 1);
}

Attributed::Attributed(const Attributed& Original)
{
	operator=(Original);
}

Attributed& Attributed::operator=(const Attributed& Original)
{
	if (this != &Original)
	{
		Scope::operator=(Original);

		Datum* datum = Find("this");
		RTTI* rtti = this;
		*datum = rtti;
	}

	return *this;
}

Attributed::Attributed(Attributed&& Original) :
  Scope(std::move(Original))
{
	Datum* datum = Find("this");
	RTTI* rtti = this;
	*datum = rtti;
}

Attributed& Attributed::operator=(Attributed&& Original)
{
	if (this != &Original)
	{
		Scope::operator=(std::move(Original));

		Datum* datum = Find("this");
		RTTI* rtti = this;
		*datum = rtti;
	}

	return *this;
}

Attributed::~Attributed()
{
	mPrescribedAttributes.Clear();
}

#pragma endregion

#pragma region MAIN_FUNCTIONS

bool Attributed::IsAttribute(const std::string& name)
{	
	return Find(name) != nullptr;
}

bool Attributed::IsPrescribedAttribute(const std::string& name) 
{
	bool isTrue = IsAttribute(name);

	if (isTrue)
	{
		Vector<std::string>* signature = GetSignature(TypeIdInstance());

		if (signature == nullptr || signature->Find(name) == signature->end())
			isTrue = false;
	}

	return isTrue;
}

bool Attributed::IsAuxiliaryAttribute(const std::string& name)
{
	return IsAttribute(name) && !IsPrescribedAttribute(name);
}

Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
{
	if (IsPrescribedAttribute(name))
		throw std::exception("Name Found Is Already A Prescribed Attribute");

	return Append(name);
}

std::uint32_t Attributed::AuxiliaryBegin()
{
	return mPrescribedAttributes.Find(TypeIdInstance())->second.Size();
}

#pragma endregion

#pragma region ADD_ATTRIBUTE_HELPERS

Datum& Attributed::AddInternalAttribute(const std::string& name, std::int32_t value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(value);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddInternalAttribute(const std::string& name, std::float_t value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(value);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddInternalAttribute(const std::string& name, std::string value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(value);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddInternalAttribute(const std::string& name, glm::vec4 value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(value);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddInternalAttribute(const std::string& name, glm::mat4x4 value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(value);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddInternalAttribute(const std::string& name, RTTI** value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(*value);

	AddSignature(name);

	return *temp;
}



Datum& Attributed::AddExternalAttribute(const std::string& name, const std::int32_t* value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	const std::int32_t* ptr = value;

	temp->SetStorage(ptr, size);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddExternalAttribute(const std::string& name, const std::float_t* value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	const std::float_t* ptr = value;

	temp->SetStorage(ptr, size);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddExternalAttribute(const std::string& name, const std::string* value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	const std::string* ptr = value;

	temp->SetStorage(ptr, size);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddExternalAttribute(const std::string& name, const glm::vec4* value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	const glm::vec4* ptr = value;

	temp->SetStorage(ptr, size);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddExternalAttribute(const std::string& name, const glm::mat4x4* value,std::uint32_t size)
{
	Datum *temp = &Append(name);

	const glm::mat4x4* ptr = value;

	temp->SetStorage(ptr, size);

	AddSignature(name);

	return *temp;
}

Datum& Attributed::AddExternalAttribute(const std::string& name, RTTI** value, std::uint32_t size)
{
	Datum *temp = &Append(name);

	RTTI **tempVal = &value[0];

	for (std::uint32_t i = 0; i < size; ++i)
		temp->Pushback(tempVal[i]);

	AddSignature(name);

	return *temp;
}



Scope& Attributed::AddScope(const std::string& name, Scope& scope)
{
	Adopt(scope, name);

	AddSignature(name);

	return scope;
}

#pragma endregion

#pragma region SIGNATURE

Vector<std::string>* Attributed::GetSignature(std::uint64_t id)
{
	attrHash::Iterator it = mPrescribedAttributes.Find(id);

	if (it == mPrescribedAttributes.end())
		return nullptr;

	return &it->second;
}

void Attributed::AddSignature(std::string name)
{
	std::int64_t id = TypeIdInstance();
	Vector<std::string>* attributes = &mPrescribedAttributes[id];

	if (attributes != nullptr && attributes->Find(name) == attributes->end())
		attributes->PushBack(name);
}

#pragma endregion
