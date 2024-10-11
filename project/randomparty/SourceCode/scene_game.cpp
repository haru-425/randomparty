//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< �C���N���[�h >-----------------------------------------------------------
#include "all.h"
#include <sstream>

//------< �萔 >----------------------------------------------------------------

//------< �ϐ� >----------------------------------------------------------------
int game_state = 0;    // ���
int game_timer = 0;    // �^�C�}�[


Sprite* sprBG;
Sprite* sprOverley;
//--------------------------------------
//  �����ݒ�
//--------------------------------------
void game_init()
{
	game_state = 0;
	game_timer = 0;
}

//--------------------------------------
//  �X�V����
//--------------------------------------
void game_update()
{
	using namespace input;

	switch (game_state)
	{
	case 0:
		//////// �����ݒ� ////////

		player_init();
		enemy_init();
		timer_init();
		bomb_init();

		sprBG = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley = sprite_load(L"./Data/Images/title_layer02.png");
		game_state++;
		/*fallthrough*/
	case 1:
		//////// �p�����[�^�̐ݒ� ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		game_state++;
		/*fallthrough*/
	case 2:
		//////// �ʏ펞 ////////


		player_update();
		enemy_update();
		bomb_update();
		timer_update();

		break;
	}

	game_timer++;


#ifdef USE_IMGUI
	ImGui::Begin("ImGUI");

	static float value = 0;
	ImGui::DragFloat("value", &value, 0.001f);

	ImGui::End();
#endif


	}

//--------------------------------------
//  �`�揈��
//--------------------------------------
void game_render()
{
	GameLib::clear(0.0, 0.0, 0.0);

	sprite_render(sprBG, SCREEN_W / 2, SCREEN_H / 2, 3, 3, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	bomb_render();
	enemy_render();
	player_render();
	timer_render();
	//text_out(0, "Hello World", 0, 0);   // ���{


	sprite_render(sprOverley, SCREEN_W / 2, SCREEN_H / 2, 3, 3, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);


}

//--------------------------------------
//  �I������
//--------------------------------------
void game_deinit()
{
	player_deinit();
	enemy_deinit();
	timer_deinit();
	bomb_deinit();

	safe_delete(sprBG);
	safe_delete(sprOverley);
}
