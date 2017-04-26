#pragma once

#include "pch.h"
#include "Attributed.h"

namespace FieaGameEngine
{
	class AttributedFoo : public Attributed
	{

	private:

		std::int32_t  externalIntArray[5] = {6,7,8,9,10};
		std::float_t externalFloatArray[5] = { 6,7,8,9,10 };
		std::string  externalStringArray[5] = { "f", "g", "h", "i", "j" };
		glm::vec4	  internalVector = {1,2,3,4} , externalVectorArray[2] = { {2,4,6,8}, {2,4,6,8} };
		glm::mat4x4   internalMatrix = { internalVector,internalVector, internalVector, internalVector };
		glm::mat4x4   externalMatrixArray[1] = { { 2 * internalMatrix } };
		
		std::uint32_t size = 5;

	public:

		AttributedFoo();
		AttributedFoo(const AttributedFoo& rhs);
		AttributedFoo(AttributedFoo&& rhs);
		AttributedFoo& operator=(const AttributedFoo& rhs);
		AttributedFoo& operator=(AttributedFoo&& rhs);
		~AttributedFoo();

		void PopulateInternal();
		void PopulateExternal();
	};
}