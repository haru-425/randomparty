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
		//////// �����ݒ� ////////


		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////

		++enemy_state;
		/*fallthrough*/

	case 2:
		//////// �ʏ펞 ////////

		// �s���̑J��
		enemy_act();


		break;
	}
}

void enemy_render() {

}

void enemy_act() {

}