//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< インクルード >-----------------------------------------------------------
#include "all.h"
#include <sstream>

//------< 定数 >----------------------------------------------------------------

//------< 変数 >----------------------------------------------------------------
int game_state = 0;    // 状態
int game_timer = 0;    // タイマー


Sprite* sprBG;
Sprite* sprOverley;
//--------------------------------------
//  初期設定
//--------------------------------------
void game_init()
{
	game_state = 0;
	game_timer = 0;
}

//--------------------------------------
//  更新処理
//--------------------------------------
void game_update()
{
	using namespace input;

	switch (game_state)
	{
	case 0:
		//////// 初期設定 ////////

		player_init();
		enemy_init();
		timer_init();
		bomb_init();

		sprBG = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley = sprite_load(L"./Data/Images/title_layer02.png");
		game_state++;
		/*fallthrough*/
	case 1:
		//////// パラメータの設定 ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		game_state++;
		/*fallthrough*/
	case 2:
		//////// 通常時 ////////


		player_update();
		enemy_update();
		bomb_update();
		timer_update();

		break;
	}

	game_timer++;


#ifdef USE_IMGUI
	ImGui::Begin("ImGUI");

	static float value = 0;
	ImGui::DragFloat("value", &value, 0.001f);

	ImGui::End();
#endif


	}

//--------------------------------------
//  描画処理
//--------------------------------------
void game_render()
{
	GameLib::clear(0.0, 0.0, 0.0);

	sprite_render(sprBG, SCREEN_W / 2, SCREEN_H / 2, 3, 3, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	bomb_render();
	enemy_render();
	player_render();
	timer_render();
	//text_out(0, "Hello World", 0, 0);   // 見本


	sprite_render(sprOverley, SCREEN_W / 2, SCREEN_H / 2, 3, 3, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);


}

//--------------------------------------
//  終了処理
//--------------------------------------
void game_deinit()
{
	player_deinit();
	enemy_deinit();
	timer_deinit();
	bomb_deinit();

	safe_delete(sprBG);
	safe_delete(sprOverley);
}
