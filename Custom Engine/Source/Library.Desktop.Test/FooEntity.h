#pragma once
#include <cstdint>
#include "pch.h"

namespace FieaGameEngine
{
	class FooEntity : public Entity
	{
	};

	ConcreteFactory(Entity, FooEntity);
}