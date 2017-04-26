#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	class WorldState final
	{
		
	private:

		GameTime* mGameTime;

	public:

		class World*  mWorld;
		class Sector* mSector;
		class Entity* mEntity;
		class Action* mAction;

		/*Default Constructor. Can Take In A Gametime parameter
		@param gameTime a GameTime pointer to refer to
		*/
 		explicit WorldState(GameTime* gameTime = nullptr);

		/*Return current GameTIme object
		@returns a gametime object
		*/
		GameTime* GetGameTime();

		/*Set current gameTIme object
		@param time a const GameTIme reference to refer to
		*/
		void SetGameTime(const GameTime& time);

	};
}