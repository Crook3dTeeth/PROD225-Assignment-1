#include "Material.h"
#include "TVector2D.h"
#include "MonsterWorld.h"
#include "Macros.h"


Material::Material(enum class MaterialType InMaterial)
{
	MType = InMaterial;
	EType = EnemyMaterial::None;
	TSpritePos = GetSpriteCoords();
}

Material::Material(enum class EnemyMaterial InMaterial)
{
	EType = InMaterial;
	MType = MaterialType::None;
	TSpritePos = GetSpriteCoords();
}

Material::~Material()
{

}

void Material::SetMaterial(enum class MaterialType InMaterial)
{
	MType = InMaterial;
	EType = EnemyMaterial::None;
	TSpritePos = GetSpriteCoords();
}


void Material::SetMaterial(enum class EnemyMaterial InMaterial)
{
	EType = InMaterial;
	MType = MaterialType::None;
	TSpritePos = GetSpriteCoords();
}



void Material::DrawMaterial(TVector2D<int32_t> TInScreenPos, olc::Sprite* Tileset, MonsterWorld* World) const
{
	World->DrawPartialSprite(olc::vi2d(TInScreenPos.X, TInScreenPos.Y), Tileset, olc::vi2d(TSpritePos.X, TSpritePos.Y), olc::vi2d(SPRITE_X_SIZE, SPRITE_Y_SIZE));
}

TVector2D<int> Material::GetSpriteCoords()
{
	if (MType != MaterialType::None) {
		switch (MType)
		{
		case MaterialType::BRICK:
			return TVector2D<int>(14, 27);
		case MaterialType::WOOD:
			return TVector2D<int>(222, 40);
		case MaterialType::WALL:
			return TVector2D<int>(118, 40);
		case MaterialType::DOOR:
			return TVector2D<int>(53, 14);
		case MaterialType::OPEN_DOOR:
			return TVector2D<int>(14, 14);
		default:
			break;
		}
	}
	else {

		switch (EType)
		{
		case EnemyMaterial::ZOMBIE:
			return TVector2D<int>(326, 40);
		case EnemyMaterial::BOSS:
			return TVector2D<int>(326, 26);
		case EnemyMaterial::DEAD_ZOMBIE:
			return TVector2D<int>(339, 144);
		case EnemyMaterial::DEAD_BOSS:
			return TVector2D<int>(326, 144);
		default:
			break;
		}
	}
}