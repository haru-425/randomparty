#include "all.h"
#include "tyto_enemy.h"
int scene_state;
int enemy_number;
extern Button EndButton;
extern Button nextbutton;
extern Button backbutton;

using namespace input;

Sprite* enemy_description;

void enemy_tyto_init()
{
	scene_state = 0;
	enemy_number = 0;
}

void enemy_tyto_deinit()
{
	safe_delete(enemy_description);
}

void enemy_tyto_update()
{
	switch (scene_state)
	{
	case 0:
		enemy_description = sprite_load(L"./Data/Images/enemy_describe.png");
		scene_state++;
	case 1:
		nextbutton.next_button_init();
		backbutton.back_button_init();
		scene_state++;
	case 2:
		if (TRG(0) & L_CLICK && nextbutton.rect_click(nextbutton) && enemy_number < 3)
		{
			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			enemy_number++;
		}
		if (nextbutton.rect_click(nextbutton))
		{
			nextbutton.scale = { 1.1f,1.1f };
		}
		else {
			nextbutton.scale = { 1.0f,1.0f };
		}
		if (TRG(0) & L_CLICK && backbutton.rect_click(backbutton) && enemy_number > 0)
		{
			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			enemy_number--;
		}
		if (backbutton.rect_click(backbutton))
		{
			backbutton.scale = { 1.1f,1.1f };
		}
		else {
			backbutton.scale = { 1.0f,1.0f };
		}
		EndButton.end_button_update();
	default:
		break;
	}
	/*debug::setString("%d", enemy_number);*/
}

void enemy_tyto_render()
{
	sprite_render(enemy_description, 0, 0, 1, 1, enemy_number * 1920, 0);
	EndButton.end_button_render();
}