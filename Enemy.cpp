#include "Enemy.h"
#include "MonsterWorld.h"
#include "Material.h"
#include "Macros.h"
#include "Boss.h"
#include "Room.h"
#include <iostream>
#include <random>
#include <ctime>


Enemy::Enemy()
{
	// Create random coordinates for the enemies
	TLocation->X = rand() % 201;
	TLocation->Y = rand() % 201;

	// Set material of the enemy
	EMaterial = new Material(Material::EnemyMaterial::ZOMBIE);

	// Set attack values and health
	fAttackSpeed = 0.0f;
	fTimeSinceAttack = 0.0f;
	iDamage = 0;
	iHealth = 0;
}


Enemy::~Enemy()
{
	delete EMaterial;
}


/// <summary>
/// Draw a generic red enemy to the world
/// </summary>
/// <param name="World"></param>
void Enemy::Draw(olc::Sprite* Tileset, MonsterWorld* World) const
{
	// Create the position, size and colour vectors for the enemy
	olc::vi2d Position = { static_cast<int32_t>(TLocation->X), static_cast<int32_t>(TLocation->Y) };
	olc::vi2d Size = {8, 8};
	olc::Pixel Colour = { 255, 0, 0, 255 };
	// Draw the enemy
	World->DrawRect(Position, Size, Colour);
}


/// <summary>
/// Updates the enemy and attacks the player if inside
/// </summary>
/// <param name="fElapsedTime"></param>
/// <param name="PlayerLocation"></param>
void Enemy::Update(float fElapsedTime, TVector2D<float>* TPlayerLocation)
{
	
}


/// <summary>
/// Take damage and knockback by the player
/// </summary>
/// <param name="iDamage"></param>
/// <param name="DamageDirection"></param>
/// <param name="KnockBack"></param>
void Enemy::Attack(int8_t iDamage, TVector2D<float> TDamageDirection, float KnockBack)
{
	// Check if enemy is alive
	if (bIsAlive) {
		iHealth -= iDamage;

		// Knock the enemy back
		TLocation->X += (TDamageDirection.X * KnockBack);
		TLocation->Y += (TDamageDirection.Y * KnockBack);

		// enemy just died
		if (iHealth <= 0) {
			// Set alive state
			bIsAlive = false;

			// Set dead material
			if (dynamic_cast<Boss*>(this)) { // check if boss or zombie
				EMaterial->SetMaterial(Material::EnemyMaterial::DEAD_BOSS);
			}
			else {
				EMaterial->SetMaterial(Material::EnemyMaterial::DEAD_ZOMBIE);
			}
		}
	}
}


/// <summary>
/// Moves the enemy towards the player
/// </summary>
/// <param name="fElapsedTime"></param>
/// <param name="TargetVec"></param>
/// <param name="RoomDimensions"></param>
void Enemy::Move(float fElapsedTime, TVector2D<float>* TTargetVec, TVector2D<uint8_t>* TRoomDimensions)
{
	if (bIsAlive) {
		TVector2D<float> TDirection = *TLocation;
		TDirection -= *TTargetVec;
		TDirection.Normalize();

		// Move in the direction of the player
		TLocation->X -= (TDirection.X * fSpeed * fElapsedTime);
		TLocation->Y -= (TDirection.Y * fSpeed * fElapsedTime);


		// Check if enemy is out of bounds
		if (TLocation->X < SPRITE_X_SIZE) {
			TLocation->X = SPRITE_X_SIZE;
		}
		if (TLocation->Y < SPRITE_Y_SIZE) {
			TLocation->Y = SPRITE_Y_SIZE;
		}

		if (TLocation->X > ((TRoomDimensions->X + 1) * SPRITE_X_SIZE - SPRITE_X_SIZE)) {
			TLocation->X = ((TRoomDimensions->X + 1) * SPRITE_X_SIZE - SPRITE_X_SIZE);
		}

		if (TLocation->Y > ((TRoomDimensions->Y + 1) * SPRITE_Y_SIZE - SPRITE_Y_SIZE)) {
			TLocation->Y = ((TRoomDimensions->Y + 1) * SPRITE_Y_SIZE - SPRITE_Y_SIZE);
		}
	}
}
