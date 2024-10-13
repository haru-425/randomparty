#include "all.h"
using namespace input;

int button_state;
Button button;
Sprite* sprButton;


void Button::button_init() {
    button_state = 0;

    
}

void Button::button_deinit() {
    safe_delete(sprButton);
}

void Button::button_update() {
    switch (button_state)
    {
    case 0:
        // 初期設定
        sprButton = sprite_load(L"./Data/Images/playButton.png");

        ++button_state;
        /*fallthrough*/

    case 1:
        // パラメータの設定
        button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };  // 中心位置
        button.scale = { 1.0f, 1.0f };
        button.texPos = { 0, 0 };
        button.texSize = { BUTTON_TEX_W, BUTTON_TEX_H };
        button.pivot = { BUTTON_PIVOT_X, BUTTON_PIVOT_Y };
        button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button.radius = BUTTON_TEX_W / 4;

        ++button_state;
        /*fallthrough*/

    case 2:
        // 通常時の処理
        Button::button_act();

        break;
    }
}

void Button::button_render() {
   

    
    sprite_render(sprButton, button.position.x, button.position.y, 0.5f, 0.5f, 0, 0, 440, 440, 440 / 2, 440 / 2);
}

void Button::button_act() {
    // ボタン内部で左クリックが押された場合
    if (TRG(0) & L_CLICK) {
        if (click()) {
            // ゲーム画面に遷移
            timer_init();
            
            nextScene = SCENE_GAME;
            return;
        }
    }
}

bool Button::click() {
    // マウスカーソルの座標取得
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(window::getHwnd(), &point);

    // 円の中心座標
    float centerX = button.position.x;
    float centerY = button.position.y;

    // マウスカーソルと円の中心との距離を計算
    float distance = sqrt(pow(point.x - centerX, 2) + pow(point.y - centerY, 2));

    // 距離がボタンの半径以下であればクリックが有効
    return (distance <= button.radius);
}
