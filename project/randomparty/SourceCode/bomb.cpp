#include "all.h"

BombInfo bomb_def;
BombInfo stage[BOMB_MAX];

void bomb_init() 
{
	bomb_def.bomb_number = 0;
	bomb_def.bomb_playerattack = false;
	bomb_def.bomb_range = 0;
	bomb_def.bomb_time = 0;
	bomb_def.bomb_type = 0;

	for (int i = 0; i < BOMB_MAX; i++)
	{
		stage[BOMB_MAX]= bomb_def;
	}

}


//配列によって、ステージに二個爆弾を置いても別々に爆発するるようにする