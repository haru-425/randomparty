#include "all.h"
using namespace input;

int button_state;
int end_button_state;
int help_button_state;
int set_button_state;
Button button;
Button EndButton;
Button HelpButton;
Button SetButton;
Button nextbutton;
Sprite* sprButton;
Sprite* sprEnd;
Sprite* sprHelp;
Sprite* sprSet;

extern int render_mode;
extern int select_c;

void Button::button_init()
{
	button_state = 0;
}

void Button::end_button_init()
{
	end_button_state = 0;
}

void Button::help_button_init()
{
	help_button_state = 0;
}

void Button::set_button_init()
{
	set_button_state = 0;
}

void Button::button_deinit()
{
	safe_delete(sprButton);
}

void Button::end_button_deinit()
{
	safe_delete(sprEnd);
}

void Button::help_button_deinit()
{
	safe_delete(sprHelp);
}

void Button::set_button_deinit()
{
	safe_delete(sprSet);
}

void Button::button_update()
{
	switch (button_state)
	{
	case 0:
		// 初期設定
		sprButton = sprite_load(L"./Data/Images/playButton.png");

		++button_state;
		/*fallthrough*/

	case 1:
		// パラメータの設定
		button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };  // 中心位置
		button.scale = { 1.0f, 1.0f };
		button.texPos = { 0, 0 };
		button.texSize = { BUTTON_TEX_W, BUTTON_TEX_H };
		button.pivot = { BUTTON_PIVOT_X, BUTTON_PIVOT_Y };
		button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		button.radius = BUTTON_TEX_W / 4;

		++button_state;
		/*fallthrough*/

	case 2:
		// 通常時の処理
		Button::button_act();

		break;
	}
}

void Button::end_button_update()
{
	switch (end_button_state)
	{
	case 0:
		// 初期設定
		sprEnd = sprite_load(L"./Data/Images/returnButton.png");

		++end_button_state;
		/*fallthrough*/

	case 1:
		// パラメータの設定
		EndButton.position = { 90, 60 };  // 中心位置
		EndButton.scale = { 1.0f, 1.0f };
		EndButton.texPos = { 0, 0 };
		EndButton.texSize = { END_TEX_W, END_TEX_H };
		EndButton.pivot = { END_PIVOT_X, END_PIVOT_Y };
		EndButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };


		++end_button_state;
		/*fallthrough*/

	case 2:
		// 通常時の処理
		Button::end_button_act();

		break;
	}
}

void Button::help_button_update()
{
	switch (help_button_state)
	{
	case 0:
		// 初期設定
		sprHelp = sprite_load(L"./Data/Images/helpButton.png");

		++help_button_state;
		/*fallthrough*/

	case 1:
		// パラメータの設定
		HelpButton.position = { SCREEN_W * 0.3f, SCREEN_H * 0.8f };  // 中心位置
		HelpButton.scale = { 1.0f, 1.0f };
		HelpButton.texPos = { 0, 0 };
		HelpButton.texSize = { HELP_TEX_W, HELP_TEX_H };
		HelpButton.pivot = { HELP_PIVOT_X, HELP_PIVOT_Y };
		HelpButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		HelpButton.radius = HELP_TEX_W / 6.7;


		++help_button_state;
		/*fallthrough*/

	case 2:
		// 通常時の処理
		Button::help_button_act();

		break;
	}
}

void Button::set_button_update()
{
	switch (set_button_state)
	{
	case 0:
		// 初期設定
		sprSet = sprite_load(L"./Data/Images/settingButton.png");

		++set_button_state;
		/*fallthrough*/

	case 1:
		// パラメータの設定
		SetButton.position = { SCREEN_W * 0.7f, SCREEN_H * 0.8f };  // 中心位置
		SetButton.scale = { 1.0f, 1.0f };
		SetButton.texPos = { 0, 0 };
		SetButton.texSize = { SET_TEX_W, SET_TEX_H };
		SetButton.pivot = { SET_PIVOT_X, SET_PIVOT_Y };
		SetButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		SetButton.radius = SET_TEX_W / 6.7;

		++set_button_state;
		/*fallthrough*/

	case 2:
		// 通常時の処理
		Button::set_button_act();

		break;
	}
}

void Button::button_render()
{

	sprite_render(sprButton, button.position.x, button.position.y, 0.5f, 0.5f, 0, 0, 440, 440, 440 / 2, 440 / 2);
}

void Button::end_button_render()
{
	sprite_render(sprEnd, EndButton.position.x, EndButton.position.y, 1.5f, 1.5f, 0, 0, 128, 64, 128 / 2, 64 / 2);
}

void Button::help_button_render()
{
	sprite_render(sprHelp, HelpButton.position.x, HelpButton.position.y, 0.3f, 0.3f, 0, 0, 440, 440, 440 / 2, 440 / 2);

}

