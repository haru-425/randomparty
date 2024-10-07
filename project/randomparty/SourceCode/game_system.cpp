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
