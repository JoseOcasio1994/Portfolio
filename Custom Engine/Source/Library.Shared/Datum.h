#pragma once
#include "pch.h"
#include <cstdint>
#include "../../External/glm/glm.hpp"
#include "../../External/glm/ext.hpp"

//using namespace Library;

namespace FieaGameEngine
{
	class Scope;

	class Datum final
	{
	public:

		/// Enum Of Data Types To Store
		enum DatumType
		{
			Unknown = 0, /// Default Type of Unknown
			Integer,	 /// Type of std::int32_t
			Float,		 /// Type of std::float_t
			Vector,		 /// Type of glm::vec4
			Matrix,		 /// Type of glm::mat4x4
			Table,		 /// Type of Scope
			String,		 /// Type of std::string
			Pointer		 /// Type of RTTI*
		};

		/// Union of pointers
		union uValues
		{
			std::int32_t*	uInteger;	/// Pointer of std::int32_t
			std::float_t*	uFloat;		/// Pointer of std::float_t
			glm::vec4*		uVector;	/// Pointer of glm::vec4
			glm::mat4x4*	uMatrix;	/// Pointer of glm::mat4x4
			Scope**			uTable;		/// Pointer Scope*
			std::string*	uString;	/// Pointer of std::string
			RTTI** uPointer;			/// Pointer of RTTI*

			void* uVoid;				/// Pointer of void

		};

		/** Default Constructor With Optional Defined Type
		@param type An Enum of DataType. Represents the type of data to store
		*/
		explicit Datum(DatumType type = Unknown);

		/** Copy Constructor.
		@param Original A const Datum& to copy
		*/
		Datum(const Datum& Original);
		Datum( Datum&& Original);

		/** Overloaded Assignment Operator
		@param Original A const Datum& to copy
		@return *this after copying Original
		*/
		Datum& operator=(const Datum& Original);
		Datum& operator=(Datum&& Original);

		/** Overloaded Comparison Operator
		@param rhs A const Datum& to compare to
		@return if this datum == rhs
		*/
		bool operator==(const Datum& rhs) const;

		/** Overloaded Not-Comparison Operator
		@param rhs A const Datum& to compare to
		@return !(operator==(rhs))
		*/
		bool operator!=(const Datum& rhs) const;

		bool operator==(const std::int32_t& rhs) ;

		bool operator==(const std::float_t& rhs);

		bool operator==(const glm::vec4& rhs);

		bool operator==(const glm::mat4x4& rhs);

		bool operator==(const Scope* rhs);

		bool operator==(const std::string& rhs);

		bool operator==(const RTTI* rhs);

		/** Overloaded Assignment Operator. 
		* Sets mSize to 1 if size == 0.
		* Sets mType to Integer if mType == Unknown
		@param rhs A std::int32_t& to copy
		*/
		void operator=(const std::int32_t rhs);

		/** Overloaded Assignment Operator.
		* Sets mSize to 1 if size == 0.
		* Sets mType to Float if mType == Unknown
		@param rhs A std::float_t& to copy
		*/
		void operator=(const std::float_t rhs);

		/** Overloaded Assignment Operator.
		* Sets mSize to 1 if size == 0.
		* Sets mType to Vector if mType == Unknown
		@param rhs A glm::vec4& to copy
		*/
		void operator=(const glm::vec4& rhs);

		/** Overloaded Assignment Operator.
		* Sets mSize to 1 if size == 0.
		* Sets mType to Matrix if mType == Unknown
		@param rhs A glm::mat4x4& to copy
		*/
		void operator=(const glm::mat4x4& rhs);

		/** Overloaded Assignment Operator.
		* Sets mSize to 1 if size == 0.
		* Sets mType to Table if mType == Unknown
		@param rhs A Scope*& to copy
		*/
		void operator=(Scope* rhs);

		/** Overloaded Assignment Operator.
		* Sets mSize to 1 if size == 0.
		* Sets mType to String if mType == Unknown
		@param rhs A std::string& to copy
		*/
		void operator=(const std::string& rhs);

		/** Overloaded Assignment Operator.
		* Sets mSize to 1 if size == 0.
		* Sets mType to Pointer if mType == Unknown
		@param rhs A RTTI*& to copy
		*/
		void operator=(RTTI* rhs);

		Scope& operator[](std::uint32_t index) { return *Get<Scope*>(index); }

