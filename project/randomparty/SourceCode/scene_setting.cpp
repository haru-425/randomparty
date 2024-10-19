#include "all.h"

using namespace input;

Bolume game_volume;
Button bgm_volume_up;
Button bgm_volume_Down;
Button se_volume_up;
Button se_volume_Down;

Sprite* volume_change;

int setting_state;

void setting_init()
{
	setting_state=0;
}

void setting_deinit()
{

}

void setting_update()
{
	switch (setting_state)
	{
	case 0:
		volume_change = sprite_load(L"./Data/Images/arrow01.png");
		setting_state++;
	case 1:
		setting_state++;
	case 2:
		if (TRG(0) & L_CLICK && bgm_volume_up.rect_click(bgm_volume_up))
		{
			game_volume.bgm_volume++;
		}
		if (TRG(0) & L_CLICK && bgm_volume_Down.rect_click(bgm_volume_Down))
		{
			game_volume.bgm_volume--;
		}
		if (TRG(0) & L_CLICK && se_volume_up.rect_click(se_volume_up))
		{
			game_volume.se_volume++;
		}
		if (TRG(0) & L_CLICK && se_volume_Down.rect_click(se_volume_Down))
		{
			game_volume.se_volume--;
		}
		break;
	default:
		break;
	}
}

void setting_render()
{
	GameLib::text_out(6, "BGM VOLUME", 400, 300, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(game_volume.bgm_volume), SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
	GameLib::text_out(6, "SE VOLUME", SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(game_volume.bgm_volume), SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
}