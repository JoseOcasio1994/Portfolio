#pragma once
#include <cstdint>
#include "pch.h"

namespace FieaGameEngine
{
	class FooMacro : public Foo<int>
	{
	};

	ConcreteFactory(Foo<int>, FooMacro);
}