		/** Overloaded Destructor
		* Calls Clear() to empty the list, and frees mValues()
		*/
		~Datum();

		/** Return mType, the type of data this object stores
		@return mType, the type of data this object stores
		*/
		DatumType Type() const;

		/** Set the type of data to store.
		* Does Nothing if already Set (mType != Unknown)
		@param type A const DatumType& that is the type to set to
		*/
		void SetType(const DatumType& type);

		/** Return mSize, the amount of data stored
		@return mSize, the amount of data stored
		*/
		std::uint32_t Size() const;

		/** Set the amount of data to store.
		* Does Not Shrink mCapacity.
		* Sets any new memory to nullptr
		@param size A const std::uint32_t& that is the amount of data to store
		*/
		void Reserve(const std::uint32_t& size);

		/** Insert Data To End of list. 
		* set mType to Integer if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A std::uint32_t& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(const std::int32_t& data);

		/** Insert Data To End of list.
		* set mType to Float if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A std::float_t& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(const std::float_t& data);

		/** Insert Data To End of list.
		* set mType to Vector if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A glm::vec4& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(const glm::vec4& data);

		/** Insert Data To End of list.
		* set mType to Matrix if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A glm::mat4x4& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(const glm::mat4x4& data);

		/** Insert Data To End of list.
		* set mType to Matrix if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A Scope*& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(Scope* data);

		/** Insert Data To End of list.
		* set mType to String if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A std::string& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(const std::string& data);

		/** Insert Data To End of list.
		* set mType to Pointer if Unknown
		* Increase mCapacity by 10 if full
		* Throw exception if storage is external
		@param data A RTTI*& that is the data to insert
		@exception mIsInternal == false, meaning you dont own this data
		*/
		void Pushback(RTTI* data);

		/** Clear the List Without Changing mCapacity
		* If mIsInternal is true, delete each element in mValues
		* else, set each element in mValues to nullptr
		*/
		void Clear();

		/** CLear() On Integers */
		void ClearInt();

		/** CLear() On Floats */
		void ClearFloat();

		/** CLear() On Vectors */
		void ClearVector();

		/** CLear() On Matrix */
		void ClearMatrix();

		/** CLear() On Scopes */
		void ClearTable();

		/** CLear() On Strings */
		void ClearString();

		/** CLear() On Pointers */
		void ClearPointer();

		/* Mark Data As External. Set Size/Capacity To Size Of Data to store.
		* Copy the data into mValues. Set mType To Integer If Unknown.
		* Throw exception if mType is not Integer.
		@exception mType is not an Integer, except for Unknown
		@param Data An std::int32_t*. An Array of data to store.
		@param Size A const std::uint32_t&. The Size of the array
		*/
		void SetStorage(const std::int32_t* data, const std::uint32_t& size);

		/* See SetStorage(std::int32_t *data, const std::uint32_t& size). 
		* Stores Floats Instead
		*/
		void SetStorage(const std::float_t* data, const std::uint32_t& size);

		/* See SetStorage(std::int32_t *data, const std::uint32_t& size). 
		* Stores glm::vec4 Instead
		*/
		void SetStorage(const glm::vec4* data, const std::uint32_t& size);

		/* See SetStorage(std::int32_t *data, const std::uint32_t& size).
		* Stores glm::mat4x4 Instead
		*/
		void SetStorage(const glm::mat4x4* data, const std::uint32_t& size);

		/* See SetStorage(std::int32_t *data, const std::uint32_t& size).
		* Stores Strings Instead
		*/
		void SetStorage(const std::string* data, const std::uint32_t& size);

		/* See SetStorage(std::int32_t *data, const std::uint32_t& size).
		* Stores RTTI* Instead
		*/
		void SetStorage( RTTI** data, const std::uint32_t& size);

		/* Modify the data at Index. Set mType To Integer If Unknown.
		* Throw Exception If Not Integer. Increase Capacity If Index Out of Range.
		@exception mType is not Integer, except unknown
		@param data std::int32_t data to insert
		@param index std::uint32_t location to store data
		*/
		void Set(const std::int32_t& data, std::uint32_t index = 0);

		/*See Set(std::int32_t& data, std::uint32_t index = 0);
		* Sets Floats Instead
		*/
		void Set(const std::float_t& data, std::uint32_t index = 0);

		/*See Set(std::int32_t& data, std::uint32_t index = 0);
		* Sets glm::vec4 Instead
		*/
		void Set(const glm::vec4& data, std::uint32_t index = 0);

