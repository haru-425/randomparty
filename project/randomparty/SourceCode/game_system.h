#pragma once
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include "all.h"

void system_init();
void system_deinit();
void system_update();
void system_render();

// �֐��̃v���g�^�C�v�錾
float tracking(VECTOR2 target, VECTOR2 tracking_person);


#endif//GAME_SYSTEM_H