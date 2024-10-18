#include "all.h"
#include "tyto_enemy.h"
int scene_state;
int enemy_number;
extern Button EndButton;


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
		scene_state++;
	case 2:

		EndButton.end_button_update();
	default:
		break;
	}
}

void enemy_tyto_render()
{
	sprite_render(enemy_description, 0, 0, 1, 1, enemy_number * 1980, 0);
	EndButton.end_button_render();
}