#pragma once

enum class SceneType
{
	None,
	DevScene,
	EditScene,
	GameScene,
	LobbyScene,
	StatUpgradeScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_UNDERSKILL,
	LAYER_PLAYER,
	LAYER_MONSTER,
	LAYER_SKILL,
	LAYER_DAMAGETEXT,
	LAYER_LOOT,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum class ColliderType
{
	Box,
	Sphere,
};

enum COMPONENT_TYPE
{
	CAMERA,
	COLLIDER,
	SKILL,

	COMPONENT_TYPE_COUNT
};


enum COLLISION_LAYER_TYPE : uint8
{
	CLT_PLAYER,
	CLT_PLAYER_SKILL,
	CLT_MONSTER,
	CLT_MONSTER_SKILL,
	CLT_MONSTER_ATK_RANGE,
	CLT_EXP,
	CLT_GROUND,
	CLT_WALL,
	// ...
	CLT_MAX_COUNT
};

enum Dir : uint8
{
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,

	DIR_COUNT
};

enum class MonsterID
{
	ID_Slime = 0,
	ID_Goblin,
	ID_Orc,
	ID_Cyclops,
	ID_WolfRider,
	ID_Owlbear,
	ID_Ogre,
	//ID_Dragon,
	ID_Count,

	ID_None = 999
};

enum SkillID
{
	ID_Slash = 0,
	ID_Iceburst,
	ID_Lightning,
	ID_Suriken,
	ID_ForceField,
	ID_Count,

	ID_None = 999
};