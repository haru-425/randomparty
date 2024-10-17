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
Sprite* sprBG;
Sprite* sprOverley;
//------< �萔 >----------------------------------------------------------------

//------< �ϐ� >----------------------------------------------------------------
int game_state = 0;    // ���
int game_timer = 0;    // �^�C�}�[
int countDown;
bool countdownComplete;
using namespace std;

SCORE score;
//--------------------------------------
//  �����ݒ�
//--------------------------------------
void game_init()
{
	game_state = 0;
	game_timer = 0;
	countDown = 3;
	countdownComplete = false;
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

		GameLib::setBlendMode(Blender::BS_ALPHA);

		player_init();
		enemy_init();
		timer_init();
		bomb_init();

		sprBG = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley = sprite_load(L"./Data/Images/title_layer02.png");

		SetCursorPos(SCREEN_W / 2, SCREEN_H / 2);
		game_state++;
		/*fallthrough*/
	case 1:
		//////// �p�����[�^�̐ݒ� ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(BGM_GAME, true);
		game_state++;
		/*fallthrough*/
	case 2:
		if (countDown >= 0) {
			static int frameCounter = 0;
			frameCounter++;
			if (frameCounter >= 60) { // 1�b���ɃJ�E���g�_�E��
				frameCounter = 0;
				countDown--;
			}
		}
		else {
			countdownComplete = true;
		}

	case 3:
		//////// �ʏ펞 ////////

		if (countdownComplete) {
			enemy_update();
			bomb_update();
			timer_update();
			score.near_score();
		}
		player_update();
		break;
	}

	game_timer++;

	//
	//#ifdef USE_IMGUI
	//	ImGui::Begin("ImGUI");
	//
	//	static float value = 0;
	//	ImGui::DragFloat("value", &value, 0.001f);
	//
	//	ImGui::End();
	//#endif


}

//--------------------------------------
//  �`�揈��
//--------------------------------------
void game_render()
{
	GameLib::clear(0.0, 0.0, 0.0);

	sprite_render(sprBG, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	sprite_render(sprOverley, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);

	player_render();

	if (countdownComplete) {
		bomb_render();
		enemy_render();
		timer_render();
	}
	else if (countDown >= 0) {
		text_out(6, to_string(countDown), SCREEN_W / 2 + 120, SCREEN_H / 2, 20, 20, 1, 1, 1, 0.5f, TEXT_ALIGN::MIDDLE);
	}
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


	music::stop(BGM_GAME);
}
