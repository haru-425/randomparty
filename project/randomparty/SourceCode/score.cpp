#include <math.h>
#include "all.h"
using namespace std;


void SCORE::near_score()
{
	time++;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		dx = player.position.x - enemy[i].position.x;
		dy = player.position.y - enemy[i].position.y;
		distance[1] = sqrt(dx * dx + dy * dy);
		if (distance[1] < distance[0])
		{
			distance[0] = distance[1];
		}
	}
	if (300 - distance[0] > 0 && time % 10 == 0)
	{
		near_total += (300 - distance[0]) / 50;
		total_score += (300 - distance[0]) / 50;
	}
	debug::setString("%d", total_score);
	distance[0] = 1000000;
}

void SCORE::enemy_kill_point()
{
	enemy_kill++;
	total_score += ENEMY_KILL_POINT;
}
