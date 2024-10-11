#include "all.h"
int     system_state;

void system_init()
{
	system_state = 0;
}

void system_deinit()
{

}
void system_update()
{
	switch (system_state)
	{
	case 0:
		//////// 初期設定 ////////

		++system_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////

		++system_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		break;
	}
}

void system_render()
{

}


float tracking(VECTOR2 target, VECTOR2 tracking_person) {
	VECTOR2 subVector;
	float angle;
	subVector.x = target.x - tracking_person.x;
	subVector.y = target.y - tracking_person.y;

	angle = (float)atan2(subVector.y, subVector.x);
	return angle;
}

bool circle_hit(VECTOR2 pos1, VECTOR2 pos2, float r1, float r2)
{
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	float r = r1 + r2;
	if (dx * dx + dy * dy <= r * r)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void game_end()
{
	nextScene = SCENE_TITLE;
}