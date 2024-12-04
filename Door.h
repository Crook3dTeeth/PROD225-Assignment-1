#pragma once
#include "olcPixelGameEngine.h"
#include "TVector2D.h"


class Player;
class Material;
class MonsterWorld;


class Door
{
public:
	Door(TVector2D<uint32_t> TInLocation, bool InitialState = false);
	~Door();

	void UnlockDoor();

	bool IsUnlocked() const;

	bool InRange(TVector2D<uint32_t> InVector) const;
	
	void DrawDoor(olc::Sprite* Tileset, TVector2D<int32_t> TInScreenPos, MonsterWorld* World) const;

	TVector2D<uint32_t> GetLocation() const;

private:
	// State of the door (locked/unlocked)
	bool BIsUnlocked;

	// Material of the door
	Material* DoorMaterial;

	// Location of the center of the hitbox
	TVector2D<uint32_t>* TLocation = new TVector2D<uint32_t>(0,0);

	// Offset of the hitbox
	TVector2D<uint32_t>* THitBotOffset = new TVector2D<uint32_t>(0,0);

	float HitBoxSize;
};

