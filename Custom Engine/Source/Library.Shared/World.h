#pragma once
#include "pch.h"
#include <cstdint>
#include "Attributed.h"

namespace FieaGameEngine
{
	class EventQueue;

	class World final : public Attributed
	{

		RTTI_DECLARATIONS(World, Attributed);

	private:

		const std::string NameKey = "Name";
		const std::string ActionKey = "Actions";
		const std::string SectorKey = "Sectors";

		std::string mName;
		Datum* mSectors, *mActions;
		WorldState mState;
		GameTime mGameTime;
		EventQueue* mQueue;

	public:

		/*default constructor
		*/
		World();

		/*constructor that takes in a name to give this World
		@param name the name to give this world
		@exception if name is empty
		*/
		World(const std::string name);

		/*destructor
		*/
		~World();

		/*Return this World's Name
		@returns this World's Name
		*/
		std::string& Name();

		/*Set this world's name
		@param name the name to give this world
		@exception if name is empty
		*/
		void SetName(const std::string& name);

		/*Return the sectors this World contains
		@returns the sectors this World contains
		*/
		Datum* Sectors();

		Datum* Actions();

		/*Create a sector with a given name
		@param instanceName name to give the new Sector
		*/
		Sector& CreateSector(const std::string& instanceName);

		Action& CreateAction(const std::string& className, const std::string& instanceName);

		/*Update this Entity with respect to a WorldState
		@param state a WorldState for this entity tp update with respect to
		*/
		void Update();

		WorldState& GetWorldState();

		EventQueue* GetEventQueue();
	};
}