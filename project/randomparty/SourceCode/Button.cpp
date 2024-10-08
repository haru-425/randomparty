#include"all.h"



int button_state;
Button button;



void button_init() {
	button_state = 0;
	button = { 100, 100, 50, false };
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
		button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.5f };
		button.scale = { 1.0f, 1.0f };
		button.texPos = { 0, 0 };
		button.texSize = { button.x, button.y };
		button.pivot = { button.x/2, button.y/2 };
		button.color = { 1.000f, 1.0f, 1.0f, 1.0f };

		++button_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移


		break;
	}
}


void button_render() {

	primitive::circle(SCREEN_W * 0.5f, SCREEN_H * 0.7f, button.radius, 1, 1, ToRadian(0), 0, 0, 0);
	
}