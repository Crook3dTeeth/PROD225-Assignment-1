#include "Boss.h"
#include "olcPixelGameEngine.h"
#include "MonsterWorld.h"
#include "Material.h"
#include "Macros.h"
#include <iostream>
#include <random>

Boss::Boss(TVector2D<float>* TSpawnLocation)
{
	// Set a random speed
	fSpeed = MIN_BOSS_SPEED + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(MAX_BOSS_SPEED- MIN_BOSS_SPEED));

	// Set material and spawn location
	EMaterial = new Material(Material::EnemyMaterial::BOSS);
	TLocation = TSpawnLocation;
	TLocation->X -= SPRITE_X_SIZE / 2;
	TLocation->Y -= SPRITE_Y_SIZE / 2;

	// Set health and attack stats
	fAttackSpeed = 5.0f;
	fTimeSinceAttack = 0.0f;
	fAttackRange = SPRITE_X_SIZE;
	iDamage = 5;
	iHealth = 20;
}

Boss::~Boss()
{
	
}


/// <summary>
/// Draws the boss sprite
/// </summary>
/// <param name="World"></param>
void Boss::Draw(olc::Sprite* Tileset, MonsterWorld* World) const
{
	// Cast the position from float to int32_t
	TVector2D<int32_t> TPosition = TVector2D<int32_t>(static_cast<int32_t>(TLocation->X), static_cast<int32_t>(TLocation->Y));

	// Draw the boss
	EMaterial->DrawMaterial(TPosition, Tileset, World);
}
