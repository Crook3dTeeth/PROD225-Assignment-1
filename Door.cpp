#include "Door.h"
#include "MonsterWorld.h"
#include "Material.h"
#include "TVector2D.h"
#include "Player.h"
#include "Macros.h"


Door::Door(TVector2D<uint32_t> TInLocation, bool InitialState)
{
	// Checks if the door starts locked or unlocked
	BIsUnlocked = InitialState;
	if (BIsUnlocked) {  
		DoorMaterial = new Material(Material::MaterialType::OPEN_DOOR);
	}
	else {
		DoorMaterial = new Material(Material::MaterialType::DOOR);
	}


	// Sets the door location 
	*TLocation = TInLocation;
	*TLocation += TVector2D<uint32_t>(static_cast<uint32_t>(SPRITE_X_SIZE/2), static_cast<uint32_t>(SPRITE_Y_SIZE / 2));

	// Set the radius of the Hitbox
	HitBoxSize = static_cast<float>(SPRITE_X_SIZE) * 1.2;
}


Door::~Door()
{
	delete DoorMaterial;
	delete TLocation;
	delete THitBotOffset;
}


/// <summary>
/// Checks if the player is in the doors hitbox
/// </summary>
/// <param name="InVector"></param>
/// <returns></returns>
bool Door::InRange(TVector2D<uint32_t> TInVector) const
{
	// Get distance to door
	float Distance = TLocation->Distance(TInVector);
	
	// Check if TInVector is within the hitbox size
	if (Distance <= HitBoxSize) {
		return true;
	}

	return false;
}


/// <summary>
/// Unlocks the door and sets the open texture
/// </summary>
void Door::UnlockDoor()
{
	BIsUnlocked = true;
	DoorMaterial->SetMaterial(Material::MaterialType::OPEN_DOOR);
}


/// <summary>
/// Draws the door material
/// </summary>
/// <param name="Tileset"></param>
/// <param name="InScreenPos"></param>
/// <param name="World"></param>
void Door::DrawDoor(olc::Sprite* Tileset, TVector2D<int32_t> InScreenPos, MonsterWorld* World) const
{
	DoorMaterial->DrawMaterial(InScreenPos, Tileset, World);
}


/// <summary>
/// Gets the location of the door
/// </summary>
/// <returns></returns>
TVector2D<uint32_t> Door::GetLocation() const
{
	return *TLocation;
}


/// <summary>
/// Checks if the door is unlocked
/// </summary>
/// <returns></returns>
bool Door::IsUnlocked() const
{
	return BIsUnlocked;
}