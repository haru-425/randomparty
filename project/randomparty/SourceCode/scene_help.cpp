#include "all.h"
#include <sstream>

using namespace input;

int help_state;
int select_c;

Sprite* sprBG_H;
Sprite* sprOverley_H;
Sprite* sprDescription_H;

extern Button button;
int help_page;
//--------------------------------------
//  初期設定
//--------------------------------------
void help_init()
{
	help_state = 0;
}

//--------------------------------------
//  終了処理
//--------------------------------------
void help_deinit()
{
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
		help_state++;
		/*fallthrough*/
	case 1:
		//////// パラメータの設定 ////////
		tuto_player_init();

		help_state++;
		/*fallthrough*/
	case 2:
		//////// 通常時 ////////
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(window::getHwnd(), &point);

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
        /*if (TRG(0) & PAD_START && select_c == 0)
        {
            sound::play(XWB_SYSTEM, XWB_SYSTEM_START);

            nextScene = SCENE_GAME;
            break;
        }
        if (TRG(0) & PAD_START && select_c == 1)
        {
            sound::play(XWB_TITLE, 0);

            nextScene = SCENE_SETTING;
            break;
        }*/

        break;
	}

}
void help_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);
	sprite_render(sprBG_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(sprOverley_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(sprDescription_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);

}
void help_act() 
{


}