		/*See Set(std::int32_t& data, std::uint32_t index = 0);
		* Sets glm::mat4x4 Instead
		*/
		void Set(const glm::mat4x4& data, std::uint32_t index = 0);

		/*See Set(std::int32_t& data, std::uint32_t index = 0);
		* Sets Scope* Instead
		*/
		void Set(Scope* data, std::uint32_t index = 0);

		/*See Set(std::int32_t& data, std::uint32_t index = 0);
		* Sets Strings Instead
		*/
		void Set(const std::string& data, std::uint32_t index = 0);

		/*See Set(std::int32_t& data, std::uint32_t index = 0);
		* Sets RTTI* Instead
		*/
		void Set(RTTI* data, std::uint32_t index = 0);

		template <typename T> T Get(std::uint32_t index = 0);

		/*Get int value stored at index. Throw exception if index is out of range or mType is different
		*exception Index is out of range or mType is different
		@param index std::uint32_t location to grab data from
		@return an std::int32_t value
		*/
		template <> std::int32_t Get<std::int32_t>(std::uint32_t index)
		{
			if (mType != Integer)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uInteger[index];
		}

		/*See Get<std::int32_t>
		  Returns std::float_t instead
		*/
		template <> std::float_t Get<std::float_t>(std::uint32_t index)
		{
			if (mType != Float)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uFloat[index];
		}

		/*See Get<std::int32_t>
		Returns glm::vec4 instead
		*/
		template <> glm::vec4 Get<glm::vec4>(std::uint32_t index)
		{
			if (mType != Vector)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uVector[index];
		}

		/*See Get<std::int32_t>
		Returns glm::mat4x4 instead
		*/
		template <> glm::mat4x4 Get<glm::mat4x4>(std::uint32_t index)
		{
			if (mType != Matrix)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uMatrix[index];
		}

		/*See Get<std::int32_t>
		Returns Scope* instead
		*/
		template <> Scope* Get<Scope*>(std::uint32_t index)
		{
			if (mType != Table)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uTable[index];
		}

		/*See Get<std::int32_t>
		Returns std::string instead
		*/
		template <> std::string Get<std::string>(std::uint32_t index)
		{
			if (mType != String)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uString[index];
		}

		/*See Get<std::int32_t>
		Returns RTTI* instead
		*/
		template <> RTTI* Get<RTTI*>(std::uint32_t index)
		{
			if (mType != Pointer)
				throw std::exception("Current Type Is Different From Requested Type");

			if (index >= mSize)
				throw std::exception("Out Of Range");

			return mValues.uPointer[index];
		}

		/* Set value at index by parsing a string
		@param data std::string to parse value from
		@param std::uint32_t location to store data in
		@exception several, depending on type. Can't Set If Type is Unknown
		*/
		void SetFromString(const std::string data, std::uint32_t index = 0);

		/*See SetFromString(). Stores An Int.
		*No exceptions.
		*/
		void IntFromString(const std::string data, std::uint32_t index = 0);

		/*See SetFromString(). Stores A Float.
		@exception If multiple '-', multiple '.', or any non-numeric characters found
		*/
		void FloatFromString(const std::string data, std::uint32_t index = 0);

		/*See SetFromString(). Stores A glm::vec4.
		*exception If any alphabet characters found
		*/
		void VectorFromString(const std::string data, std::uint32_t index = 0);

		/*See SetFromString(). Stores A glm::mat4x4.
		*exception If any alphabet characters found
		*/
		void MatrixFromString(const std::string data, std::uint32_t index = 0);

		void TableFromString(const std::string data, std::uint32_t index = 0);

		/*See SetFromString(). Stores A String
		*No Exceptions.
		*/
		void StringFromString(const std::string data, std::uint32_t index = 0);

		void PointerFromString(const std::string data, std::uint32_t index = 0);

		/* Turn value at index into a string. Throw exception if out of range or unknown type
		@exception index out of range or type is unknown
		@param index std::uint32_t location of value to convert to String
		*/
		std::string ToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string IntToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string FloatToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string VectorToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string MatrixToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string TableToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string StringToString(std::uint32_t index = 0);

		/*See ToString()*/
		std::string PointerToString(std::uint32_t index = 0);

		bool RemoveTable(const Scope* scope);

	private:

		DatumType mType;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		uValues mValues;
		bool mIsInternal;

	};

}