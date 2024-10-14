#pragma once
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include "all.h"

void system_init();
void system_deinit();
void system_update();
void system_render();
void game_start();
void game_end();
void result_end();

// 関数のプロトタイプ宣言
float tracking(VECTOR2 target, VECTOR2 tracking_person);
bool circle_hit(VECTOR2 pos1, VECTOR2 pos2, float r1, float r2);

#endif//GAME_SYSTEM_H