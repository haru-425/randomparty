#include "all.h"
#include <sstream>

using namespace input;

int help_state;

Sprite* sprBG_H;
Sprite* sprOverley_H;
Sprite* sprDescription_H;

extern Button button;
int help_page;
//--------------------------------------
//  �����ݒ�
//--------------------------------------
void help_init()
{
	help_state = 0;


}

//--------------------------------------
//  �I������
//--------------------------------------
void help_deinit()
{
	safe_delete(sprBG_H);
	safe_delete(sprOverley_H);
	safe_delete(sprDescription_H);

}

void help_update()
{

	switch (help_state)
	{
	case 0:
		//////// �����ݒ� ////////

		GameLib::setBlendMode(Blender::BS_ALPHA);


		sprBG_H = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley_H = sprite_load(L"./Data/Images/title_layer02.png");
		sprDescription_H = sprite_load(L"./Data/Images/enemy_describe.png");
		help_state++;
		/*fallthrough*/
	case 1:
		//////// �p�����[�^�̐ݒ� ////////

		help_state++;
		/*fallthrough*/
	case 2:
		//////// �ʏ펞 ////////

		help_act();
		break;
	}


}
void help_render()
{
	// ��ʂ�œh��Ԃ�
	GameLib::clear(0.3f, 0.5f, 1.0f);
	sprite_render(sprBG_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(sprOverley_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(sprDescription_H, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);

}
void help_act() 
{


}