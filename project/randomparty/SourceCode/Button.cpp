#include"all.h"
using namespace input;

int button_state;
Button button;

void Button::button_init() {
	button_state = 0;

	button = { 100, 100, 50 };

}

void Button::button_deinit() {

}

void Button::button_update() {
	switch (button_state)
	{
	case 0:
		//////// 初期設定 ////////


		++button_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////



		button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };
		button.scale = { 1.0f, 1.0f };
		button.texPos = { 0, 0 };
		button.texSize = { button.x, button.y };
		button.pivot = { button.x / 2, button.y / 2 };
		button.color = { 1.000f, 1.0f, 1.0f, 1.0f };


		++button_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		Button::button_act();

		break;
	}
}






void Button::button_render() {
	// 円形のボタンの描画
	primitive::circle(button.position.x, button.position.y, button.radius, 1, 1, ToRadian(0), 0, 0, 0);


}

void Button::button_act() {
	



	// ボタンの内部で左クリックが押された場合
	if (TRG(0) & L_CLICK) {
		if (click()) {
			// ゲーム画面に遷移
			nextScene = SCENE_GAME;
			return;
		}

	}

}


bool Button::click() {
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);

	// 円の中心座標
	float centerX = button.position.x;
	float centerY = button.position.y;

	// 円の半径
	float radius = button.texSize.x / 2;  // texSize.x はボタンの直径として使用

	// マウスの座標と円の中心との距離を計算
	float distance = sqrt(pow(point.x - centerX, 2) + pow(point.y - centerY, 2));

	// 距離が半径以下であればクリックが有効
	if (distance <= radius) {
		return true;
	}
	return false;
}


