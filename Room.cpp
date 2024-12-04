#include <random>
#include "Room.h"
#include "Door.h"
#include "Material.h"
#include "MonsterWorld.h"
#include "Macros.h"
#include "TArray.h"
#include "Boss.h"
#include "Zombie.h"

Room::Room(int8_t iRoomOffset, int8_t iLevel, Room* PreviousRoom)
{
	// zero Rooms and doors
	LeftSideRoom = nullptr;
	RightSideRoom = nullptr;
	LeftDoor = nullptr;
	RightDoor = nullptr;
	CenterDoor = nullptr;


	// Set the level
	uCurrentLevel = iLevel;

	// Initialise zombie storage
	TZombies = new TArray<Zombie*>();

	// Set room offset
	this->RoomOffset = iRoomOffset;

	// Generate size of the room
	uint8_t RoomWidth = MIN_ROOM_X + rand() % (MAX_ROOM_X + 1 - MIN_ROOM_X);
	uint8_t RoomHeight = MIN_ROOM_Y + rand() % (MAX_ROOM_Y + 1 - MIN_ROOM_Y);
	TRoomSize += TVector2D<uint8_t>(RoomWidth, RoomHeight);

	// Generate the material sprites for the room and store them
	TRoomMaterials = new TArray<Material*>();
	Material* CurrentMaterial;
	

	// Room dimension for drawing 2d from a 1d array
	uint8_t CurrentHeight = 0;
	uint8_t CurrentWidth = 0;

	// Draw the room floor and walls
	for (int MaterialIndex = 0; MaterialIndex < ((TRoomSize.X + 2) * (TRoomSize.Y + 2)); MaterialIndex++)
	{
		// Check if its wall or floor
		if (CurrentWidth == 0 || CurrentHeight == 0 || CurrentWidth == TRoomSize.X + 1 || CurrentHeight == TRoomSize.Y + 1) {
			CurrentMaterial = new Material(Material::MaterialType::WALL);
			TRoomMaterials->AddElement(CurrentMaterial);
		}
		else {
			CurrentMaterial = new Material(Material::MaterialType::BRICK);
			TRoomMaterials->AddElement(CurrentMaterial);
		}
		// Increment height
		CurrentWidth++;
		if (CurrentWidth >= TRoomSize.X + 2) {
			CurrentWidth = 0;
			CurrentHeight++;
		}
	}

	
	// Check and generate side rooms
	if (abs(iRoomOffset) < MAX_SIDE_ROOMS) {
		// Randomly Generate any side rooms
		uint8_t LeftSideRoomChance = rand() % 101;
		uint8_t RightSideRoomChance = rand() % 101;

		// Current room is center so left and right can have doors
		if (iRoomOffset == 0) {
			// Generate left rooms
			if (LeftSideRoomChance > (100 - SIDE_ROOM_CHANCE)) {
				LeftSideRoom = new Room(iRoomOffset - 1, uCurrentLevel, this);
				LeftDoor = new Door(TVector2D<uint32_t>(0, (TRoomSize.Y * SPRITE_Y_SIZE) / 2));
			}
			// Generate right rooms
			if (RightSideRoomChance > (100 - SIDE_ROOM_CHANCE)) {
				RightSideRoom = new Room(iRoomOffset + 1, uCurrentLevel, this);
				RightDoor = new Door(TVector2D<uint32_t>(((TRoomSize.X + 1) * SPRITE_X_SIZE), (TRoomSize.Y * SPRITE_Y_SIZE) / 2));
			}
			// Generate the next level
			if (uCurrentLevel < MAX_LEVEL) {
				CenterDoor = new Door(TVector2D<uint32_t>((((TRoomSize.X + 1) * SPRITE_X_SIZE) / 2), 0));
			}

		}
		else if (iRoomOffset < 0) // Only generate new left rooms
		{
			if (LeftSideRoomChance > (100 - SIDE_ROOM_CHANCE)) {
				LeftSideRoom = new Room(iRoomOffset - 1, uCurrentLevel, this);
				LeftDoor = new Door(TVector2D<uint32_t>(0, (TRoomSize.Y * SPRITE_Y_SIZE) / 2));
			}

			// Set the door and room to get back
			RightSideRoom = PreviousRoom;
			RightDoor = new Door(TVector2D<uint32_t>(((TRoomSize.X + 1) * SPRITE_X_SIZE), (TRoomSize.Y * SPRITE_Y_SIZE) / 2), true);
		}
		else { // Only generate new right room
			if (RightSideRoomChance > (100 - SIDE_ROOM_CHANCE)) {
				RightSideRoom = new Room(iRoomOffset + 1, uCurrentLevel, this);
				RightDoor = new Door(TVector2D<uint32_t>(((TRoomSize.X + 1) * SPRITE_X_SIZE), (TRoomSize.Y * SPRITE_Y_SIZE) / 2));
			}

			// Set the door and room to get back
			LeftSideRoom = PreviousRoom;
			LeftDoor = new Door(TVector2D<uint32_t>(0, (TRoomSize.Y * SPRITE_Y_SIZE) / 2), true);
		}
	}
	else {
		if (iRoomOffset < 0) {
			RightSideRoom = PreviousRoom;
			RightDoor = new Door(TVector2D<uint32_t>(((TRoomSize.X + 1) * SPRITE_X_SIZE), (TRoomSize.Y * SPRITE_Y_SIZE) / 2), true);
		}
		else if (iRoomOffset > 0) {
			LeftSideRoom = PreviousRoom;
			LeftDoor = new Door(TVector2D<uint32_t>(0, (TRoomSize.Y * SPRITE_Y_SIZE) / 2), true);
		}
	}

	// Get the center of the room
	TVector2D<float>* TRoomCenter = new TVector2D<float>(((TRoomSize.X / 2) * SPRITE_X_SIZE) + SPRITE_X_SIZE, ((TRoomSize.Y / 2) * SPRITE_Y_SIZE) + SPRITE_Y_SIZE);

	// Generate enemies and or bosses
	if (iRoomOffset == 0) // Center room has boss
	{
		Bosses = new Boss(TRoomCenter);
	}
	else {
		// No bosses with zombies
		Bosses = nullptr;

		// Space the zombies in the world
		float fZombieSpaceing = SPRITE_Y_SIZE * 1.5;

		// Generate zombies
		uint8_t NumZombies = MIN_ZOMBIES + rand() % (MAX_ZOMBIES + 1 - MIN_ZOMBIES);
		Zombie* NewZombie;

		for (uint8_t ZombieIndex = MIN_ZOMBIES; ZombieIndex <= NumZombies; ZombieIndex++) {
			TVector2D<float>* TStartingPos = new TVector2D<float>(0.0f, 0.0f);

			// Even number of zombies
			if ((ZombieIndex- MIN_ZOMBIES) % 2 == 0) {
				TStartingPos->Y = TRoomCenter->Y - (((NumZombies) * fZombieSpaceing) - ((ZombieIndex- MIN_ZOMBIES) * fZombieSpaceing));
			}
			else { // Odd number of zombies
				TStartingPos->Y = TRoomCenter->Y - (((NumZombies / 2) * fZombieSpaceing) - ((ZombieIndex - MIN_ZOMBIES) * fZombieSpaceing));
			}

			// Generate the zombie and store it
			NewZombie = new Zombie(TStartingPos);
			TZombies->AddElement(NewZombie);
		}
	}
}


