#pragma once
#include "pch.h"
#include <cstdint>
#include "..\..\External\Expat\source\expat.h"

#define BUFFERSIZE 128

namespace FieaGameEngine
{
	class SharedData;

	class XMLParseMaster : public RTTI
	{
		RTTI_DECLARATIONS(XMLParseMaster, RTTI);
		friend class SharedData;

	public:

		/** Default Constructor with mandatory Data reference
		@param Data const SharedData& the data to be shared with helpers
		*/
		XMLParseMaster(const SharedData& Data);

		XMLParseMaster(const XMLParseMaster& rhs) = delete;
		XMLParseMaster(XMLParseMaster&& rhs) = delete;

		virtual ~XMLParseMaster();

		/** Return a copy of self
		@returns a copy of self
		*/
		XMLParseMaster& Clone();

		/** Add a reference to a parsehelper
		@params helper a const XMLParseHelper reference that is the helper to add
		@exception If this object is a clone
		*/
		void AddHelper(const XMLParseHelper& helper);

		/** Remove a helper and return a bool if it was removed
		@params helper a const XMLParseHelper reference that is the helper to remove
		@returns a bool if the helper was removed
		*/
		bool RemoveHelper(const XMLParseHelper& helper);

		/** Thin wrapper to Expat's xml_parse function
		@param buffer char* that is the data to parse
		@param length size of buffer, since it is not null terminated
		@param lastChunk bool if buffer is the last data to parse
		*/
		void Parse(const char* buffer, int length, bool lastChunk);

		/** Parse a file
		@params name std::string that is the name of the file
		@exception File Not Found
		*/
		void ParseFromFile(const std::string& fileName);

		/** Return path of file being parsed
		@returns path of file being parsed
		*/
		std::string& GetFileName();

		/** Set that data to be shared between helpers
		@params data the SharedData to refer to
		@exception If this object is a clone
		*/
		void SetSharedData(const SharedData& data);

		/** Return the data that is being referred to
		@returns the data that is being referred to
		*/
		SharedData* GetSharedData();

	private:

		Vector<XMLParseHelper*> mHelpers;
		XML_Parser mParser;
		std::string mFile, mCharData;
		SharedData* mSharedData;
		bool isClone;

		/** Expat Callback for StartElement */
 		static void StartElementHandler(void *userData, const char *name, const char **attribute);
		/** Expat Callback for EndElement */
		static void EndElementHandler(void *userData, const char *name);
		/** Expat Callback for CharData */
		static void CharDataHandler(void *userData, const char *val, int len);
	};

	class SharedData : public RTTI
	{
		RTTI_DECLARATIONS(SharedData, RTTI);
		friend class XMLParser;
	protected:

		XMLParseMaster* mMasterPointer;
		std::uint32_t mDepth = 0;

	public:
		/** Return a copy of self
		@returns a copy of self
		*/
		virtual SharedData& Clone() = 0;

		/** Set a pointer to an xmlParseMaster
		@params master a const XMLParseMaster* that is the owner of this data
		*/
		void SetXMLParseMaster(const XMLParseMaster* master = nullptr);

		/** Return a pointer to XMLParseMaster
		@returns a pointer to XMLParseMaster
		*/
		XMLParseMaster* GetXMLParseMaster();

		/** Increment Depth, how many start tags we hit
		*/
		void IncrementDepth();

		/** Decrement Depth, how many end tags we hit
		*/
		void DecrementDepth();

		/** Return how far down we are in the xml
		@returns how far down we are in the xml
		*/
		std::uint32_t Depth();

	};

}