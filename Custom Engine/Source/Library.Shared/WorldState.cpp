#include "pch.h"

using namespace FieaGameEngine;

WorldState::WorldState(GameTime* gameTime) :
	mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mGameTime()
{
	if (gameTime != nullptr)
		SetGameTime(*gameTime);
}

GameTime* WorldState::GetGameTime()
{
	return mGameTime;
}

void WorldState::SetGameTime(const GameTime& time)
{
	mGameTime = &const_cast<GameTime&>(time);
}