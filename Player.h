#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	void Draw(olc::Sprite* Tileset, MonsterWorld* World) const override;

	void Update(float fElapsedTime, MonsterWorld* World, olc::Sprite* Tileset) override;

	void Move(float fElapsedTime, MonsterWorld* World);

	virtual TVector2D<float> GetLocation() const override;

	void SetPosition(TVector2D<uint32_t> TInVector);
protected:
	// XP for leveling (damage, health, abilities)
	int iXP = 0;

private:
	// Last direction so sprite can face the correct direction
	olc::Key LastDirection = olc::Key::LEFT;
};

