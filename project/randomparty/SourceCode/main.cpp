//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< namespace >-----------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;
extern Bolume game_volume;
//------------------------------------------------------------------------------
//  WinMain�i�G���g���|�C���g�j
//------------------------------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)// �g�p���Ȃ��ϐ��͋L�q���Ȃ�
{
	// �Q�[�����C�u�����̏����ݒ�
	GameLib::init(L"FIGAVOID", SCREEN_W, SCREEN_H, FULLSCREEN);

	//game_init();
	audio_init();
	while (GameLib::gameLoop())
	{




		// �V�[���؂�ւ�����
		if (curScene != nextScene)
		{
			// ���݂̃V�[���ɉ������I������
			switch (curScene)
			{
			case SCENE_TITLE:
				title_deinit();
				break;
			case SCENE_GAME:
				game_deinit();
				break;

			case SCENE_RESULT:
				result_deinit();
				break;

			case SCENE_HELP:
				help_deinit();
				break;

			case SCENE_SETTING:
				setting_deinit();
				break;
			}
			for (int i; i < 4; i++)
			{

				music::setVolume(i, game_volume.bgm_volume * 5.0f);
			}
			for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
			{

				sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * 5.0f);
			}
			// ���̃V�[���ɉ����������ݒ菈��
			switch (nextScene)
			{
			case SCENE_TITLE:
				title_init();
				break;
			case SCENE_GAME:
				game_init();
				break;

			case SCENE_RESULT:
				result_init();
				break;
			case SCENE_HELP:
				help_init();
				break;

			case SCENE_SETTING:
				setting_init();
				break;
			}
			// nextScene �� curScene �ɂȂ�
			curScene = nextScene;
		}

		// ���͏���
		input::update();
		music::update();
		// ���݂̃V�[���ɉ������X�V�E�`�揈��
		switch (curScene)
		{
		case SCENE_TITLE:
			title_update();
			title_render();
			break;
		case SCENE_GAME:
			game_update();
			game_render();
			break;
		case SCENE_RESULT:
			result_update();
			result_render();
			break;

		case SCENE_HELP:
			help_update();
			help_render();
			break;

		case SCENE_SETTING:
			setting_update();
			setting_render();
			break;
		}
		for (int i = 0; i < 4; i++)
		{

			music::setVolume(i, game_volume.bgm_volume * (1.0f / 5.0f));
		}
		for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
		{

			sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * (1.0f / 5.0f));
		}
		//debug::setString("B:S %d:%d", game_volume.bgm_volume, game_volume.se_volume);
#ifdef USE_IMGUI
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
#endif

		// ���݂̃V�[�����X�V�E�`��
		/*game_update();
		game_render();*/

#ifdef USE_IMGUI
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

		// �f�o�b�O�������`��
		debug::display(1.0f, 1.0f, 1.0f, 1, 1);

		//debug::setString("GP1_01 SAMPLE");

		// �o�b�N�o�b�t�@�̓��e��\��
		GameLib::present(1, 0);
	}

	// ���݂̃V�[���ɉ������I���������s��
	switch (curScene)
	{
	case SCENE_TITLE:
		title_deinit();
		break;
	case SCENE_GAME:
		game_deinit();
		break;
	case SCENE_RESULT:
		result_deinit();
		break;
	case SCENE_HELP:
		help_deinit();
		break;
	case SCENE_SETTING:
		setting_deinit();
		break;
	}

	// �Q�[���V�[���̏I��
	//game_deinit();
	audio_deinit();
	// �Q�[�����C�u�����̏I������
	GameLib::uninit();

	return 0;
}
