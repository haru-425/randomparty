#include "all.h"

extern Bolume game_volume;
void audio_init()
{

	music::load(0, L"./Data/Musics/9th_Attempt.wav");
	music::load(1, L"./Data/Musics/�����]�o�g��.wav");
	music::load(2, L"./Data/Musics/�}�b�h�T�C�G���e�B�X�q.wav");
	music::load(3, L"./Data/Musics/���_�����~�b�V����.wav");

	//for (int i = 0; i < 3; i++)
	//{

	//	music::setVolume(i, VOLUME_BGM);
	//}


	sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");   // ���j���[�Ȃǂ�SE
	//for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
	//{

	//	sound::setVolume(XWB_SYSTEM, i, VOLUME_FX);
	//}

	//sound::setVolume(XWB_SYSTEM, XWB_SYSTEM_RESULT, VOLUME_FX_RESULT);
	//sound::setVolume(XWB_STAGE1, XWB_STAGE1_MISSILE, 4.0f);
	for (int i; i < 4; i++)
	{

		music::setVolume(i, game_volume.bgm_volume * 5.0f);
	}
	for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
	{

		sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * 5.0f);
	}
}

void audio_deinit()
{
	music::clear;

}