Room::~Room()
{	
	
	if (TZombies != nullptr)
		if(RoomOffset == 0)
			delete TZombies;
	

	if (Bosses != nullptr)
		delete Bosses;

	if (TRoomMaterials != nullptr) {
		if (RoomOffset == 0)
		delete TRoomMaterials;
	}


	if (CenterDoor != nullptr) 
		delete CenterDoor;
	
	if (RoomOffset >= 0) {
		if (RightSideRoom != nullptr)
			delete RightSideRoom;
	}
	
	if (RightDoor != nullptr) 
		delete RightDoor;

	if (RoomOffset <= 0) {
		if (LeftSideRoom != nullptr)
			delete LeftSideRoom;
	}

	if(LeftDoor != nullptr)
		delete LeftDoor;
	

}


/// <summary>
/// Returns the room dimension
/// </summary>
/// <returns></returns>
TVector2D<uint8_t> Room::GetRoomDimension() const
{
	return TRoomSize;
}


/// <summary>
/// Draws the room
/// </summary>
/// <param name="World"></param>
/// <param name="Tileset"></param>
void Room::Draw(MonsterWorld* World, olc::Sprite* Tileset) const
{
	// Current sprite material
	Material* CurrentMaterial;
	// Room dimension for drawing 2d from a 1d array
	uint8_t CurrentHeight = 0;
	uint8_t CurrentWidth = 0;

	// Draw the room floor and walls
	for (int MaterialIndex = 0; MaterialIndex < TRoomMaterials->Num(); MaterialIndex++)
	{
		// Draw the sprite
		CurrentMaterial = TRoomMaterials->GetElement(MaterialIndex);
		CurrentMaterial->DrawMaterial(TVector2D<int32_t>(((CurrentWidth) * SPRITE_X_SIZE), ((CurrentHeight) * SPRITE_Y_SIZE)), Tileset, World);
		
		// Check if its a new row
		CurrentWidth++;
		if (CurrentWidth >= TRoomSize.X + 2) {
			CurrentWidth = 0;
			CurrentHeight++;
		}
	}

	// Draw any doors
	if (RoomOffset == 0) { // Center door
		if (CenterDoor != nullptr) {
			TVector2D<int32_t> TInScreenPos = TVector2D<int32_t>((TRoomSize.X * SPRITE_X_SIZE) / 2, 0);
			CenterDoor->DrawDoor(Tileset, TInScreenPos, World);
		}

		if (LeftDoor != nullptr && LeftSideRoom) {
			TVector2D<int32_t> TInScreenPos = TVector2D<int32_t>(0, (TRoomSize.Y * SPRITE_Y_SIZE) / 2);
			LeftDoor->DrawDoor(Tileset, TInScreenPos, World);
		}

		if (RightDoor != nullptr && RightSideRoom) {
			TVector2D<int32_t> TInScreenPos = TVector2D<int32_t>(((TRoomSize.X + 1)* SPRITE_X_SIZE), (TRoomSize.Y * SPRITE_Y_SIZE) / 2);
			RightDoor->DrawDoor(Tileset, TInScreenPos, World);
		}
	}


	// Draw the open door that player came through
	else if (RoomOffset > 0) { // draw Left door
		if (LeftDoor != nullptr && LeftSideRoom) {
			TVector2D<int32_t> TInScreenPos = TVector2D<int32_t>(0, (TRoomSize.Y * SPRITE_Y_SIZE) / 2);
			LeftDoor->DrawDoor(Tileset, TInScreenPos, World);
		}
	}
	else { // draw Right door
		if (RightDoor != nullptr && RightSideRoom) {
			TVector2D<int32_t> TInScreenPos = TVector2D<int32_t>(((TRoomSize.X + 1)* SPRITE_X_SIZE), (TRoomSize.Y * SPRITE_Y_SIZE) / 2);
			RightDoor->DrawDoor(Tileset, TInScreenPos, World);
		}
	}

	// Draw enemies
	if (Bosses != nullptr) {
		Bosses->Draw(Tileset, World);
	}
	for (int ZombieIndex = 0; ZombieIndex < TZombies->Num(); ZombieIndex++) {
		TZombies->GetElement(ZombieIndex)->Draw(Tileset, World);
	}

}


