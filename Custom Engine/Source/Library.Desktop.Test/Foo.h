#pragma once

#include "pch.h"

namespace FieaGameEngine
{
	template <typename T>
	class Foo : public RTTI
	{

		RTTI_DECLARATIONS(Foo, RTTI);

	public:

		T *mData;
		static const std::uint32_t Constant = 113;

		Foo();
		Foo(const T& Data);
		Foo(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;
		std::uint32_t operator()( Foo key);
		T& operator*();
		~Foo();

	};
#include "Foo.inl"
}