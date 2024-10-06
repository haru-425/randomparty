#include"all.h"

int enemy_state;
extern PLAYER player;
typedef enum
{
	APPROACH_SLOW,
	APPROACH_FAST,

}ENEMY_TYPE;
ENEMY enemy[ENEMY_MAX];
void enemy_init() {
	enemy_state = 0;
}

void enemy_deinit() {

}

void enemy_update() {

	switch (enemy_state)
	{
	case 0:
		//////// 初期設定 ////////


		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////

		++enemy_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		enemy_act();


		break;
	}
}

void enemy_render() {

}

void enemy_act() {
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		VECTOR2 subVector;
		subVector.x = player.position.x - enemy[i].position.x;
		subVector.y = player.position.y - enemy[i].position.y;

		enemy[i].angle = (float)atan2(subVector.y, subVector.x);
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (enemy[i].type)
		{
		case APPROACH_SLOW:
			break;
		case APPROACH_FAST:
			break;
		}
	}


}