#include <stdio.h>
#include "Player.h"
#include "olcPixelGameEngine.h"
#include "MonsterWorld.h"
#include "TextRenderer.h"
#include "Macros.h"


Player::Player()
{
	// Set the starting position
	TLocation->X = 1;
	TLocation->Y = 1;

	// Set the sprite
	TCurrentSprite.X = 1;
	TCurrentSprite.Y = 118;

	// Set  the speed
	fSpeed = 30.0f;

	// Set attack values and health
	fAttackSpeed = 1.0f;
	fTimeSinceAttack = 0.0f;

	fAttackRange = SPRITE_X_SIZE * 2;

	iDamage = 5;
	iHealth = 10;
}


Player::~Player()
{
	delete TLocation;
	delete THitBot;
}


/// <summary>
/// Draws the player
/// </summary>
/// <param name="Tileset"></param>
/// <param name="World"></param>
void Player::Draw(olc::Sprite* Tileset, MonsterWorld* World) const
{
	// Create the position, size and colour vectors for the zombie
	olc::vi2d Position = { int(TLocation->X), int(TLocation->Y)};

	olc::vi2d Size = {SPRITE_X_SIZE, SPRITE_Y_SIZE};

	olc::vi2d TSpritePos = { TCurrentSprite.X, TCurrentSprite.Y};

	olc::Sprite::Flip Direction = olc::Sprite::NONE;
	if (LastDirection == olc::Key::LEFT) {
		Direction = olc::Sprite::HORIZ;
	}


	// Draw the zombie in the world
	World->DrawPartialSprite(Position, Tileset, TSpritePos, Size, 1U, Direction);
}

void Player::Update(float fElapsedTime, MonsterWorld* World, olc::Sprite* Tileset)
{
	TextRenderer Text;

	// Notification location
	TVector2D<uint32_t> TNotificationLocation = TVector2D<uint32_t>(0, ((World->GetRoomDimension().Y + 2) * (SPRITE_Y_SIZE)));

	// Center of the player coords
	TVector2D<uint32_t> TPlayerCenter = TVector2D<uint32_t>(static_cast<uint32_t>(TLocation->X), static_cast<uint32_t>(TLocation->Y)) + TVector2D<uint32_t>(static_cast<uint32_t>(SPRITE_X_SIZE / 2), static_cast<uint32_t>(SPRITE_Y_SIZE / 2));

	// Update attack timer
	fTimeSinceAttack += fElapsedTime;

	// Check if in range of enemy
	if (World->IsInEnemy(TPlayerCenter, fAttackRange))
	{
		Text.RenderText("Space to attack", TNotificationLocation, World, Tileset);
		// Attack enemy
		if (World->GetKey(olc::Key::SPACE).bPressed)
		{
			if (fTimeSinceAttack >= fAttackSpeed) {
				// Attack
				World->AttackEnemy(*TLocation, iDamage, static_cast<float>(SPRITE_X_SIZE), fAttackRange);

				// Reset timer
				fTimeSinceAttack = 0;

			}
		}

	}
	//Check if won
	else if (World->HasWon()) {
		Text.RenderText("You Won", TNotificationLocation, World, Tileset);
	}
	// Doors check
	else if (World->IsInDoor(TVector2D<uint32_t>(static_cast<uint32_t>(TLocation->X), static_cast<uint32_t>(TLocation->Y))+ TVector2D<uint32_t>(static_cast<uint32_t>(SPRITE_X_SIZE / 2), static_cast<uint32_t>(SPRITE_Y_SIZE / 2)))) 
	{
		// Check if door is locked
		if (World->IsLocked(TPlayerCenter)) {
			// Print notification
			if (!World->BossAlive()) {
				Text.RenderText("E to unlock Door", TNotificationLocation, World, Tileset);
				if (World->GetKey(olc::Key::E).bPressed) {
					// Unlock door
					World->UnlockDoor(TPlayerCenter);
				}
			}
			else {
				Text.RenderText("Kill boss first", TNotificationLocation, World, Tileset);
			}

		}
		else { // Door is unlocked
			Text.RenderText("E to enter Room", TNotificationLocation, World, Tileset);

			if (World->GetKey(olc::Key::E).bPressed) {

				World->EnterDoor(TPlayerCenter);
			}
		}
	}
}


/// <summary>
/// Moves the player around the screen based on the speed of the player
/// </summary>
/// <param name="fElapsedTime">Time since last frame</param>
/// <param name="World">World object for accessing the olc funcs</param>
void Player::Move(float fElapsedTime, MonsterWorld* World)
{
	if (World->GetKey(olc::Key::LEFT).bHeld) 
	{
		LastDirection = olc::Key::LEFT;
		TLocation->X -= ((fElapsedTime / 1.0f) * fSpeed);
	}
	if (World->GetKey(olc::Key::RIGHT).bHeld) 
	{ 
		TLocation->X += ((fElapsedTime / 1.0f) * fSpeed);
		LastDirection = olc::Key::RIGHT;
	}
	
	
	if (World->GetKey(olc::Key::UP).bHeld) TLocation->Y -= (fElapsedTime / 1.0f) * fSpeed;
	if (World->GetKey(olc::Key::DOWN).bHeld) TLocation->Y += (fElapsedTime / 1.0f) * fSpeed;


	// Check room hitbox
	TVector2D<uint8_t> TRoomDimension = World->GetRoomDimension();
	// Check wall collision
	if (TLocation->X < SPRITE_X_SIZE) {
		TLocation->X = SPRITE_X_SIZE;
	}
	if (TLocation->Y < SPRITE_Y_SIZE) {
		TLocation->Y = SPRITE_Y_SIZE;
	}
	if (TLocation->X > ((TRoomDimension.X + 1) * SPRITE_X_SIZE - SPRITE_X_SIZE)) {
		TLocation->X = ((TRoomDimension.X + 1) * SPRITE_X_SIZE - SPRITE_X_SIZE);
	}
	if (TLocation->Y > ((TRoomDimension.Y + 1) * SPRITE_Y_SIZE - SPRITE_Y_SIZE)) {
		TLocation->Y = ((TRoomDimension.Y + 1) * SPRITE_Y_SIZE - SPRITE_Y_SIZE);
	}
}


/// <summary>
/// Get the location of the player
/// </summary>
/// <returns></returns>
TVector2D<float> Player::GetLocation() const
{
	return *TLocation;
}


/// <summary>
/// Set the position of the player
/// </summary>
/// <param name="TInVector"></param>
void Player::SetPosition(TVector2D<uint32_t> TInVector)
{
	TLocation->X = static_cast<float>(TInVector.X);
	TLocation->Y = static_cast<float>(TInVector.Y);
}