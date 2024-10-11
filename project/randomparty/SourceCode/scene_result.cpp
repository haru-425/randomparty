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
	text_out(1, "rere", 0, 0, 2, 2);
}