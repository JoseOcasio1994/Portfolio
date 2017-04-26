#pragma once
#include "pch.h"
#include <cstdint>
#include "Scope.h"
#include "../../External/glm/glm.hpp"
#include "../../External/glm/ext.hpp"

namespace FieaGameEngine
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

		typedef std::pair<std::uint64_t, Vector<std::string>> pairType;
		typedef HashMap<std::uint64_t, Vector<std::string>> attrHash;

	private:

		static attrHash mPrescribedAttributes;

		/** Return pointer to the signature of datum with name, nullptr if name not found
		@params name a const std::string reference that is the name of the datum to find
		@returns a pointer to a datum signature, nullptr if not found
		*/
		Vector<std::string>* GetSignature(std::uint64_t id);
		void AddSignature(std::string name);

	public:

		/** Default Constructor
		*/
		Attributed();

		/** Virtual Destructor
		*/
		virtual ~Attributed() = 0;

		/** Copy Constructor
		@param Original a const Attributed reference to copy
		*/
		Attributed(const Attributed& Original);

		/** Overloaded Assignment Operator
		@param Original a const Attributed reference to copy
		@returns *this after possibly copying data
		*/
		Attributed& operator=(const Attributed& Original);

		/** Move Constructor
		@param Original a Attributed&& to take data from
		*/
		Attributed(Attributed&& Original);

		/** Overloaded Move Operator
		@param Original a Attributed&& to take data from
		@returns *this after possibly copying data
		*/
		Attributed& operator=(Attributed&& Original);

		/** Check if the datum with given name is an attribute by using the Find()
		* method that is inside the Scope base class
		@param name a const std::string& that is the name to look for
		@returns true if the name is an attribute
		*/
		bool IsAttribute(const std::string& name);

		/** Check if the datum with given name is a precribed attribute by calling isAttribute()
		* to check if it is an attribute first, then checking if the Signature Exists.
		@param name a const std::string& that is the name to look for
		@returns true if the name is a prescribed attribute
		*/
		bool IsPrescribedAttribute(const std::string& name);

		/** Check if the datum with given name is an auxiliary attribute by 
		* doing the opposite of isPrescribedAttribute
		@param name a const std::string& that is the name to look for
		@returns true if the name is an auxiliary attribute
		*/
		bool IsAuxiliaryAttribute(const std::string& name);

		/** Add an auxiliary attribute. This is a tin wrapper to append that just checks if
		* an existing name is a prescribed attribute
		@param name a const std::string& that is the name to append
		@exception existing name is a prescribed attribute
		@returns Datum& to added attribute
		*/
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/** Return start of Auxiliary list
		@exception no auxiliary attributes exist
		@returns a std::uint32_t that is the location of the first auxiliary attribute
		*/
		std::uint32_t AuxiliaryBegin();

	protected:

		/* Add an internal attribute to the list. 5 Overloads
		@param name a const std::string& that is the name of the attribute
		@param value a int/float/string/glm::vec4/glm::mat4x4 that is the data to store
		@param size a std::uint32_t that is the amount of data to add
		@returns a Datum& to the added attribute
		*/
		Datum& AddInternalAttribute(const std::string& name, std::int32_t value, std::uint32_t size);
		Datum& AddInternalAttribute(const std::string& name, std::float_t value, std::uint32_t size);
		Datum& AddInternalAttribute(const std::string& name, std::string value, std::uint32_t size);
		Datum& AddInternalAttribute(const std::string& name, glm::vec4 value, std::uint32_t size);
		Datum& AddInternalAttribute(const std::string& name, glm::mat4x4 value, std::uint32_t size);
		Datum& AddInternalAttribute(const std::string& name, RTTI** value, std::uint32_t size);

		/* Add an external attribute to the list. 6 Overloads
		@param name a const std::string& that is the name of the attribute
		@param value a pointer to an int/float/string/glm::vec4/glm::mat4x4/RTTI* that is the data to store
		@param size a std::uint32_t that is the amount of data to add
		@returns a Datum& to the added attribute
		*/
		Datum& AddExternalAttribute(const std::string& name, const std::int32_t* value, std::uint32_t size);
		Datum& AddExternalAttribute(const std::string& name, const std::float_t* value, std::uint32_t size);
		Datum& AddExternalAttribute(const std::string& name, const std::string* value, std::uint32_t size);
		Datum& AddExternalAttribute(const std::string& name, const glm::vec4* value, std::uint32_t size);
		Datum& AddExternalAttribute(const std::string& name, const glm::mat4x4* value, std::uint32_t size);
		Datum& AddExternalAttribute(const std::string& name, RTTI** value, std::uint32_t size);


		/** Same as AddAttribute, except always internal
		@param name a const std::string& that is the name of the data
		@param scope an optional const scope pointer that is the value of the scope to added
		@returns a reference to the added scope
		*/
		Scope& AddScope(const std::string& name, Scope& scope);
	};
}