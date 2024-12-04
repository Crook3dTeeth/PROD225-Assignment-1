#include "MonsterWorld.h"
#include <iostream>
#include "Room.h"
#include "Macros.h"
#include "Player.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Boss.h"



MonsterWorld::MonsterWorld()
{
	
}



MonsterWorld::~MonsterWorld()
{
	// Delete Rooms
	delete FirstRoom;

	delete Tileset;

	delete PlayerPtr;
	
}


/// <summary>
/// Creates all the enemy objects 
/// </summary>
/// <returns>True if successful</returns>
bool MonsterWorld::OnUserCreate()
{
	// Set the seed at the start of the program for rng
	srand(time(NULL));


	// Load the tileset image
	Tileset = new olc::Sprite("tileset.png");

	// Generate the first room
	FirstRoom = new Room(0, 0);

	// Create a player
	PlayerPtr = new Player();

	TVector2D<uint8_t> TRoomSize = FirstRoom->GetRoomDimension();

	TVector2D<uint32_t> tStartingPos = TVector2D<uint32_t>(((TRoomSize.X + 2) /2) * SPRITE_X_SIZE, (TRoomSize.Y + 2) * SPRITE_Y_SIZE);

	PlayerPtr->SetPosition(tStartingPos);

	return true;
}


TVector2D<uint8_t> MonsterWorld::GetRoomDimension() const
{
	return FirstRoom->GetRoomDimension();
}


bool MonsterWorld::IsInDoor(TVector2D<uint32_t> InVector) const
{
	return FirstRoom->IsInDoor(InVector);
}


void MonsterWorld::EnterDoor(TVector2D<uint32_t> InVector)
{
	// Get the coords of the door in the new room
	TVector2D<uint32_t> NewPosition = FirstRoom->GetClosestDoorCoords(InVector);

	Room* OldRoom = FirstRoom;

	// Get the new room and set it as the current room
	FirstRoom = FirstRoom->GetClosestDoor(InVector);

	// Delete the old level if going to new level
	if (OldRoom->GetLevel() != FirstRoom->GetLevel()) {
		delete OldRoom;
	}

	// Move the player to the door
	PlayerPtr->SetPosition(NewPosition);
}


bool MonsterWorld::HasWon() const
{
	return FirstRoom->HasWon();
}


bool MonsterWorld::IsLocked(TVector2D<uint32_t> InVector) const
{
	return FirstRoom->IsLockedDoor(InVector);
}


void MonsterWorld::UnlockDoor(TVector2D<uint32_t> InVector)
{
	FirstRoom->UnlockDoor(InVector);
}

/// <summary>
/// Draws all the enemies on the world
/// </summary>
/// <param name="fElapsedTime"></param>
/// <returns>True when complete</returns>
bool MonsterWorld::OnUserUpdate(float fElapsedTime)
{
	// Clears the screen
	const olc::Pixel ClearPixel;
	Clear(ClearPixel);

	// Update the player
	PlayerPtr->Update(fElapsedTime, this, Tileset);

	// Get the player location
	TVector2D<float> PlayerLocation = PlayerPtr->GetLocation();

	// Update the enemies
	FirstRoom->UpdateEnemies(fElapsedTime, &PlayerLocation);

	// Draw the room
	FirstRoom->Draw(this, Tileset);

	
	PlayerPtr->Draw(Tileset, this);
	PlayerPtr->Move(fElapsedTime, this);

	return true;
}

bool MonsterWorld::BossAlive() const
{
	return FirstRoom->BossAlive();
}


bool MonsterWorld::IsInEnemy(TVector2D<uint32_t> InVector, float Range) const
{
	return FirstRoom->IsInEnemy(InVector, Range);
}


void MonsterWorld::AttackEnemy(TVector2D<float> InVector, int8_t iDamage, float KnockBack, float Range)
{
	FirstRoom->AttackEnemy(InVector, iDamage, KnockBack, Range);
}