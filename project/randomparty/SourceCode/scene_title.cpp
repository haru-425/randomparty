#include "all.h"
#include <sstream>

#define SELECT_COUNT 2              //選択肢の数

int title_state;
int title_timer;



Sprite* backspr;
Sprite* backspr2;
Sprite* titlespr;
Sprite* sprRogo;

VECTOR2 titlePos;
int title_move_timer;
float title_angle;


extern Button button;
extern Button HelpButton;
extern Button SetButton;

//--------------------------------------
//  初期設定
//--------------------------------------
void title_init()
{
	title_state = 0;
	title_timer = 0;

	button.button_init();
	HelpButton.help_button_init();
	SetButton.set_button_init();
}

//--------------------------------------
//  終了処理
//--------------------------------------
void title_deinit()
{
	music::stop(3);
	button.button_deinit();
	HelpButton.help_button_deinit();
	SetButton.set_button_deinit();
	safe_delete(backspr);
	safe_delete(backspr2);
	safe_delete(titlespr);
	safe_delete(sprRogo);


	music::stop(BGM_TITLE);
}

void title_update()
{
	using namespace input;
	button.button_update();
	HelpButton.help_button_update();
	SetButton.set_button_update();

	switch (title_state)
	{
	case 0:
		//////// 初期設定 ////////

		GameLib::setBlendMode(Blender::BS_ALPHA);
		backspr = sprite_load(L"./Data/Images/title_layer01.png");
		backspr2 = sprite_load(L"./Data/Images/title_layer02.png");
		titlespr = sprite_load(L"./Data/Images/Title.png");
		sprRogo = sprite_load(L"./Data/Images/rogo.png");

		title_move_timer = 0;
		title_state++;
		/*fallthrough*/
	case 1:
		//////// パラメータの設定 ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(BGM_TITLE, true);
		title_state++;
		/*fallthrough*/
	case 2:
		//////// 通常時 ////////

		title_act();
		break;
	}

	title_timer++;


	//#ifdef USE_IMGUI
	//	ImGui::Begin("ImGUI");
	//
	//	static float value = 0;
	//	ImGui::DragFloat("value", &value, 0.001f);
	//
	//	ImGui::End();
	//#endif



}
void title_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);

	sprite_render(backspr, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(backspr2, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(titlespr, titlePos.x, titlePos.y, 0.5f, 0.5f, 0, 0, 3000, 500, 3000 / 2, 500 / 2);
	sprite_render(sprRogo, SCREEN_W - 50, SCREEN_H - 50, 0.3f, 0.3f, 0, 0, 400, 400, 400 / 2, 400 / 2);
	button.button_render();
	HelpButton.help_button_render();
	SetButton.set_button_render();
}
void title_act() {
	/*
	VECTOR2 titlePos;
	int title_move_timer;
	float title_angle;
	*/
	title_move_timer++;
	titlePos.x = SCREEN_W / 2 + cos(title_angle) * 20;
	titlePos.y = SCREEN_H * 0.3f + sin(2 * title_angle) * 20;
	title_angle += ToRadian(1);


}