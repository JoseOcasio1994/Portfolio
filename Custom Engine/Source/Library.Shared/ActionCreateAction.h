#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{

	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action);

	private:

		typedef std::pair<std::string, std::string> pairType;

		static const std::uint32_t mBufferSize = 10;
		const std::string CreatedKey = "CreatedActions";

		SList<pairType> mPendingCreate;

	public:

		ActionCreateAction();

		void Update(WorldState& state);

		void PendCreateAction(const std::string& prototype, const std::string& name);

	};
}