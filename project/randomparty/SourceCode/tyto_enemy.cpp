#include "all.h"
#include "tyto_enemy.h"
int scene_state;
int enemy_number;
extern Button EndButton;
extern Button nextbutton;

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
		scene_state++;
	case 2:
		if (TRG(0) & L_CLICK && nextbutton.rect_click(nextbutton) && enemy_number<3)
		{
			enemy_number++;
		}
		if (TRG(0) & L_CLICK && nextbutton.rect_click(nextbutton) && enemy_number < 3)
		{
			enemy_number++;
		}
		EndButton.end_button_update();
	default:
		break;
	}
	debug::setString("%d", enemy_number);
}

void enemy_tyto_render()
{
	sprite_render(enemy_description, 0, 0, 1, 1, enemy_number * 1920, 0);
	EndButton.end_button_render();
}