void Button::set_button_render()
{
	sprite_render(sprSet, SetButton.position.x, SetButton.position.y, 0.3f, 0.3f, 0, 0, 440, 440, 440 / 2, 440 / 2);

}

void Button::button_act()
{
	// ボタン内部で左クリックが押された場合
	if (TRG(0) & L_CLICK) {
		if (click()) {
			// ゲーム画面に遷移

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			game_start();
			return;
		}
	}
}

void Button::end_button_act()
{
	if (curScene == SCENE_HELP)
	{
		if (TRG(0) & L_CLICK) {
			if (end_click()) {

				sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
				render_mode = 0;
				select_c = 0;
				return;
			}
	    }
	}
	// ボタン内部で左クリックが押された場合
	if (TRG(0) & L_CLICK) {
		if (end_click()) {

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			result_end();
			return;
		}
	}
}

void Button::help_button_act()
{
	// ボタン内部で左クリックが押された場合
	if (TRG(0) & L_CLICK) {
		if (help_click()) {

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			help_start();
			return;
		}
	}
}

void Button::set_button_act()
{
	// ボタン内部で左クリックが押された場合
	if (TRG(0) & L_CLICK) {
		if (set_click()) {

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			result_end();
			return;
		}
	}
}

bool Button::click() {
	// マウスカーソルの座標取得
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);

	// 円の中心座標
	float centerX = button.position.x;
	float centerY = button.position.y;

	// マウスカーソルと円の中心との距離を計算
	float distance = sqrt(pow(point.x - centerX, 2) + pow(point.y - centerY, 2));

	// 距離がボタンの半径以下であればクリックが有効
	return (distance <= button.radius);
}

bool Button::end_click() {
	// マウスカーソルの座標取得
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);

	// ボタンの四辺を取得
	float button_right = EndButton.position.x + EndButton.texSize.x / 1.3;
	float button_left = EndButton.position.x - EndButton.texSize.x / 1.3;
	float button_top = EndButton.position.y - EndButton.texSize.y / 1.3;
	float button_bottom = EndButton.position.y + EndButton.texSize.y / 1.3;

	// マウスの座標がボタンの範囲内かチェック
	bool isWithinX = (point.x >= button_left && point.x <= button_right);
	bool isWithinY = (point.y >= button_top && point.y <= button_bottom);

	// マウスがボタン範囲内ならクリックされたと判定
	return isWithinX && isWithinY;
}

bool Button::help_click()
{
	// マウスカーソルの座標取得
	POINT Helppoint;
	GetCursorPos(&Helppoint);
	ScreenToClient(window::getHwnd(), &Helppoint);

	// 円の中心座標
	float HelpcenterX = HelpButton.position.x;
	float HelpcenterY = HelpButton.position.y;

	// マウスカーソルと円の中心との距離を計算
	float Helpdistance = sqrt(pow(Helppoint.x - HelpcenterX, 2) + pow(Helppoint.y - HelpcenterY, 2));

	// 距離がボタンの半径以下であればクリックが有効
	return (Helpdistance <= HelpButton.radius);
}

bool Button::set_click()
{
	// マウスカーソルの座標取得
	POINT Setpoint;
	GetCursorPos(&Setpoint);
	ScreenToClient(window::getHwnd(), &Setpoint);

	// 円の中心座標
	float SetcenterX = SetButton.position.x;
	float SetcenterY = SetButton.position.y;

	// マウスカーソルと円の中心との距離を計算
	float Setdistance = sqrt(pow(Setpoint.x - SetcenterX, 2) + pow(Setpoint.y - SetcenterY, 2));

	// 距離がボタンの半径以下であればクリックが有効
	return (Setdistance <= SetButton.radius);
}

void next_button_init()
{
	nextbutton.position = { 90, 60 };  // 中心位置
	nextbutton.scale = { 1.0f, 1.0f };
	nextbutton.texPos = { 0, 0 };
	nextbutton.texSize = { 80, 320 };
	nextbutton.pivot = { 0, 0 };
	nextbutton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

bool Button::next_click() 
{
	// マウスカーソルの座標取得
	POINT nextpoint;
	GetCursorPos(&nextpoint);
	ScreenToClient(window::getHwnd(), &nextpoint);
	// ボタンの四辺を取得
	float button_right = EndButton.position.x + EndButton.texSize.x / 1.3;
	float button_left = EndButton.position.x - EndButton.texSize.x / 1.3;
	float button_top = EndButton.position.y - EndButton.texSize.y / 1.3;
	float button_bottom = EndButton.position.y + EndButton.texSize.y / 1.3;

	// マウスの座標がボタンの範囲内かチェック
	bool isWithinX = (nextpoint.x >= button_left && nextpoint.x <= button_right);
	bool isWithinY = (nextpoint.y >= button_top && nextpoint.y <= button_bottom);

	// マウスがボタン範囲内ならクリックされたと判定
	return isWithinX && isWithinY;

}

