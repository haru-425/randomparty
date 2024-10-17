#include "all.h"
using namespace input;

int Tutorial_state;
extern int player_state;
extern int select_c;
extern int render_mode;



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
		
		++Tutorial_state;
		/*fallthrough*/

	case 1:
		++Tutorial_state;
		/*fallthrough*/

	case 2:
		player_update();
		if (TRG(0) & PAD_START)
		{
			++Tutorial_state;
			++render_mode;
		}
		break;
	case 3:
		player_deinit();

		++Tutorial_state;
		/*fallthrough*/

	case 4:
		player_init();
		player_state++;
		++Tutorial_state;
		/*fallthrough*/
	case 5:
		debug::setString("a");
		player_update();
		if (TRG(0) & PAD_START)
		{
			tuto_player_deinit();
			select_c = 0;
		}
		break;

	}
}

void tuto_player_deinit()
{
	player_deinit();
}