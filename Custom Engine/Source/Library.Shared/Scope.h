#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class Datum;

	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI);

	protected:
		
		typedef std::pair<std::string, Datum> PairType;
		typedef HashMap<std::string, Datum> Table;
		typedef Table::Iterator Iterator;
		typedef Vector<PairType*> TablePointers;

		Scope* mParent;
		Table mTable;
		TablePointers mTablePointers;
		std::uint32_t mSize;
		static const std::uint32_t defaultHashSize = 5;
		
		/* remove this child from its parent*/
		void Orphan();
		void Reparent(Scope& scope);

	public:
		
		/* Default Constructor With Optional Default Size For Expected Amount Of Elements
		@params size std::uint32_t the amount of memory to reserve for hashmap pointers
		*/
		explicit Scope(std::uint32_t size = defaultHashSize);

		/* Copy Constructor
		@param Original const Scope& the scope to copy\
		*/
		Scope(const Scope& Original);
		Scope(Scope&& Original);

		/* Overloaded Assignment Operator
		@param Original const Scope& the scope to copy
		@returns *this
		*/
		Scope& operator=(const Scope& Original);
		Scope& operator=(Scope&& Original);

		/* Virtual Destructor*/
		virtual ~Scope();

		/* Overloaded [] Operator. Takes a string, looks for it in the hashmap, and returns the datum
		stored at that location. Appends an empty datum if not found
		@param name const std::string the name of a datum to find
		@returns a Datum& stored at location name
		*/
		Datum& operator[](const std::string name);

		/* Overloaded [] Operator. Takes an int, goes into that position in vector, and returns the datum
		stored at that location. Exception if out of bound
		@exception index out of bound
		@param index const std::uint32_t position into vector
		@returns a Datum& stored at index
		*/
		Datum& operator[](const std::uint32_t index);

		/* Overloaded == Operator. Returns if this == rhs by comparing size, then the contents
		@param rhs const Scope& to compare self to
		@returns true if this == rhs
		*/
		bool operator==(const Scope& rhs);

		/* Overloaded != Operator. Returns the opposite of ==
		@param rhs const Scope& to compare self to
		@returns true if this != rhs
		*/
		bool operator!=(const Scope& rhs);

		/* Return the amount of elements stored in this scope
		@returns mSize
		*/
		std::uint32_t Size() const;

		/* Find the datum stored with a given name in this scope only
		@param name const std::string the name of the datum to search for
		@returns a pointer to datum with given name, returns nullptr if not found
		*/
		Datum* Find(const std::string name) const;

		/* Same as Find(), but looks through parents also until name is found
		@param name const std::string the name of the datum to search for
		@returns a pointer to datum with given name, returns nullptr if not found
		*/
		Datum* Search(const std::string name, Scope** scope = nullptr) const;

		/* Add a new entry into the table with the given name if it does not exist.
		* If a name already exists, return that name
		@param name const std::string the name to give the datum
		@returns a reference to the datum with the given name
		*/
		Datum& Append(const std::string name);

		/* Same as Append(), except it throws exception if existing name is not a Scope, else it appends
		* the scope to itself.
		@exception if name exists AND is not a scope
		@param name const std::string the name to give the datum
		@returns a reference to the Scope with the given name
		*/
		Scope& AppendScope(const std::string name);

		/* Add a scope by taking it from another scope
		@exception if name exists AND is not a scope
		@param scope Scope& the scope to adopt
		@param name const std::string the name to give the datum
		*/
		void Adopt(Scope& scope, const std::string name);

		/* Return the parent of this scope
		@returns the parent of this scope, nullptr if no parent
		*/
		Scope* GetParent() const;

		/* Find the name of this scope by looking for it through its parent
		@param scope const scope& the address of this scope
		@return std::string the name of this scope
		*/
		std::string FindName(const Scope& scope) const;

		/* remove all elements from this scope*/
		void Clear();

		PairType* GetPair(std::uint32_t i);
	};
}