#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(TVector2D<float>* TSpawnLocation);
	~Zombie() override;

	// Draws the zombie to the screen
	virtual void Draw(olc::Sprite* Tileset, MonsterWorld* World) const override;

private:
	float fTimeSinceMove = 0;

	bool bIsAlive = true;

	const float MAX_ZOMBIE_SPEED = 8.0f;
	const float MIN_ZOMBIE_SPEED = 1.0f;
};

