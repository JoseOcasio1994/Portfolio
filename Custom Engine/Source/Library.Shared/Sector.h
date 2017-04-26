#pragma once
#include "pch.h"
#include <cstdint>
#include "Attributed.h"

namespace FieaGameEngine
{

	class World;

	class Sector final : public Attributed
	{

		RTTI_DECLARATIONS(Sector, Attributed);

	private:
		
		const std::string EntityKey = "Entities";
		const std::string ActionKey = "Actions";
		const std::string NameKey = "Name";
		const std::string WorldKey = "World";

		std::string mName;
		World* mWorld;
		Datum* mEntities, *mActions;

	public:
		
		/*default constructor
		*/
		Sector();

		/*constructor that can take in a name and world reference
		@param name the name to give this Sector
		@param world the world this Sector resides in
		@exception if name is empty
		*/
		explicit Sector(const std::string name, World* world = nullptr);

		/*destructor
		*/
		~Sector();

		/*Return the name of this Sector
		@returns the name of this Sector
		*/
		std::string& Name();

		/*Set the name of this Sector
		@param name the name to give this Sector
		@exception if name is empty
		*/
		void SetName(const std::string& name);

		/*Return the world this sector is in
		@returns the world this sector is in
		*/
		World* GetWorld() const;

		/*Set the world this Sector is in
		@param world the world this Sector will reside in
		*/
		void SetWorld(World& world);

		/*Returns the Entities inside this Sector
		@returns the Entities inside this Sector
		*/
		Datum* Entities();

		Datum* Actions();

		/*Create an Entity of type CLassName and give it name of instanceName
		@param ClassName std::string the name of the class
		@param instanceName std::string the name of this Entity
		*/
		Entity& CreateEntity(const std::string& className, const std::string& instanceName);

		Action& CreateAction(const std::string& className, const std::string& instanceName);

		/*Update this Entity with respect to a WorldState
		@param state a WorldState for this entity tp update with respect to
		*/
		void Update(WorldState& state);

	};
}