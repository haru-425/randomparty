#pragma once
#include <math.h>
#include "all.h"

#define ENEMY_KILL_POINT 50

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
	void near_score();
	void enemy_kill_point();
	int score_get()
	{
		return total_score;
	}
	int kill_score_get()
	{
		return enemy_kill;
	}
	int distance_score_get()
	{
		return near_total;
	}
	void score_reset()
	{
		total_score=0;
		enemy_kill=0;
		near_total=0;
	}
};
