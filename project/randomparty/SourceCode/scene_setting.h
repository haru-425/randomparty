#pragma once
#ifndef SETTING_H
#define SETTING_H


class Bolume
{
public:
	Bolume()
	{
		bgm_volume = 3;
		se_volume = 3;
	}
	int bgm_volume;
	int se_volume;

};

void setting_init();
void setting_deinit();
void setting_update();
void setting_render();

#endif//SETTING_H

