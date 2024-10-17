#include "all.h"
#include <sstream>

using namespace input;

int help_state;
int select_c;
int render_mode;

Sprite* sprBG_H;
Sprite* sprOverley_H;
Sprite* sprDescription_H;
Sprite* player_description;
Sprite* bomb_description;
Sprite* next_button;

extern Button button;
int help_page;
//--------------------------------------
//  初期設定
//--------------------------------------
void help_init()
{
	help_state = 0;
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

}

void help_update()
{
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
		next_button = sprite_load(L"./Data/Images/nextButton.png");
		help_state++;
		/*fallthrough*/
	case 1:
		//////// パラメータの設定 ////////
		tuto_player_init();
		render_mode = 1;
		help_state++;
		/*fallthrough*/
	case 2:
		//////// 通常時 ////////
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(window::getHwnd(), &point);
		tuto_player_update();
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
	bomb_render();
	switch (render_mode)
	{
	case 1:
		player_render();
		sprite_render(player_description, 0, 0, 1, 1, 0, 0);
		
		break;
	case 2:

		bomb_render();
		player_render();
		sprite_render(bomb_description, 0, 0, 1, 1, 0, 0);
		
		break;
	default:
		break;
	}

}
void help_act() 
{


}