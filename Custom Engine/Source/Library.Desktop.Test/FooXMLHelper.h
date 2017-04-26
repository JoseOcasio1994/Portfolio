#pragma once

#include "pch.h"

namespace FieaGameEngine
{
	class FooXMLHelper : public XMLParseHelper
	{
		RTTI_DECLARATIONS(FooXMLHelper, RTTI);

	public:
		~FooXMLHelper();
		void Initialize() override;
		bool StartElementHandler(const std::string& name, const xmlHashMap& attributes, SharedData* data) override;
		bool EndElementHandler(const std::string& name, SharedData* data) override;
		bool CharDataHandler(const char* buffer, const std::uint32_t length, SharedData* data) override;
		XMLParseHelper& Clone() override;
	};
}