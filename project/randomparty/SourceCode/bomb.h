#pragma once
#ifndef BOMB_H 
#define BOMB_H

#include "all.h"

// 関数のプロトタイプ宣言 
void bomb_init();
void bomb_deinit();
void bomb_set();
void bomb_update();
void bomb_render();

struct BombInfo
{
	int   bomb_number;
	int	  bomb_type;
	float bomb_range;
	int   bomb_time;
	bool  bomb_playerattack;
};

extern PLAYER player;

#define BOMB_MAX 10


BombInfo normal = {0,1,3.0,5,true};

#endif//BOMB_H