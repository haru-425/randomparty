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
		stage[i]= bomb_def;
	}

}

void bomb_set()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		if (bomb_def.bomb_number == 0)
		{
			stage[i] = normal;
			stage[i].bomb_number = i + 1;
		}
	}
}

void bomb_update()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		if (bomb_def.bomb_number != 0)
		{

		}
	}

}

//�z��ɂ���āA�X�e�[�W�ɓ���e��u���Ă��ʁX�ɔ��������悤�ɂ���