#pragma once
#include "pch.h"
#include "Attributed.h"
#include <cstdint>

namespace FieaGameEngine
{

	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);

	protected:

		const std::string NameKey = "Name";
		const std::string EmptyName = "";
		std::string mName = "";
		
		bool mPendingDelete;

	public:

		Action();

		virtual void Update(WorldState& state) = 0;

		std::string& Name();
		void SetName(const std::string& name);

		void MarkForDelete();
		bool isPendingDelete();

	};
}