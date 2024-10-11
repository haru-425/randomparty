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
	SCORE() :total_score(0), enemy_kill(0), near_total(0) {}
	~SCORE() {}

	void near_score()
	{
		float distance[2] = {0,0}, dx, dy;
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			dx = player.position.x - enemy->position.x;
			dy = player.position.y - enemy->position.y;
			distance[1] = sqrt(dx * dx + dy * dy);
			if (distance[1]< distance[0])
			{
				distance[0] = distance[1];
			}
		}
		debug::setString("%a", distance[0]);
	}
};
