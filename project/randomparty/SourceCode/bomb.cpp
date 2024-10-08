#include "all.h"

BombInfo bomb_def;
BombInfo stage[BOMB_MAX];


BombInfo normal = { 0,1,3.0,5,true };


extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];
void bomb_init()
{
	bomb_def.bomb_number = 0;
	bomb_def.bomb_playerattack = false;
	bomb_def.bomb_range = 0;
	bomb_def.bomb_time = -1;
	bomb_def.bomb_type = 0;
	bomb_def.bomb_position.x = -200;
	bomb_def.bomb_position.y = -200;

	for (int i = 0; i < BOMB_MAX; i++)
	{
		stage[i] = bomb_def;
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
			bomb_def.bomb_position = player.position;
		}
	}
}

void bomb_update()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		if (bomb_def.bomb_number != 0)
		{
			stage[i].bomb_time -= 1;
			if (stage[i].bomb_time == 0)
			{
				bomb_explosion(i);

			}
		}
	}

}

void bomb_explosion(int bomb_namber)
{
	int waitTime=1;
	float enemy_r = ENEMY_CORE_TEX_W * enemy[0].scale.x/2;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (circle_hit(stage[bomb_namber].bomb_position, enemy->position, stage[bomb_namber].bomb_range, enemy_r))
		{
			enemy[i].reset();
			enemy[i].waitNum = waitTime;
			waitTime++;
		}
	}
}

//配列によって、ステージに二個爆弾を置いても別々に爆発するるようにする