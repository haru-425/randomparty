#include "all.h"

using namespace input;

Bolume game_volume;
Button bgm_volume_up;
Button bgm_volume_Down;
Button se_volume_up;
Button se_volume_Down;
extern Button EndButton;

Sprite* sprBG_S;
Sprite* sprOverley_S;
Sprite* volume_change;
Sprite* volume_setting;

int setting_state;

void setting_init()
{
	setting_state=0;
}

void setting_deinit()
{
	safe_delete(volume_change);
	safe_delete(sprBG_S);
	safe_delete(sprOverley_S);
	safe_delete(volume_setting);
}

void setting_update()
{
	switch (setting_state)
	{
	case 0:
		GameLib::setBlendMode(Blender::BS_ALPHA);
		volume_change = sprite_load(L"./Data/Images/arrow01.png");
		sprBG_S = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley_S = sprite_load(L"./Data/Images/title_layer02.png");
		volume_setting = sprite_load(L"./Data/Images/setting.png");
		setting_state++;
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);
		bgm_volume_up.bgm_volume_up_init();
		bgm_volume_Down.bgm_volume_Down_init();
		se_volume_up.se_volume_up_init();
		se_volume_Down.se_volume_Down_init();
		setting_state++;
	case 2:
		if (TRG(0) & L_CLICK && bgm_volume_up.rect_click(bgm_volume_up) && game_volume.bgm_volume < 5)
		{
			game_volume.bgm_volume++;
		}
		if (TRG(0) & L_CLICK && bgm_volume_Down.rect_click(bgm_volume_Down) && game_volume.bgm_volume > 0)
		{
			game_volume.bgm_volume--;
		}
		if (TRG(0) & L_CLICK && se_volume_up.rect_click(se_volume_up) && game_volume.se_volume < 5)
		{
			game_volume.se_volume++;
		}
		if (TRG(0) & L_CLICK && se_volume_Down.rect_click(se_volume_Down) && game_volume.se_volume > 0)
		{
			game_volume.se_volume--;
		}
		EndButton.end_button_update();
	default:
		break;
	}

}

void setting_render()
{
	GameLib::clear(0.3f, 0.5f, 1.0f);
	sprite_render(sprBG_S, 0, 0, 1, 1, 0, 0);
	sprite_render(sprOverley_S, 0, 0, 1, 1, 0, 0);
	sprite_render(volume_setting, 0, 0, 1, 1, 0, 0);
	GameLib::text_out(6, "BGM VOLUME", 850, 400, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(game_volume.bgm_volume), 1250, 400, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
	GameLib::text_out(6, "SE VOLUME", 850, 600, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(game_volume.se_volume), 1250, 600, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
	if (game_volume.bgm_volume < 5)
	{
		sprite_render(volume_change, 1450, 330, 0.3f, 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90));
	}
	else
	{
		sprite_render(volume_change, 1450, 330, 0.3f, 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90),1,1,1, 0.5);
	}
	if (game_volume.bgm_volume > 0)
	{
		sprite_render(volume_change, 970, 330, 0.3f, 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90));
	}
	else
	{
		sprite_render(volume_change, 970, 330, 0.3f, 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90),1,1,1,0.5);
	}
	if (game_volume.se_volume < 5)
	{
		sprite_render(volume_change, 1450, 530, 0.3f, 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90));
	}
	else
	{
		sprite_render(volume_change, 1450, 530, 0.3f, 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90), 1, 1, 1, 0.5);
	}
	if (game_volume.se_volume > 0)
	{
		sprite_render(volume_change, 970, 530, 0.3f, 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90));
	}
	else
	{
		sprite_render(volume_change, 970, 530, 0.3f, 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90), 1, 1, 1, 0.5);
	}
	
	
	
	EndButton.end_button_render();
}