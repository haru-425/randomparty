#include"all.h"

int button_state;

void button_init() {
	button_state = 0;
}

void button_deinit() {

}

void button_update() {
	switch (button_state)
	{
	case 0:
		//////// �����ݒ� ////////


		++button_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////


		++button_state;
		/*fallthrough*/

	case 2:
		//////// �ʏ펞 ////////

		// �s���̑J��


		break;
	}
}


void button_render() {

}