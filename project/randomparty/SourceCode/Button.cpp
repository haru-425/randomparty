#include "all.h"
using namespace input;

int button_state;
int end_button_state;
Button button;
Button EndButton;
Sprite* sprButton;
Sprite* sprEnd;


void Button::button_init()
{
    button_state = 0;
}

void Button::end_button_init() 
{
    end_button_state = 0;
}

void Button::button_deinit() 
{
    safe_delete(sprButton);
}

void Button::end_button_deinit()
{
    safe_delete(sprEnd);
}

void Button::button_update() 
{
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

void Button::end_button_update() 
{
    switch (end_button_state)
    {
    case 0:
        // 初期設定
        sprEnd = sprite_load(L"./Data/Images/returnButton.png");

        ++end_button_state;
        /*fallthrough*/

    case 1:
        // パラメータの設定
        EndButton.position = { 90, 60 };  // 中心位置
        EndButton.scale = { 1.0f, 1.0f };
        EndButton.texPos = { 0, 0 };
        EndButton.texSize = { END_TEX_W, END_TEX_H };
        EndButton.pivot = { END_PIVOT_X, END_PIVOT_Y };
        EndButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        

        ++end_button_state;
        /*fallthrough*/

    case 2:
        // 通常時の処理
        Button::end_button_act();

        break;
    }
}

void Button::button_render() 
{

    sprite_render(sprButton, button.position.x, button.position.y, 0.5f, 0.5f, 0, 0, 440, 440, 440 / 2, 440 / 2);
}

void Button::end_button_render()
{
    sprite_render(sprEnd, EndButton.position.x, EndButton.position.y, 1.5f, 1.5f, 0, 0, 128, 64, 128 / 2, 64 / 2);
}

void Button::button_act() 
{
    // ボタン内部で左クリックが押された場合
    if (TRG(0) & L_CLICK) {
        if (click()) {
            // ゲーム画面に遷移            
            game_start();
            return;
        }
    }
}

void Button::end_button_act() 
{
    // ボタン内部で左クリックが押された場合
    if (TRG(0) & L_CLICK) {
        if (end_click()) {
                       
            result_end();
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

bool Button::end_click() {
    // マウスカーソルの座標取得
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(window::getHwnd(), &point);

    // ボタンの四辺を取得
    float button_right = EndButton.position.x + EndButton.texSize.x / 1.3;
    float button_left = EndButton.position.x - EndButton.texSize.x / 1.3;
    float button_top = EndButton.position.y - EndButton.texSize.y / 1.3;
    float button_bottom = EndButton.position.y + EndButton.texSize.y / 1.3;

    // マウスの座標がボタンの範囲内かチェック
    bool isWithinX = (point.x >= button_left && point.x <= button_right);
    bool isWithinY = (point.y >= button_top && point.y <= button_bottom);

    // マウスがボタン範囲内ならクリックされたと判定
    return isWithinX && isWithinY;
}


