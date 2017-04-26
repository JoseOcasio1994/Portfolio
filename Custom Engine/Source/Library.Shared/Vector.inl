#include "Vector.h"

template <typename T>
Vector<T>::Vector(const int Capacity = 20) : 
	mSize(0), mCapacity(0), mBuffer(nullptr)
{
	Reserve(Capacity);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& Original) :
	mSize(0), mCapacity(0), mBuffer(nullptr)
{
	operator=(Original);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& Original) :
	mSize(Original.mSize), mCapacity(Original.mCapacity), mBuffer(Original.mBuffer)
{
	Original.mSize = 0;
	Original.mCapacity = 0;
	Original.mBuffer = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& Original)
{
	if (this != &Original)
	{
		Clear();
		
		Reserve(Original.mCapacity);
		mSize = Original.mSize;

		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			new (mBuffer + i)T(Original.mBuffer[i]);
		}
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& Original)
{
	if (this != &Original)
	{
		Clear();
		mSize = Original.mSize;
		mCapacity = Original.mCapacity;
		mBuffer = Original.mBuffer;

		Original.mSize = 0;
		Original.mCapacity = 0;
		Original.mBuffer = nullptr;
	}

	return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& Original)
{
	if (mSize != Original.mSize)
		return false;

	for (std::uint32_t i = 0; i < mSize; ++i)
		if (mBuffer[i] != Original.mBuffer[i])
			return false;

	return true;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& Original) const
{
	if (mSize != Original.mSize)
		return false;

	for (std::uint32_t i = 0; i < mSize; ++i)
		if (mBuffer[i] != Original.mBuffer[i])
			return false;

	return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& Original)
{
	return !operator==(rhs);
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& Original) const
{
	return !operator==(rhs);
}

template <typename T>
T& Vector<T>::operator[](const std::uint32_t Index)
{
	if(Index >= mSize)
		throw std::exception("Out Of Range");

	return mBuffer[Index];
}

template <typename T>
T& Vector<T>::operator[](const std::uint32_t Index) const
{
	if (Index >= mSize)
		throw std::exception("Out Of Range");

	return mBuffer[Index];
}

template <typename T>
Vector<T>::~Vector()
{
	Clear();
}

template <typename T>
T&	Vector<T>::At(const std::uint32_t Index)
{
	if (Index >= mSize)
		throw std::exception("Out Of Range");

	return mBuffer[Index];
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::PushBack(const T &Data)
{
	if (mSize >= mCapacity)
	{
		Reserve(mSize * 2);
	}

	new (mBuffer+mSize)T(Data);

	return Iterator(mSize++, *this);
}

template <typename T>
void Vector<T>::PopBack()
{
	if(mSize > 0)
		mBuffer[--mSize].~T();
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return mSize == 0;
}

template <typename T>
T& Vector<T>::Front()
{
	if (isEmpty())
		throw std::exception("Empty List");

	return mBuffer[0];
}

template <typename T>
const T& Vector<T>::Front() const
{
	if (isEmpty())
		throw std::exception("Empty List");

	return mBuffer[0];
}

template <typename T>
T& Vector<T>::Back()
{
	if (isEmpty())
		throw std::exception("Empty List");

	return mBuffer[mSize-1];
}

template <typename T>
const T& Vector<T>::Back() const
{
	if (isEmpty())
		throw std::exception("Empty List");

	return  mBuffer[mSize - 1];
}

template<typename T>
std::uint32_t Vector<T>::Size() const
{
	return mSize;
}

template<typename T>
std::uint32_t Vector<T>::Capacity() const
{
	return mCapacity;
}

template <typename T>
void Vector<T>::Clear()
{
	while(mSize > 0)
		PopBack();

	free(mBuffer);

	mCapacity = 0;
	mBuffer = nullptr;
}

template <typename T>
void Vector<T>::Reserve(std::uint32_t Amount)
{
	if (Amount > mCapacity)
	{
		T *Temp = (T*)malloc(Amount * sizeof(T));

		if (mBuffer != nullptr)
		{
			memcpy(Temp, mBuffer, mSize * sizeof(T));
			free(mBuffer);
		}

		mCapacity = Amount;
		mBuffer = Temp;
	}

}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const
{
	return Iterator(0, *this);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() const
{
	return Iterator(mSize, *this);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Find(const T& Value) const
{
	Vector<T>::Iterator It = begin();

	for (; It != end(); ++It)
	{
		if (*It == Value)
			break;
	}

	return It;
}

template <typename T>
typename void Vector<T>::Remove(const T& Value)
{
	Vector<T>::Iterator Found = Find(Value);

	if (Found == end())
		return;

	for (std::uint32_t i = Found.mIndex; i < mSize ; ++i)
	{
		mBuffer[i] = mBuffer[i + 1];
	}

	PopBack();
}

template <typename T>
typename void Vector<T>::Remove(const Iterator& start, const Iterator& last)
{
	if(start.mOwner != this || last.mOwner != this)
		throw std::exception("Invalid Iterator(s).");

	if(start.mIndex >= Size() || last.mIndex >= Size() )
		throw std::exception("Iterator(s) Out Of Range.");

	std::uint32_t iStart, iEnd, i;

	if (start.mIndex > last.mIndex)
	{
		iStart = last.mIndex;
		iEnd = start.mIndex;
	}
	else
	{
		iStart = start.mIndex;
		iEnd = last.mIndex;
	}

	for (i = iEnd-iStart + 1; iStart <= iEnd || iStart < mSize; ++iStart)
	{
		if (iStart + i < mSize)
		{
			mBuffer[iStart] = mBuffer[iStart + i]; // Replace Element With Existing Elements Past Last If Any
		}
		else
		{
			mBuffer[iStart].~T(); // Call Destructor On Element (No More Elements To Replace With)
		}
	}

	// Move Rest Of The Elements Forward
	for (; iStart <= mSize || iStart + i < mSize; ++iStart)
	{
		mBuffer[iStart] = mBuffer[iStart + i];
	}

	mSize -= i;
}
