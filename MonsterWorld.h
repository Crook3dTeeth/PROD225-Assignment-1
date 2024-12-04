#pragma once
#include "olcPixelGameEngine.h"
#include "TVector2D.h"


class Enemy;
class Player;
class Room;


#define MAX_ROOMS 5
#define MAX_SIDE_ROOM_WIDTH 3

class MonsterWorld : public olc::PixelGameEngine
{
public:
	static MonsterWorld* World;

	MonsterWorld();
	~MonsterWorld();

	// Creates all the game world  
	virtual bool OnUserCreate() override;
	// Draws all the enemies in the world
	virtual bool OnUserUpdate(float fElapsedTime) override;

	TVector2D<uint8_t> GetRoomDimension() const;

	// Checks if the coords are in a door
	bool IsInDoor(TVector2D<uint32_t> TInVector) const;

	// Check if in range of enemy
	bool IsInEnemy(TVector2D<uint32_t> TInVector, float fRange) const;

	// Attack enemy if in range
	void AttackEnemy(TVector2D<float> TInVector, int8_t iDamage, float fKnockBack, float fRange);

	// Checks if the door is locked
	bool IsLocked(TVector2D<uint32_t> TInVector) const;

	// Enters the door the player is near
	void EnterDoor(TVector2D<uint32_t> TInVector);

	// Unlocks the door
	void UnlockDoor(TVector2D<uint32_t> TInVector);

	// Checks if the boss is still alive
	bool BossAlive() const;

	// Check if the player has won
	bool HasWon() const;

	// Stores the tileset
	olc::Sprite* Tileset;

protected:
	// The player
	Player* PlayerPtr = nullptr;

	// The current room
	Room* FirstRoom = nullptr;
};