/// <summary>
/// Unlocks the door the coords are in
/// </summary>
/// <param name="Coords"></param>
void Room::UnlockDoor(TVector2D<uint32_t> TCoords)
{
	if (LeftDoor != nullptr) {
		if (LeftDoor->InRange(TCoords)) {
			LeftDoor->UnlockDoor();
			return;
		}
	}
	if (RightDoor != nullptr) {
		if (RightDoor->InRange(TCoords)) {
			RightDoor->UnlockDoor();
			return;
		}
	}
	if (CenterDoor != nullptr) {
		if (CenterDoor->InRange(TCoords)) {
			CenterDoor->UnlockDoor();
			return;
		}
	}
}

/// <summary>
/// Checks if the given coords are in the door hit box
/// </summary>
/// <param name="Coords">Player coords</param>
/// <returns></returns>
bool Room::IsInDoor(TVector2D<uint32_t> TCoords) const
{
	if (LeftDoor != nullptr) {
		if (LeftDoor->InRange(TCoords)) {
			return true;
		}
	}
	if (RightDoor != nullptr) {
		if (RightDoor->InRange(TCoords)) {
			return true;
		}
	}
	if (CenterDoor != nullptr) {
		if (CenterDoor->InRange(TCoords)) {
			return true;
		}
	}

	return false;
}


