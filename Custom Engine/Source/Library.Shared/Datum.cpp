
#include "pch.h"
#include "Datum.h"

using namespace FieaGameEngine;

typedef std::string(Datum::*Funcs)(std::uint32_t index);
Funcs functions[8] = { nullptr, &Datum::IntToString,    &Datum::FloatToString,
&Datum::VectorToString, &Datum::MatrixToString,
&Datum::TableToString,  &Datum::StringToString,
&Datum::PointerToString };

typedef void (Datum::*setStrFuncs)(std::string data, std::uint32_t index);
setStrFuncs setStrFunctions[8] = { nullptr, &Datum::IntFromString, &Datum::FloatFromString, &Datum::VectorFromString,
&Datum::MatrixFromString, &Datum::TableFromString, &Datum::StringFromString,
&Datum::PointerFromString };

typedef void (Datum::*clearFuncs)();
clearFuncs clearFunctions[8] = { nullptr, &Datum::ClearInt, &Datum::ClearFloat, &Datum::ClearVector,
&Datum::ClearMatrix, &Datum::ClearTable,
&Datum::ClearString,&Datum::ClearPointer };

#pragma region CONSTRUCTORS_AND_OPERATORS

Datum::Datum(DatumType type) :
	mSize(0), mCapacity(0), mType(type), mIsInternal(true)
{
	mValues.uVoid = nullptr;
}

Datum::Datum(const Datum& Original) :
	mSize(0), mCapacity(0), mType(Unknown), mIsInternal(true)
{
	mValues.uVoid = nullptr;
	operator=(Original);
}

Datum::Datum(Datum&& Original) :
	mType(Original.mType), mSize(Original.mSize), mCapacity(Original.mCapacity),
	mIsInternal(Original.mIsInternal), mValues(Original.mValues)
{
	Original.mType = Unknown;
	Original.mSize = 0;
	Original.mCapacity = 0;
	Original.mIsInternal = true;
	Original.mValues.uVoid = nullptr;
}

Datum& Datum::operator=(const Datum& Original)
{
	if (this != &Original)
	{
		Clear();
		mCapacity = 0;
		mType = Original.mType;
		Reserve(Original.mSize);
		mSize = Original.mSize;


		if (mType == Pointer)
		{
			SetStorage(Original.mValues.uPointer, Original.mSize);
		}
		else
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				switch (mType)
				{
				case Integer:
					mValues.uInteger[i] = Original.mValues.uInteger[i];
					break;

				case Float:
					mValues.uFloat[i] = Original.mValues.uFloat[i];
					break;

				case Vector:
					mValues.uVector[i] = Original.mValues.uVector[i];
					break;

				case Matrix:
					mValues.uMatrix[i] = Original.mValues.uMatrix[i];
					break;

				case Table:
					mValues.uTable[i] = Original.mValues.uTable[i];
					break;

				case String:
					mValues.uString[i] = Original.mValues.uString[i];
					break;

				default:
					break;
				}
			}

	}

	return *this;
}

Datum& Datum::operator=(Datum&& Original)
{
	if (this != &Original)
	{
		Clear();

		mType = Original.mType;
		mSize = Original.mSize;
		mCapacity = Original.mCapacity;
		mIsInternal = Original.mIsInternal;
		mValues = Original.mValues;

		Original.mType = Unknown;
		Original.mSize = 0;
		Original.mCapacity = 0;
		Original.mIsInternal = true;
		Original.mValues.uVoid = nullptr;
	}

	return *this;
}

void Datum::operator=(const std::int32_t rhs)
{
	if (mType == Unknown)
		mType = Integer;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	mValues.uInteger[0] = rhs;
}

void Datum::operator=(const std::float_t rhs)
{
	if (mType == Unknown)
		mType = Float;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	mValues.uFloat[0] = std::float_t(rhs);
}

void Datum::operator=(const glm::vec4& rhs)
{
	if (mType == Unknown)
		mType = Vector;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	mValues.uVector[0] = glm::vec4(rhs);
}

void Datum::operator=(const glm::mat4x4& rhs)
{
	if (mType == Unknown)
		mType = Matrix;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	mValues.uMatrix[0] = glm::mat4x4(rhs);
}

void Datum::operator=(Scope* rhs)
{
	if (mType == Unknown)
		mType = Table;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	Set(rhs);
}

void Datum::operator=(const std::string& rhs)
{
	if (mType == Unknown)
		mType = String;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	Set(rhs);
}

void Datum::operator=(RTTI* rhs)
{
	if (mType == Unknown)
		mType = Pointer;

	if (mCapacity == 0)
	{
		Reserve(1);
		mSize = 1;
	}

	Set(rhs);
}

