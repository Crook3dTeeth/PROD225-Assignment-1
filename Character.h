#pragma once
#include "Actor.h"
#include "olcPixelGameEngine.h"

class MonsterWorld;

class Character : public Actor
{
public:
	virtual void Draw(olc::Sprite* Tileset, MonsterWorld* World) const {};

	virtual void Update(float fElapsedTime, MonsterWorld* World, olc::Sprite* Tileset) {};

	virtual bool IsAlive() const {
		return bIsAlive;
	}

	virtual TVector2D<float> GetLocation() const {
		return *TLocation;
	};

protected:
	// Speed of the character
	float fSpeed = 0.0f;

	// The current sprite of the actor if it (with defualt sprite)
	TVector2D<uint8_t> TCurrentSprite = TVector2D<uint8_t>(391, 456);

	// Is the character alive
	bool bIsAlive = true;

	// Attack and health values
	float fAttackSpeed;
	float fTimeSinceAttack;
	float fAttackRange;
	int8_t iDamage;
	int8_t iHealth;
};

