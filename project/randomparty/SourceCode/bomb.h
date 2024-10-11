#pragma once
#ifndef BOMB_H 
#define BOMB_H

#include "all.h"

#define BOMB_RANGE_SCALE ( PLAYER_TEX_W * player.scale.x)

// 関数のプロトタイプ宣言 
void bomb_init();
void bomb_deinit();
void bomb_set();
void bomb_update();
void bomb_explosion(int bomb_namber);
void bomb_render();

class BombInfo
{
public:
	int   bomb_number;
	int	  bomb_type;
	float bomb_range;
	int   bomb_time;
	bool  bomb_playerattack;
	VECTOR2 bomb_position;
	int bomb_explode_count;
};


#define BOMB_MAX 10


#endif//BOMB_H