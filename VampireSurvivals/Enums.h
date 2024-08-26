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

enum Sight
{
	Right,
	Left
};

enum class ColliderType
{
	Box,
	Sphere,
};


enum COLLISION_LAYER_TYPE : uint8
{
	CLT_PLAYER,
	CLT_SKILL,
	CLT_MONSTER,
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