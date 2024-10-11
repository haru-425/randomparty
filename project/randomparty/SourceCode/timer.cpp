#include "all.h"

// タイマー状態変数
int timer_state;
int remaining_time;  // 残り時間
int frame_count;     // フレームカウント

void timer_init() {
    // 残り時間を初期化（30秒 × 60フレーム）
    remaining_time = TIME_LIMIT;    // TIME_LIMIT を 60*30 として設定
    frame_count = 0;                // フレームカウントをリセット
}

void timer_deinit() {
    
}

void timer_update() {
    // フレームごとにカウントを増加
    frame_count++;

    // 1フレームを「1秒」に見立てて60フレーム経過ごとに1秒減らす
    if (frame_count  >= 60) {
        --remaining_time;   // 残り時間を1秒減少
    }

    // 残り時間が0以下になったらタイマー停止
    if (remaining_time < 1) {
        remaining_time = 0;
        game_end();
    }
}

void timer_render() {
    // 残り時間を秒単位で表示する
    int seconds = remaining_time / 60;  // フレームカウントで秒単位に変換

    // 秒数が1未満の場合は1秒を表示する
    if (seconds < 1) {
        seconds = 1;
    }

    std::string time_text = "TIME: " + std::to_string(seconds) ;
    text_out(1, time_text.c_str(), 0, 0, 2, 2, 1, 1, 1, 1);  // 座標 (0, 0) にテキスト描画
}