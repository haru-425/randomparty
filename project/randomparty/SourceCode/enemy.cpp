#include"all.h"

int enemy_state;

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

}