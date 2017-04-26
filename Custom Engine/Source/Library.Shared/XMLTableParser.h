#pragma once
#include "pch.h"
#include "Datum.h"
#include "Scope.h"

namespace FieaGameEngine
{
	class XMLTableParser : public XMLParseHelper
	{
		RTTI_DECLARATIONS(XMLTableParser, RTTI);

	private:

		enum State
		{
			None = 0,
			If,
			Condition,
			Then,
			Else
		};

		bool IntHandler(const xmlHashMap& attributes);
		bool FloatHandler(const xmlHashMap& attributes);
		bool VectorHandler(const xmlHashMap& attributes);
		bool MatrixHandler(const xmlHashMap& attributes);
		bool StringHandler(const xmlHashMap& attributes);
		bool ScopeHandler(const xmlHashMap& attributes);
		bool WorldHandler(const xmlHashMap& attributes, const std::uint32_t depth);
		bool SectorHandler(const xmlHashMap& attributes);
		bool EntityHandler(const xmlHashMap& attributes);
		bool ActionHandler(const xmlHashMap& attributes);
		bool ActionIfHandler(const std::string& name, const xmlHashMap& attributes);

		Scope* curScope;
		State mState;

	public:

		void Initialize() override;
		bool StartElementHandler(const std::string& name, const xmlHashMap& attributes, SharedData* data) override;
		bool EndElementHandler(const std::string& name, SharedData* data) override;
		bool CharDataHandler(const char* buffer, const std::uint32_t length, SharedData* data) override;
		XMLParseHelper& Clone() override;
		
	};
}