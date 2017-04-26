
#include "pch.h"
#include "AttributedFoo.h"

using namespace FieaGameEngine;

AttributedFoo::AttributedFoo() 
{
	PopulateInternal();
	PopulateExternal();
}

AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
	Attributed(rhs)
{
}

AttributedFoo::AttributedFoo(AttributedFoo&& rhs) :
	Attributed(std::move(rhs))
{
}

AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs)
{
	if (this != &rhs)
	{
		Attributed::operator=(std::move(rhs));
	}

	return *this;
}

AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
{
	if (this != &rhs)
	{
		Attributed::operator=(rhs);
	}

	return *this;
}

AttributedFoo::~AttributedFoo()
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		externalStringArray[i].clear();
	}
}

void AttributedFoo::PopulateInternal()
{
	AddInternalAttribute("InternalIntArray",    1, size);
	AddInternalAttribute("InternalFloatArray",  1.0f, size);
	AddInternalAttribute("InternalStringArray", "Jose", size);
	AddInternalAttribute("InternalVectorArray", glm::vec4(internalVector), size);
	AddInternalAttribute("InternalMatrixArray", glm::mat4x4(internalMatrix), size);

	Scope* scope = new Scope();
	scope->Append("Health") = 100;
	AddScope("InternalScope", *scope);
}

void AttributedFoo::PopulateExternal()
{
	AddExternalAttribute("ExternalIntArray",    externalIntArray,    size);
	AddExternalAttribute("ExternalFloatArray",  externalFloatArray,  size);
	AddExternalAttribute("ExternalStringArray", externalStringArray, size);
	AddExternalAttribute("ExternalVectorArray", externalVectorArray,    2);
	AddExternalAttribute("ExternalMatrixArray", externalMatrixArray,    1);
}
