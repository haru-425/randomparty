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
	int bolume(int bolume)
	{
		switch (bolume)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	}

};

void setting_init();
void setting_deinit();
void setting_update();
void setting_render();

#endif//SETTING_H

