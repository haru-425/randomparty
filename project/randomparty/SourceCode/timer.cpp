#include "all.h"

using namespace std;


int timer_state;
int remaining_time;  // 残り時間
int frame_count;     // フレームカウント

void timer_init() {
    // 残り時間を初期化（30秒 × 60フレーム）
    remaining_time = TIME_LIMIT/60;    // TIME_LIMIT を 60*30 として設定
    frame_count = 0;                // フレームカウントをリセット
}

void timer_deinit() {
    
}

void timer_update() {
    
    frame_count++;

    // 60フレームごとに1秒減らす
    if (frame_count >= 60) {
        remaining_time--;   // 残り時間を1秒減少
        frame_count = 0;    // フレームカウントをリセット
    }

    // 残り時間が1以下になったらタイマー停止し、リザルト画面へ
    if (remaining_time < 1) {
        remaining_time = 1;
        game_end();
    }
}

void timer_render() {
    // 残り時間が1秒以上の場合のみ表示
    if (remaining_time >= 1) {
        string time_text = "TIME: " + to_string(remaining_time);
        text_out(1, time_text.c_str(), 0, 0, 2, 2, 1, 1, 1, 1);  // 座標 (0, 0) にテキスト描画
    }
}
