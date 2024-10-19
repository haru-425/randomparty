#include "all.h"
#include <sstream>

using namespace input;

int help_state;
int select_c;
int render_mode;
int help_timer;
int help_page;

Sprite* sprBG_H;
Sprite* sprOverley_H;
Sprite* sprDescription_H;
Sprite* player_description;
Sprite* bomb_description;
Sprite* next_button;
Sprite* mouse1;
Sprite* mouse2;
Sprite* arrow;
Sprite* select_button1;
Sprite* select_button2;
Sprite* select_button3;
Sprite* bomb_stock_text;
Sprite* score_nabi;

extern Button button;
extern Button select_player_button;
extern Button select_enemy_button;
extern Button select_score_button;
extern Button EndButton;
extern int enemy_number;

extern Button nextbutton;
extern Button backbutton;

//--------------------------------------
//  初期設定
//--------------------------------------
void help_init()
{
	help_state = 0;
	help_timer = 0;
	bomb_init();
}

//--------------------------------------
//  終了処理
//--------------------------------------
void help_deinit()
{

	safe_delete(player_description);
	safe_delete(bomb_description);
	safe_delete(sprBG_H);
	safe_delete(sprOverley_H);
	safe_delete(sprDescription_H);
	safe_delete(mouse1);
	safe_delete(mouse2);
	safe_delete(arrow);
	safe_delete(select_button1);
	safe_delete(select_button2);
	safe_delete(select_button3);
	safe_delete(bomb_stock_text);
	safe_delete(score_nabi);
}

