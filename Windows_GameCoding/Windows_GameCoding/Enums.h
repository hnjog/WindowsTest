#pragma once

enum class SceneType
{
	None,
	DevScene,
	EditScene,
};

enum class Dir
{
	Left,
	Right,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT,
};

enum class ColliderType
{
	Box,
	Sphere,
};

enum COLLISION_LAYER_TYPE
{
	CLT_OBJECT = 0,
	CLT_GROUND,
	CLT_WALL,

	CLT_MAXCOUNT,
};