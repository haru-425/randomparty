#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

// 定数の定義
//
#define BGM_TITLE 0
#define BGM_GAME 1
#define BGM_RESULT 2
// XWBの種類
#define XWB_SYSTEM 0
// SYSTEMの効果音
#define XWB_SYSTEM_BOMB_FAILURE 0
#define XWB_SYSTEM_EXPLODE		1
#define XWB_SYSTEM_DEATH		2
#define XWB_SYSTEM_RESULT		3
#define XWB_SYSTEM_BUTTON		4

// 関数のプロトタイプ宣言
void audio_init();
void audio_deinit();

#endif//AUDIO_H
