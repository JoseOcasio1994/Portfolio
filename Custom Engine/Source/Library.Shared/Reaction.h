#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);

	};
}