/// <summary>
/// Checks if the given coords are in the door hit box
/// </summary>
/// <param name="Coords">Player coords</param>
/// <returns></returns>
Room* Room::GetClosestDoor(TVector2D<uint32_t> TCoords)
{
	if (LeftDoor != nullptr) {
		if (LeftDoor->InRange(TCoords)) {
			return LeftSideRoom;
		}
	}
	if (RightDoor != nullptr) {
		if (RightDoor->InRange(TCoords)) {
			return RightSideRoom;
		}
	}
	if (CenterDoor != nullptr) {
		if (CenterDoor->InRange(TCoords)) {
			return new Room(0, uCurrentLevel + 1);
		}
	}

	return nullptr;
}


/// <summary>
/// Checks if the boss is currently alive
/// </summary>
/// <returns></returns>
bool Room::BossAlive() const{
	return Bosses->IsAlive();
}


/// <summary>
/// Checks if the coords are within the range of an enemy
/// </summary>
/// <param name="InVector"></param>
/// <param name="Range">Distance enemy can be</param>
/// <returns></returns>
bool Room::IsInEnemy(TVector2D<uint32_t> TInVector, float fRange) const
{
	// Check boss
	if (Bosses != nullptr) {
		// Center of the player coords
		TVector2D<float> TBossLocation = Bosses->GetLocation();
		TVector2D<uint32_t> TBossCenter = TVector2D<uint32_t>(static_cast<uint32_t>(TBossLocation.X + (SPRITE_X_SIZE/2)), static_cast<uint32_t>(TBossLocation.Y + (SPRITE_Y_SIZE / 2)));

		// Get distance to boss
		float DistanceToBoss = TBossCenter.Distance(TInVector);
		// Chcek if boss is within range
		if (DistanceToBoss <= fRange && Bosses->IsAlive()) {
			return true;
		}
	}

	// Check zombies
	for (uint8_t ZombieIndex = 0; ZombieIndex < TZombies->Num(); ZombieIndex++) {
		TVector2D<float> TZombieLocation = TZombies->GetElement(ZombieIndex)->GetLocation();
		if (TZombies->GetElement(ZombieIndex)->IsAlive()) {
			TVector2D<uint32_t> TZombieCenter = TVector2D<uint32_t>(static_cast<uint32_t>(TZombieLocation.X + (SPRITE_X_SIZE / 2)), static_cast<uint32_t>(TZombieLocation.Y + (SPRITE_Y_SIZE / 2)));

			if (TZombieCenter.Distance(TInVector) <= fRange) {
				return true;
			}
		}
	}

	return false;
}

