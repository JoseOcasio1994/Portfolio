//#include "Foo.h"

template <typename T>
RTTI_DEFINITIONS(Foo<T>);

template <typename T>
Foo<T>::Foo() :
	mData(nullptr)
{

}

template <typename T>
Foo<T>::Foo(const T& Data) :
	mData(new T(Data))
{

}

template <typename T>
Foo<T>::Foo(const Foo& rhs) :
	mData(nullptr)
{
	operator=(rhs);
}

template <typename T>
Foo<T>::~Foo()
{
	delete mData;
}

template <typename T>
Foo<T>& Foo<T>::operator=(const Foo& rhs)
{
	if (this != &rhs)
	{
		if (mData != nullptr && rhs.mData != nullptr)
			*mData = *rhs.mData;
		else if (mData == nullptr && rhs.mData != nullptr)
			mData = new T(*rhs.mData);
		else
			mData = rhs.mData;
	}

	return *this;
}

template <typename T>
bool Foo<T>::operator==(const Foo<T>& rhs) const
{
	return (*mData == *rhs.mData);
}

template <typename T>
bool Foo<T>::operator!=(const Foo<T>& rhs) const
{
	return !(operator==(rhs));
}

template <typename T>
std::uint32_t Foo<T>::operator()( Foo key)
{
	T copy = *key.mData;
	std::uint8_t * data = reinterpret_cast<std::uint8_t*>(&copy);
	std::uint32_t hash = 0;

	for (int i = 0; i < sizeof(T); ++i)
		hash += (Constant * data[i]);

	return hash;
}

template <typename T>
T& Foo<T>::operator*()
{
	return *mData;
}
