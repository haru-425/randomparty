#include "all.h"

using namespace std;

TIMER timer;



void timer_init() {
    
    timer.remaining_time = TIME_LIMIT/60;    // TIME_LIMIT を 60*180 として設定
    timer.frame_count = 0;                // フレームカウントをリセット
}

void timer_deinit() {
    
}

void timer_update() {
    
    timer.frame_count++;

    // 60フレームごとに1秒減らす
    if (timer.frame_count >= 60) {
        timer.remaining_time--;   // 残り時間を1秒減少
        timer.frame_count = 0;    // フレームカウントをリセット
    }

    // 残り時間が1以下になったらタイマー停止し、リザルト画面へ
    if (timer.remaining_time < 1) {
        timer.remaining_time = 0;
        game_end();
    }
}

void timer_render() {
    // 残り時間が1秒以上の場合のみ表示
    if (timer.remaining_time >= 1) {
        string time_text = "TIME: " + to_string(timer.remaining_time);
        text_out(1, time_text.c_str(), 0, 0, 2, 2, 1, 1, 1, 1);  // 座標 (0, 0) にテキスト描画
    }
}
