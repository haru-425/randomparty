#include "all.h"

void audio_init()
{

	music::load(0, L"./Data/Musics/9th_Attempt.wav");
	music::load(1, L"./Data/Musics/�����]�o�g��.wav");




	//sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");   // ���j���[�Ȃǂ�SE


	//sound::setVolume(XWB_STAGE1, XWB_STAGE1_MISSILE, 4.0f);
}

void audio_deinit()
{
	music::clear;

}
