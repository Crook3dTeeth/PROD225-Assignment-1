#include "Zombie.h"
#include "olcPixelGameEngine.h"
#include "MonsterWorld.h"
#include "Material.h"
#include "Macros.h"
#include <iostream>
#include <random>

Zombie::Zombie(TVector2D<float>* TSpawnLocation)
{
	// Set zombie sprite
	EMaterial = new Material(Material::EnemyMaterial::ZOMBIE);

	// Set spawn location
	TLocation = TSpawnLocation;

	// Set health and attack stats
	fAttackSpeed = 10.0f;
	fTimeSinceAttack = 0.0f;
	iDamage = 1.0f;
	iHealth = 1.0f;
	fAttackRange = SPRITE_X_SIZE;

	// Set random speed
	fSpeed = MIN_ZOMBIE_SPEED + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (MAX_ZOMBIE_SPEED - MIN_ZOMBIE_SPEED));
}


Zombie::~Zombie()
{
	delete EMaterial;
}


/// <summary>
/// Draws the zombie in the world
/// </summary>
/// <param name="World"></param>
void Zombie::Draw(olc::Sprite* Tileset, MonsterWorld* World) const
{
	// Cast the position from float to int32_t
	TVector2D<int32_t> TPosition = TVector2D<int32_t>(static_cast<int32_t>(TLocation->X), static_cast<int32_t>(TLocation->Y));

	// Draw the zombie
	EMaterial->DrawMaterial(TPosition, Tileset, World);
}