// Attack enemy if in range
void Room::AttackEnemy(TVector2D<float> TInVector, int8_t iDamage, float fKnockBack, float fRange)
{
	// Check boss
	if (Bosses != nullptr) {
		// Center of the player coords
		TVector2D<float> TBossLocation = Bosses->GetLocation();
		TVector2D<float> TBossCenter = TVector2D<float>(SPRITE_X_SIZE/2,SPRITE_Y_SIZE/2);
		TBossCenter += TBossLocation;

		float DistanceToBoss = TBossCenter.Distance(TInVector);
		if (DistanceToBoss <= fRange) {
			TVector2D<float> fDirection = TBossLocation;
			fDirection -= TInVector;
			fDirection.Normalize();

			Bosses->Attack(iDamage, fDirection, fKnockBack);
		}
	}

	// Check zombies
	for (uint8_t ZombieIndex = 0; ZombieIndex < TZombies->Num(); ZombieIndex++) {
		TVector2D<float> TZombieLocation = TZombies->GetElement(ZombieIndex)->GetLocation();
		TVector2D<float> TZombieCenter = TVector2D<float>(SPRITE_X_SIZE / 2, SPRITE_Y_SIZE / 2);

		TZombieCenter += TZombieLocation;
		if (TZombieCenter.Distance(TInVector) <= fRange) {
			TVector2D<float> fDirection = TZombieCenter;
			fDirection -= TInVector;
			fDirection.Normalize();

			TZombies->GetElement(ZombieIndex)->Attack(iDamage, fDirection, fKnockBack);
		}
	}
}


/// <summary>
/// Gets the coordinates of the closest door that the player is in the
/// hitbox of
/// </summary>
/// <param name="Coords">Player coordinates</param>
/// <returns></returns>
TVector2D<uint32_t> Room::GetClosestDoorCoords(TVector2D<uint32_t> TCoords) const
{

	if (LeftDoor != nullptr) {
		if (LeftDoor->InRange(TCoords)) {
			return LeftSideRoom->RightDoor->GetLocation();
		}
	}
	if (RightDoor != nullptr) {
		if (RightDoor->InRange(TCoords)) {
			return RightSideRoom->LeftDoor->GetLocation();
		}
	}
	if (CenterDoor != nullptr) {
		if (CenterDoor->InRange(TCoords)) {
			TVector2D<uint8_t> TNextRoomCoords = this->GetRoomDimension();
			return TVector2D<uint32_t>(((TNextRoomCoords.X + 2)/2) * SPRITE_X_SIZE,(TNextRoomCoords.Y + 1) * SPRITE_Y_SIZE);
		}
	}

	return TVector2D<uint32_t>(0, 0);
}

/// <summary>
/// Check if the door is currently locked
/// </summary>
/// <param name="Coords"></param>
/// <returns></returns>
bool Room::IsLockedDoor(TVector2D<uint32_t> TCoords) const
{
	if (LeftDoor != nullptr) {
		if (LeftDoor->InRange(TCoords)) {
			return !LeftDoor->IsUnlocked();
		}
	}
	if (RightDoor != nullptr) {
		if (RightDoor->InRange(TCoords)) {
			return !RightDoor->IsUnlocked();
		}
	}
	if (CenterDoor != nullptr) {
		if (CenterDoor->InRange(TCoords)) {
			return !CenterDoor->IsUnlocked();
		}
	}

	return false;
}


/// <summary>
/// Checks if the player has won and there is no where else to go
/// </summary>
/// <returns></returns>
bool Room::HasWon() const
{
	if (uCurrentLevel >= MAX_LEVEL && !Bosses->IsAlive()) {
		return true;
	}

	return false;
}


/// <summary>
/// Updates and moves all the enemies in the room
/// </summary>
/// <param name="fElapsedTime"></param>
/// <param name="PlayerLocation"></param>
void Room::UpdateEnemies(float fElapsedTime, TVector2D<float>* TPlayerLocation)
{
	// Update and move the boss
	if (Bosses != nullptr) {
		Bosses->Update(fElapsedTime, TPlayerLocation);
		Bosses->Move(fElapsedTime, TPlayerLocation, &TRoomSize);
	}

	// Update and move any zombies
	for (int EnemyIndex = 0; EnemyIndex < TZombies->Num(); EnemyIndex++) {
		Zombie* CurrentZombie = TZombies->GetElement(EnemyIndex);
		CurrentZombie->Update(fElapsedTime, TPlayerLocation);
		CurrentZombie->Move(fElapsedTime, TPlayerLocation, &TRoomSize);
	}
}