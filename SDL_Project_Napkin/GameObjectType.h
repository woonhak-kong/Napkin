#pragma once
#ifndef __GAME_OBJECT_TYPE__

enum class GameObjectType
{
	NONE = -1,
	PLAYER,
	PLAYER_ATTACK,
	ENEMY,
	ENEMY_ATTACK,
	START_BUTTON,
	EXIT_BUTTON,
	MENU_BUTTON,
	DOOR,
	SWORD,
	FOOD,
	NUM_OF_TYPES
};
#endif // !__GAME_OBJECT_TYPE__
