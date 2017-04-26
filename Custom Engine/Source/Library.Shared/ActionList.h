#pragma once
#include <cstdint>

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);

	private:

		const std::string ActionKey = "Actions";

		Datum* mActions;

	public:

		ActionList();
		ActionList(const std::string& name);

		virtual void Update(WorldState& state);

		Datum* Actions();

		Action& CreateAction(const std::string& className, const std::string& instanceName);
	};
}