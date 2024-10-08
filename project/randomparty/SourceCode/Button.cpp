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
		//////// 初期設定 ////////


		++button_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////


		++button_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移


		break;
	}
}


void button_render() {

}