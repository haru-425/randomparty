#include"all.h"

int result_state;

void result_init()
{

}

void result_deinit()
{

}

void result_update() 
{
	result_end();
}

void result_render() 
{
	GameLib::clear(0.0, 0.0, 0.0);
	text_out(1, "push enter key", SCREEN_W * 0.275, SCREEN_H * 0.7, 2, 2);//‰¼
}