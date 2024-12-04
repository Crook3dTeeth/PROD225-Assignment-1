#pragma once
#include "Material.h"

// Sizes of the walkable area inside (walls are added on)
#define MIN_ROOM_X 7
#define MIN_ROOM_Y 7
#define MAX_ROOM_X 12
#define MAX_ROOM_Y 12


class MonsterWorld;
class Door;
class Boss;
class Zombie;

template<typename T>
class TVector2D;
template<typename T>
class TArray;

class Room
{
public:
	Room(int8_t iRoomOffset, int8_t iLevel, Room* PreviousRoom = nullptr);
	~Room();

	virtual void Draw(MonsterWorld* World, olc::Sprite* Tileset) const;

	bool IsInDoor(TVector2D<uint32_t> TCoords) const;

	bool IsLockedDoor(TVector2D<uint32_t> TCoords) const;

	void UnlockDoor(TVector2D<uint32_t> TCoords);

	void UpdateEnemies(float fElapsedTime, TVector2D<float>* TPlayerLocation);

	TVector2D<uint8_t> GetRoomDimension() const;

	Room* GetClosestDoor(TVector2D<uint32_t> Coords);

	TVector2D<uint32_t> GetClosestDoorCoords(TVector2D<uint32_t> TCoords) const;

	bool IsInEnemy(TVector2D<uint32_t> TInVector, float fRange) const;

	bool BossAlive() const;

	bool HasWon() const;

	void GenerateNextLevel();

	uint8_t GetLevel() const {
		return uCurrentLevel;
	}

	// Attack enemy if in range
	void AttackEnemy(TVector2D<float> TInVector, int8_t iDamage, float fKnockBack, float fRange);

protected:

	TVector2D<uint8_t> TRoomSize = TVector2D<uint8_t>(0, 0);

private:
	// Zombies
	TArray<Zombie*>* TZombies;

	// Boss
	Boss* Bosses;

	// Room offset from centre, 0 means middle (boss) room, -/+ left right of main path
	int8_t RoomOffset;

	// Left room
	Room* LeftSideRoom;
	Door* LeftDoor;

	// Right room
	Room* RightSideRoom;
	Door* RightDoor;

	// Center door
	Door* CenterDoor;

	// Material sprites for drawing the room
	TArray<Material*>* TRoomMaterials;

	// Max zombies per room
	const int MAX_ZOMBIES = 2;
	const int MIN_ZOMBIES = 1;

	// Level of the world
	uint8_t uCurrentLevel = 0;
	const uint8_t MAX_LEVEL = 5;
};

