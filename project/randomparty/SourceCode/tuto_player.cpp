#include "all.h"
using namespace input;

int Tutorial_state;
extern int player_state;
extern int select_c;
extern int render_mode;
extern int player_has_bomb;
extern Button nextbutton;

void tuto_player_init()
{
	Tutorial_state = 0;
}
void tuto_player_update()
{
	switch (Tutorial_state)
	{
	case 0:
		player_init();
		bomb_init();
		nextbutton.next_button_init();
		++Tutorial_state;
		/*fallthrough*/

	case 1:
		++Tutorial_state;
		/*fallthrough*/

	case 2:
		player_update();
		if (TRG(0) & L_CLICK && nextbutton.rect_click(nextbutton))
		{
			++Tutorial_state;
			++render_mode;
		}
		break;
	case 3:
		++Tutorial_state;
		/*fallthrough*/

	case 4:
		player_state++;
		player_has_bomb = BOMB_MAX;
		++Tutorial_state;
		/*fallthrough*/
	case 5:
		player_update();
		bomb_update();
		if (TRG(0) & L_CLICK && nextbutton.rect_click(nextbutton))
		{
			tuto_player_deinit();
			select_c = 0;
			render_mode = 0;
		}
		break;

	}
}

void tuto_player_deinit()
{
	player_deinit();
	bomb_deinit();
}