#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class SharedData;

	class XMLParseHelper : public RTTI
	{

	protected:
		bool mIsInitialized = false;

	public:

		typedef HashMap<std::string, std::string> xmlHashMap;

		/** Initialize This Helper*/
		virtual void Initialize() = 0;

		/** Try to handle The Data. If So, return true, false otherwise
		@params name a const std::string reference that is the name of the element
		@params attributes a const reference to a hashmap of <std::string, std::string> that is the name-value pair
		@returns bool if data was handled or not
		*/
		virtual bool StartElementHandler(const std::string& name, const xmlHashMap& attributes, SharedData* data) = 0;

		/** Try to handle The Data. If So, return true, false otherwise
		@params name a const std::string reference that is the name of the element
		@returns a pointer to a datum signature, nullptr if not found
		*/
		virtual bool EndElementHandler(const std::string& name, SharedData* data) = 0;

		/** Try to handle The Data.
		@params buffer a const char* that is the data to handle
		@params length size of buffer
		*/
		virtual bool CharDataHandler(const char* buffer,const std::uint32_t length, SharedData* data) = 0;

		/** Return a copy of self
		@returns a reference to a copy of self
		*/
		virtual XMLParseHelper& Clone() = 0;
		
		virtual bool GetInitialized()
		{
			return mIsInitialized;
		}

	};
}