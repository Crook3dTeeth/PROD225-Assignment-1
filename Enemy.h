#pragma once
#include "Character.h"

#define DEBUG_OUTPUT

class Material;
class Room;

class Enemy : public Character
{
public:
	Enemy();
	virtual ~Enemy();

	// Draws enemy to the screen
	virtual void Draw(olc::Sprite* Tileset, MonsterWorld* World) const override;

	virtual void Update(float fElapsedTime, TVector2D<float>* TPlayerLocation);

	virtual void Move(float fElapsedTime, TVector2D<float>* TTargetVec, TVector2D<uint8_t>* TRoomDimensions);

	virtual void Attack(int8_t iDamage, TVector2D<float> TDamageDirection, float KnockBack);

protected:

	Material* EMaterial;
};