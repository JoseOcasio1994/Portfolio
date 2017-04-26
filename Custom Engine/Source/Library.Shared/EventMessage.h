#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class EventMessage final: public Scope
	{
		RTTI_DECLARATIONS(EventMessage, Scope);

	private:

		std::string mSubtype;
		World* mWorld;

	public:

		/* Default Constructor
		*/
		EventMessage();

		/* COnstructor that takes in a type and world
		@param type a string representing its subtype
		@param world the world the event resides in
		*/
		explicit EventMessage(std::string& type,  World* world = nullptr);

		/* Copy constructor
		*/
		EventMessage(const EventMessage& rhs);

		/* Copy Assignment Operator
		*/
		EventMessage& operator=(const EventMessage& rhs);

		/* Destructor
		*/
		~EventMessage() = default;

		/* Return A String Representing the subtype
		@returns A string representing the subtype
		*/
		std::string& Subtype();

		/* Takes a string and sets its subtype representation
		@param type string that represents its subtype
		*/
		void SetSubtype(const std::string& type);

		/* Return The world this event resides in
		@returns the world this event resides in
		*/
		World& GetWorld();

		/* Set the world for this event to reside in
		@param world the world for this event to reside in
		*/
		void SetWorld(const World& world);

	};
}