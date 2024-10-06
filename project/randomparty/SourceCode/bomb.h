#pragma once
#ifndef BOMB_H 
#define BOMB_H

#include "all.h"

// 関数のプロトタイプ宣言 
void bomb_init(VECTOR2 player_position);
void bomb_deinit();
void bomb_update();
void bomb_render();

struct BombInfo
{
	int   bomb_number;
	int	  bomb_type;
	float bomb_scope;
	int   bomb_time;
	bool  bomb_playerattack;
};

#endif//BOMB_H