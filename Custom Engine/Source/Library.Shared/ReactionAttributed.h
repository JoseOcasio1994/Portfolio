#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);

	private:

		const std::string SubtypeKey = "Subtype";
		Datum* mSubtype;

	public:

		/* Default Constructor
		*/
		ReactionAttributed();

		/* Destructor
		*/
		virtual ~ReactionAttributed() = default;

		/* Add A Subtype As A String Value
		@param type a string value that is the name of the Subtype
		*/
		void AddSubtype(const std::string& type);

		/* Return An Array Of Strings That Is The List Of Subtypes
		@returns An Array Of Strings That Is The List Of Subtypes
		*/
		Datum* GetSubtypes() const;

		/* Upon Receiving An Event Of Type EventMessage ( A Generic Event ),
		* Copy Over The Attributes And Call Update
		*/
		void Notify(const EventPublisher& publisher);
	};

	ConcreteFactory(Action, ReactionAttributed);
}