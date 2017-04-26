#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class ActionEvent final: public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);

	private:
		typedef std::chrono::milliseconds milliseconds;

		const std::string DelayKey = "Delay";
		const std::string SubtypeKey = "Subtype";

		Datum* mSubtype, *mDelay;

	public:

		/* Default constructor
		*/
		ActionEvent();

		/* Constructor that takes in a type and delay amount
		@param type a string representation of its subtype
		@param delay amount of time in milliseconds to delay delivery of created events
		*/
		ActionEvent(std::string& type, int delay);

		/* Destructor
		*/
		~ActionEvent() = default;

		/* Set the subtype of events for this action to create
		@param type a string representation of subtype
		*/
		void SetSubType(const std::string& type);

		/* Return a string representation of subtype
		@returns a string representation of subtype
		*/
		std::string GetSubType();

		/* Set the delay that created events will be delayed by before delivery
		@param delay an int value for time in milliseconds to delay delivery of created events
		*/
		void SetDelay(std::int32_t delay);

		/* Return delay amount
		@returns the delay amount
		*/
		std::int32_t GetDelay();

		/* Create an Event<EventMessage> object, set its Subtype and World, copy over
		*  any auxiliary attributes, and Enqueue that event.
		@param state used to get gameTime for Enqueueing events
		*/
		void Update(WorldState& state);
	};

	ConcreteFactory(Action, ActionEvent);
}