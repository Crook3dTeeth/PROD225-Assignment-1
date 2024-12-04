#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(TVector2D<float>* TSpawnLocation);
	~Boss() override;

	// Draws the boss on the screen
	virtual void Draw(olc::Sprite* Tileset, MonsterWorld* World) const override;

private:
	float fTimeSinceMove = 0;

	const float MAX_BOSS_SPEED = 10.0f;
	const float MIN_BOSS_SPEED = 15.0f;

};