void help_update()
{
	help_timer++;
	switch (help_state)
	{
	case 0:
		//////// 初期設定 ////////

		GameLib::setBlendMode(Blender::BS_ALPHA);


		sprBG_H = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley_H = sprite_load(L"./Data/Images/title_layer02.png");
		sprDescription_H = sprite_load(L"./Data/Images/enemy_describe.png");
		player_description = sprite_load(L"./Data/Images/help_player.png");
		bomb_description = sprite_load(L"./Data/Images/help_boomb.png");
		next_button = sprite_load(L"./Data/Images/arrow00.png");
		mouse1 = sprite_load(L"./Data/Images/マウス.png");
		mouse2 = sprite_load(L"./Data/Images/マウス右クリ.png");
		arrow = sprite_load(L"./Data/Images/mugen.png");
		select_button1 = sprite_load(L"./Data/Images/player_navi_button.png");
		select_button2 = sprite_load(L"./Data/Images/enemy_describ_button.png");
		select_button3 = sprite_load(L"./Data/Images/score_describe.png");
		bomb_stock_text = sprite_load(L"./Data/Images/bomb_stock_text.png");
		score_nabi = sprite_load(L"./Data/Images/score_nabi.png");
		help_state++;
		/*fallthrough*/
	case 1:
		//////// パラメータの設定 ////////
		tuto_player_init();
		enemy_tyto_init();
		select_player_button.tuto_player_button_init();
		select_enemy_button.tyto_enemy_button_init();
		select_score_button.descript_score_button_init();
		render_mode = 0;
		help_state++;
		/*fallthrough*/
	case 2:
		//////// 通常時 ////////
		///*tuto_player_update();*/
		//enemy_tyto_update();
		if (TRG(0) & L_CLICK && select_player_button.rect_click(select_player_button) && render_mode == 0)
		{
			render_mode = 1;
			select_c = 1;
		}
		if (select_player_button.rect_click(select_player_button))
		{
			select_player_button.scale = { 0.4f,0.4f };
		}
		else {
			select_player_button.scale = { 0.3f,0.3f };
		}

		if (TRG(0) & L_CLICK && select_enemy_button.rect_click(select_enemy_button) && render_mode == 0)
		{
			render_mode = 3;
			select_c = 2;
		}
		if (select_enemy_button.rect_click(select_enemy_button))
		{
			select_enemy_button.scale = { 0.4f,0.4f };
		}
		else {
			select_enemy_button.scale = { 0.3f,0.3f };
		}

		if (TRG(0) & L_CLICK && select_score_button.rect_click(select_score_button) && render_mode == 0)
		{
			render_mode = 4;
			select_c = 3;
		}
		if (select_score_button.rect_click(select_score_button))
		{
			select_score_button.scale = { 0.4f,0.4f };
		}
		else {
			select_score_button.scale = { 0.3f,0.3f };
		}





		switch (select_c)
		{
		case 1:
			tuto_player_update();
			break;
		case 2:
			enemy_tyto_update();
			break;

		case 3:
			EndButton.end_button_update();
			break;
		default:
			EndButton.end_button_update();
			break;

		}

		break;
	}
	/*debug::setString("%d", select_c);*/
}
void help_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);
	sprite_render(sprBG_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(sprOverley_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	//sprite_render(sprDescription_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	switch (render_mode)
	{
	case 0:
		sprite_render(select_button1, select_player_button.position.x, select_player_button.position.y, select_player_button.scale.x, select_player_button.scale.y, 0, 0, 1500, 500, 750, 250);
		sprite_render(select_button2, select_enemy_button.position.x, select_enemy_button.position.y, select_enemy_button.scale.x, select_enemy_button.scale.y, 0, 0, 1500, 500, 750, 250);
		sprite_render(select_button3, select_score_button.position.x, select_score_button.position.y, select_score_button.scale.x, select_score_button.scale.y, 0, 0, 1500, 500, 750, 250);
		EndButton.end_button_render();
		//primitive::rect(710, 820, 1500*0.3f, 500*0.3f);

		break;
	case 1:
		player_render();
		sprite_render(player_description, 0, 0, 1, 1, 0, 0);
		sprite_render(arrow, 1400, 160, 1, 1, 0, 0);
		sprite_render(mouse1, 1610, 260, 0.5, 0.5, 0, 0);
		sprite_render(next_button, nextbutton.position.x, nextbutton.position.y, nextbutton.scale.x, nextbutton.scale.y, 0, 0, 100, 300, 50, 150);
		break;
	case 2:
		player_render();
		sprite_render(bomb_description, 0, 0, 1, 1, 0, 0);
		if (help_timer >> 5 & 0x01)
		{
			sprite_render(mouse2, 1600, 280, 0.5, 0.5, 0, 0);
		}
		else
		{
			sprite_render(mouse1, 1600, 280, 0.5, 0.5, 0, 0);
		}
		bomb_render();
		sprite_render(next_button, nextbutton.position.x, nextbutton.position.y, nextbutton.scale.x, nextbutton.scale.y, 0, 0, 100, 300, 50, 150);
		sprite_render(bomb_stock_text, 1750, 820, 0.26f, 0.26f, 0, 0);
		break;
	case 3:
		enemy_tyto_render();
		switch (enemy_number)
		{
		case 0:
			sprite_render(next_button, nextbutton.position.x, nextbutton.position.y, nextbutton.scale.x, nextbutton.scale.y, 0, 0, 100, 300, 50, 150);

			break;
		case 3:
			sprite_render(next_button, backbutton.position.x, backbutton.position.y, backbutton.scale.x, backbutton.scale.y, 0, 0, 100, 300, 50, 150, ToRadian(180));
			break;
		default:
			sprite_render(next_button, nextbutton.position.x, nextbutton.position.y, nextbutton.scale.x, nextbutton.scale.y, 0, 0, 100, 300, 50, 150);
			sprite_render(next_button, backbutton.position.x, backbutton.position.y, backbutton.scale.x, backbutton.scale.y, 0, 0, 100, 300, 50, 150, ToRadian(180));
			break;
		}
		break;
	case 4:
		sprite_render(score_nabi, 0, 0, 1, 1, 0, 0);
		EndButton.end_button_render();
		break;
	default:
		break;
	}

}
void help_act()
{


}