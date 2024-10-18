#include "all.h"
#include <sstream>

using namespace input;

int help_state;
int select_c;
int render_mode;
int help_timer;

Sprite* sprBG_H;
Sprite* sprOverley_H;
Sprite* sprDescription_H;
Sprite* player_description;
Sprite* bomb_description;
Sprite* next_button;
Sprite* mouse1;
Sprite* mouse2;
Sprite* arrow;



extern Button button;
int help_page;
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
		mouse1= sprite_load(L"./Data/Images/マウス.png");
		mouse2 = sprite_load(L"./Data/Images/マウス右クリ.png");
		arrow = sprite_load(L"./Data/Images/mugen.png");
		help_state++;
		/*fallthrough*/
	case 1:
		//////// パラメータの設定 ////////
		tuto_player_init();
		enemy_tyto_init();
		render_mode = 3;
		help_state++;
		/*fallthrough*/
	case 2:
		//////// 通常時 ////////
		/*tuto_player_update();*/
		enemy_tyto_update();
        if (TRG(0) & PAD_DOWN)
        {
            select_c++;
        }if (TRG(0) & PAD_UP)
        {
            select_c--;
        }
		switch (select_c)
		{
		case1:
			tuto_player_update();
			break;
		case 2:
			enemy_tyto_update();
			break;
		default:
			break;
			
		}
        
        break;
	}

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
	case 1:
		player_render();
		sprite_render(player_description, 0, 0, 1, 1, 0, 0);
		sprite_render(arrow, 1400, 160, 1, 1, 0, 0);
		sprite_render(mouse1, 1610, 260, 0.5, 0.5, 0, 0);
		sprite_render(next_button, -20, 0, 1, 1, 0, 0);
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
		sprite_render(next_button, -20, 0, 1, 1, 0, 0);
		break;
	case 3:
		enemy_tyto_render();
		break;
	default:
		break;
	}

}
void help_act() 
{


}