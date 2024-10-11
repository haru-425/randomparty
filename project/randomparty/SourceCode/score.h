#pragma once
#include <math.h>
#include "all.h"

extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];

class SCORE
{
private:
	int total_score;
	int enemy_kill;
	int near_total;

public:
	int time;
	SCORE() :total_score(0), enemy_kill(0), near_total(0) {}
	~SCORE() {}
	float distance[2] = { 1000000,0 }, dx, dy;
	void near_score()
	{
		time++;
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			dx = player.position.x - enemy[i].position.x;
			dy = player.position.y - enemy[i].position.y;
			distance[1] = sqrt(dx * dx + dy * dy);
			if (distance[1]< distance[0])
			{
				distance[0] = distance[1];
			}
		}
		if (300 - distance[0]>0&& time %60 == 0)
		{
			near_total += (300 - distance[0])/50;
		}
		debug::setString("%d", near_total);
		distance[0] = 1000000;
	}
};