bool Datum::operator==(const Datum & rhs) const
{
	if (mType != rhs.mType || mSize != rhs.mSize)
		return false;

	for (std::uint32_t i = 0; i < mSize; ++i)
	{
		switch (mType)
		{
		case Integer:
			if (mValues.uInteger[i] != rhs.mValues.uInteger[i])
				return false;
			break;

		case Float:
			if (mValues.uFloat[i] != rhs.mValues.uFloat[i])
				return false;
			break;

		case Vector:
			if (mValues.uVector[i] != rhs.mValues.uVector[i])
				return false;
			break;

		case Matrix:
			if (mValues.uMatrix[i] != rhs.mValues.uMatrix[i])
				return false;
			break;

		case Table:
			if (mValues.uTable[i] != rhs.mValues.uTable[i])
				return false;
			break;

		case String:
			if (mValues.uString[i] != rhs.mValues.uString[i])
				return false;
			break;

		case Pointer:
			if (mValues.uPointer[i] != rhs.mValues.uPointer[i])
				return false;
			break;

		default:
			break;
		}
	}

	return true;
}

bool Datum::operator!=(const Datum & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator==(const std::int32_t& rhs)
{
	return mValues.uInteger[0] == rhs;
}

bool Datum::operator==(const std::float_t& rhs)
{
	return mValues.uFloat[0] == rhs;
}

bool Datum::operator==(const glm::vec4& rhs)
{
	return mValues.uVector[0] == rhs;
}

bool Datum::operator==(const glm::mat4x4& rhs)
{
	return mValues.uMatrix[0] == rhs;
}

bool Datum::operator==(const Scope* rhs)
{
	return mValues.uTable[0] == rhs;
}

bool Datum::operator==(const std::string& rhs)
{
	return mValues.uString[0] == rhs;
}

bool Datum::operator==(const RTTI* rhs)
{
	return mValues.uPointer[0] == rhs;
}

Datum::~Datum()
{
	Clear();
}

#pragma endregion

#pragma region TYPE_AND_SIZE

Datum::DatumType Datum::Type() const
{
	return mType;
}

void Datum::SetType(const DatumType& type)
{
	if (mType == Unknown)
		mType = type;
	else
		throw std::exception("Type Already Set. Can't Change Type.");
}

std::uint32_t Datum::Size() const
{
	return mSize;
}

void Datum::Reserve(const std::uint32_t& size)
{
	if (mIsInternal && mCapacity < size)
	{
		switch (mType)
		{
		case Integer:
			mValues.uInteger = (std::int32_t*)realloc(mValues.uInteger, size * sizeof(std::int32_t));
			break;
		case Float:
			mValues.uFloat = (std::float_t*)realloc(mValues.uFloat, size * sizeof(std::float_t));
			break;
		case Vector:
			mValues.uVector = (glm::vec4*)realloc(mValues.uVector, size * sizeof(glm::vec4));
			break;
		case Matrix:
			mValues.uMatrix = (glm::mat4x4*)realloc(mValues.uMatrix, size * sizeof(glm::mat4x4));
			break;
		case Table:
			mValues.uTable = (Scope**)realloc(mValues.uTable, size * sizeof(Scope*));
			break;
		case String:
			mValues.uString = (std::string*)realloc(mValues.uString, size * sizeof(std::string));
			for (std::uint32_t i = mCapacity; i < size; ++i)
				new (mValues.uString + i)std::string("");
			break;
		case Pointer:
			mValues.uPointer = (RTTI**)realloc(mValues.uPointer, size * sizeof(RTTI*));
			break;
		default:
			return;
		}

		mCapacity = size;
	}
}

#pragma endregion

#pragma region PUSHBACK

// Integer
void Datum::Pushback(const std::int32_t & data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = Integer;

	if (mSize >= mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

// FLoat
void Datum::Pushback(const std::float_t& data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = Float;

	if (mSize == mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

// Vector
void Datum::Pushback(const glm::vec4& data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = Vector;

	if (mSize == mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

// Matrix
void Datum::Pushback(const glm::mat4x4& data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = Matrix;

	if (mSize == mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

// Scope
void Datum::Pushback(Scope* data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = Table;

	if (mSize == mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

// String
void Datum::Pushback(const std::string& data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = String;

	if (mSize == mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

// Pointer
void Datum::Pushback(RTTI* data)
{
	if (!mIsInternal)
		throw std::exception("Can Not PushBack On External Storage");

	if (mType == Unknown)
		mType = Pointer;

	if (mSize == mCapacity)
		Reserve(mSize + 1);

	Set(data, mSize++);
}

#pragma endregion

#pragma region CLEAR

void Datum::Clear()
{
	if (mType != Unknown)
		(this->*clearFunctions[mType])();
}

void Datum::ClearInt()
{
	if (mIsInternal)
	{
		delete mValues.uInteger;
		mValues.uInteger = nullptr;
		mSize = 0;
	}

}

void Datum::ClearFloat()
{
	if (mIsInternal)
	{
		delete mValues.uFloat;
		mValues.uFloat = nullptr;
		mSize = 0;
	}
}

void Datum::ClearVector()
{
	if (mIsInternal)
	{
		delete mValues.uVector;
		mValues.uVector = nullptr;
		mSize = 0;
	}
}

void Datum::ClearMatrix()
{
	if (mIsInternal)
	{
		delete mValues.uMatrix;
		mValues.uMatrix = nullptr;
		mSize = 0;
	}
}

void Datum::ClearTable()
{
	if (mIsInternal)
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			mValues.uTable[i] = nullptr;
		}

		delete mValues.uTable;
		mSize = 0;
	}
}

void Datum::ClearString()
{
	if (mIsInternal)
	{
		for (std::uint32_t i = 0; i < mCapacity; ++i)
		{
			mValues.uString[i].~basic_string();
		}
		delete mValues.uString;
		mValues.uString = nullptr;
		mSize = 0;
	}
}

void Datum::ClearPointer()
{
	if (mIsInternal)
	{
		delete &mValues.uPointer[0];

		mValues.uPointer = nullptr;
		mSize = 0;
	}

}

#pragma endregion

#pragma region SET_STORAGE

// INTEGER
void Datum::SetStorage(const std::int32_t *data, const std::uint32_t& size)
{
	if (mType == Unknown)
		mType = Integer;

	if (mType != Integer)
		throw std::exception("Data Is Of Different Type. Current Type: Integer");

	Clear();
	mCapacity = mSize = size;

	mIsInternal = false;

	mValues.uInteger = const_cast<std::int32_t*>(data);
}

// FLOAT
void Datum::SetStorage(const std::float_t* data, const std::uint32_t& size)
{
	if (mType == Unknown)
		mType = Float;

	if (mType != Float)
		throw std::exception("Data Is Of Different Type. Current Type: Float");

	Clear();
	mCapacity = mSize = size;

	mIsInternal = false;

	mValues.uFloat = const_cast<std::float_t*>(data);
}

// VECTOR
void Datum::SetStorage(const glm::vec4* data, const std::uint32_t& size)
{
	if (mType == Unknown)
		mType = Vector;

	if (mType != Vector)
		throw std::exception("Data Is Of Different Type. Current Type: Vector4");

	Clear();
	mCapacity = mSize = size;

	mIsInternal = false;

	mValues.uVector = const_cast<glm::vec4*>(data);
}

// Matrix
void Datum::SetStorage(const glm::mat4x4* data, const std::uint32_t& size)
{
	if (mType == Unknown)
		mType = Matrix;

	if (mType != Matrix)
		throw std::exception("Data Is Of Different Type. Current Type: Matrix 4x4");

	Clear();
	mCapacity = mSize = size;

	mIsInternal = false;

	mValues.uMatrix = const_cast<glm::mat4x4*>(data);
}

// STRING
void Datum::SetStorage(const std::string* data, const std::uint32_t& size)
{
	if (mType == Unknown)
		mType = String;

	if (mType != String)
		throw std::exception("Data Is Of Different Type. Current Type: String");

	Clear();
	mCapacity = mSize = size;

	mIsInternal = false;

	mValues.uString = const_cast<std::string*>(data);
}

// RTTI*
void Datum::SetStorage(RTTI** data, const std::uint32_t& size)
{
	if (mType == Unknown)
		mType = Pointer;

	if (mType != Pointer)
		throw std::exception("Data Is Of Different Type. Current Type: Pointer");

	Clear();
	mCapacity = mSize = size;

	mIsInternal = false;

	mValues.uPointer = data;
}

#pragma endregion

#pragma region SET

// INTEGER
void Datum::Set(const std::int32_t& data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = Integer;

	if (mType != Integer)
		throw std::exception("Data Is Of Different Type. Current Type: Integer");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uInteger[index] = data;
}

// FLOAT
void Datum::Set(const std::float_t& data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = Float;

	if (mType != Float)
		throw std::exception("Data Is Of Different Type. Current Type: Float");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uFloat[index] = data;
}

// VECTOR
void Datum::Set(const glm::vec4& data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = Vector;

	if (mType != Vector)
		throw std::exception("Data Is Of Different Type. Current Type: Vector4");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uVector[index] = data;
}

// MATRIX
void Datum::Set(const glm::mat4x4& data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = Matrix;

	if (mType != Matrix)
		throw std::exception("Data Is Of Different Type. Current Type: Matrix 4x4");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uMatrix[index] = data;
}

// Scope
void Datum::Set(Scope* data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = Table;

	if (mType != Table)
		throw std::exception("Data Is Of Different Type. Current Type: Scope");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uTable[index] = data;
}

// STRING
void Datum::Set(const std::string& data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = String;

	if (mType != String)
		throw std::exception("Data Is Of Different Type. Current Type: String");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uString[index] = data;
}

// RTTI*
void Datum::Set(RTTI* data, std::uint32_t index)
{
	if (mType == Unknown)
		mType = Pointer;

	if (mType != Pointer)
		throw std::exception("Data Is Of Different Type. Current Type: Pointer");

	if (index >= mSize)
		throw std::exception("Index Out Of Bounds");

	mValues.uPointer[index] = data;
}

#pragma endregion

#pragma region SET_FROM_STRING

void Datum::SetFromString(std::string data, std::uint32_t index)
{
	if (mType == Unknown)
		throw std::exception("Can't Set Unknown Type");

	(this->*setStrFunctions[mType])(data, index);
}

void Datum::IntFromString(std::string data, std::uint32_t index)
{
	if (index >= mSize)
		Pushback(stoi(data));
	else
		Set(stoi(data), index);
}

void Datum::FloatFromString(std::string data, std::uint32_t index)
{
	if (index >= mSize)
		Pushback(stof(data));
	else
		Set(stof(data), index);
}

void Datum::VectorFromString(std::string data, std::uint32_t index)
{
	glm::vec4 newData;

	sscanf_s(data.c_str(), "%f %f %f %f", &newData.x, &newData.y, &newData.z, &newData.w);

	if (index >= mSize)
		Pushback(newData);
	else
		Set(newData, index);
}

void Datum::MatrixFromString(std::string data, std::uint32_t index)
{
	glm::vec4 t1, t2, t3, t4;

	sscanf_s(data.c_str(), "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
		&t1.x, &t1.y, &t1.z, &t1.w,
		&t2.x, &t2.y, &t2.z, &t2.w,
		&t3.x, &t3.y, &t3.z, &t3.w,
		&t4.x, &t4.y, &t4.z, &t4.w);

	glm::mat4x4 newData = { t1, t2, t3, t4 };

	if (index >= mSize)
		Pushback(newData);
	else
		Set(newData, index);
}

void Datum::TableFromString(std::string data, std::uint32_t index)
{
	UNREFERENCED_PARAMETER(index);
}

void Datum::StringFromString(std::string data, std::uint32_t index)
{
	if (index >= mSize)
		Pushback(data);
	else
		Set(data, index);
}

void Datum::PointerFromString(std::string data, std::uint32_t index)
{
	UNREFERENCED_PARAMETER(index);
}

#pragma endregion

#pragma region TO_STRING

std::string Datum::ToString(std::uint32_t index)
{
	if (mType == Unknown)
		throw std::exception("Can't Convert Unknown Type To String");

	if (index >= mSize)
		throw std::exception("Index Out Of Range");

	return (this->*functions[mType])(index);

}

std::string Datum::IntToString(std::uint32_t index)
{
	return std::to_string(mValues.uInteger[index]);
}

std::string Datum::FloatToString(std::uint32_t index)
{
	return std::to_string(mValues.uFloat[index]);
}

std::string Datum::VectorToString(std::uint32_t index)
{
	return glm::to_string(mValues.uVector[index]);
}

std::string Datum::MatrixToString(std::uint32_t index)
{
	return glm::to_string(mValues.uMatrix[index]);
}

std::string Datum::TableToString(std::uint32_t index)
{
	UNREFERENCED_PARAMETER(index);
	return "Table";
}

std::string Datum::StringToString(std::uint32_t index)
{
	return mValues.uString[index];
}

std::string Datum::PointerToString(std::uint32_t index)
{
	return (mValues.uPointer[index])->ToString();
}

#pragma endregion

bool Datum::RemoveTable(const Scope* scope)
{
	if (mType == Table)
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (mValues.uTable[i] == scope)
			{
				memmove(mValues.uTable + i, mValues.uTable + i + 1, (mSize - i - 1) * sizeof(Scope*));
				--mSize;
				return true;
			}
		}
	}
	return false;
}