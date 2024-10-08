#include"all.h"

int button_state;

void button_init() {
	button_state = 0;
<<<<<<< Updated upstream
=======
	button = { 100, 100, 50 };
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream

=======
		button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };
		button.scale = { 1.0f, 1.0f };
		button.texPos = { 0, 0 };
		button.texSize = { button.x, button.y };
		button.pivot = { button.x/2, button.y/2 };
		button.color = { 1.000f, 1.0f, 1.0f, 1.0f };
>>>>>>> Stashed changes

		++button_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		button_act();

		break;
	}
}



<<<<<<< Updated upstream
}
=======

void button_render() {
	// 円形のボタンの描画
	primitive::circle(button.position.x, button.position.y, button.radius, 1, 1, ToRadian(0), 0, 0, 0);

	
}

void button_act() {
	using namespace input;

	
	
		// ボタンの内部で左クリックが押された場合
		if (TRG(0) & L_Click) {
			if (click()) {
				// ゲーム画面に遷移
				nextScene = SCENE_GAME;
				return;
			}
			
		}
	
}


bool click() {
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);
	float button_right = button.position.x + button.texSize.x / 2;
	float button_left = button.position.x - button.texSize.x / 2;
	float button_top = button.position.y - button.texSize.y / 2;
	float button_buttom = button.position.y + button.texSize.y / 2;
	if (point.x <= button_right && button_left <= point.x)
	{
		
		if (point.y <= button_buttom && button_top <= point.y)
		{
			
			return true;
		}
	}
	return false;
}
>>>>>>> Stashed changes
