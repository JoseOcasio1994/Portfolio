#pragma once
#include "pch.h"
#include "Attributed.h"
#include <cstdint>

namespace FieaGameEngine
{
	class Sector;

	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed);

	private:

		const std::string NameKey = "Name";
		const std::string ActionKey = "Actions";

		std::string mName;
		Datum* mActions;
		Sector* mSector;

	public:
		static const std::uint32_t mNumFactories = 20;

		/*Default constructor
		*/
		Entity();

		/*Constructor that can take in a name and sector
		@param name std::string the name of this Entity
		@param sector the sector this entity resides in
		@exception if name is empty
		*/
		explicit Entity(const std::string& name, Sector* sector = nullptr);

		/*Destructor
		*/
		virtual ~Entity();

		/*Return the name of this entity
		@returns std::string the name of this entity
		*/
		std::string& Name();

		/*Set the name of this entity
		@rparam name std::string the name to give this entity
		@exception if name is empty
		*/
		void SetName(const std::string& name);

		/*Return the sector this entity resides in
		@returns Sector* the sector this entity resides in
		*/
		Sector* GetSector() const;

		/*Set the sector for this entity to reside in
		@param sector the sector for this entity to reside in
		*/
		void SetSector(Sector& sector);

		Datum* Actions();

		Action& CreateAction(const std::string& className, const std::string& instanceName);

		virtual void Update(WorldState& state);

	};
}