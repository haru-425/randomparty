#include "all.h"

// ゲームの音量管理用の外部変数
extern Bolume game_volume;

// 音声の初期化関数
void audio_init()
{
    // ゲームで使用する音楽ファイルを読み込む
    music::load(0, L"./Data/Musics/9th_Attempt.wav");          
    music::load(1, L"./Data/Musics/超頭脳バトル.wav");         
    music::load(2, L"./Data/Musics/マッドサイエンティス子.wav");
    music::load(3, L"./Data/Musics/拠点制圧ミッション.wav");    

    // システム音（メニューなどで使用するSE）をまとめたサウンドファイルを読み込む
    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");   
}

// 音声リソースの解放関数
void audio_deinit()
{
    // 音楽リソースを解放
    music::clear;  // メモリにロードされた音楽データを全てクリア
}