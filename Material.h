#pragma once
#include "TVector2D.h"
#include "olcPixelGameEngine.h"



class MonsterWorld;

class Material
{
public:
	enum class MaterialType
	{
		BRICK,
		WOOD,
		WALL,
		DOOR,
		OPEN_DOOR,
		None
	};

	enum class EnemyMaterial
	{
		ZOMBIE,
		BOSS,
		DEAD_ZOMBIE,
		DEAD_BOSS,
		None
	};

	Material(enum class MaterialType InMaterial);
	Material(enum class EnemyMaterial InMaterial);
	~Material();

	void DrawMaterial(TVector2D<int32_t> TInScreenPos, olc::Sprite* Tileset, MonsterWorld* World) const;

	void SetMaterial(enum class MaterialType InMaterial);
	void SetMaterial(enum class EnemyMaterial InMaterial);

private:
	TVector2D<int> GetSpriteCoords();

	TVector2D<int> TSpritePos = TVector2D<int>(0, 0);


	enum class MaterialType MType;
	enum class EnemyMaterial EType;
};

