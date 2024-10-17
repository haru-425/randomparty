#include "all.h"

void audio_init()
{

	music::load(0, L"./Data/Musics/9th_Attempt.wav");
	music::load(1, L"./Data/Musics/超頭脳バトル.wav");




	//sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");   // メニューなどのSE


	//sound::setVolume(XWB_STAGE1, XWB_STAGE1_MISSILE, 4.0f);
}

void audio_deinit()
{
	music::clear;

}
