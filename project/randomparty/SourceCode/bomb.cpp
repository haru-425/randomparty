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


//�z��ɂ���āA�X�e�[�W�ɓ���e��u���Ă��ʁX�ɔ��������悤�ɂ���