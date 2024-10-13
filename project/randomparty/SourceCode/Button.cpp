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
        // �����ݒ�
        sprButton = sprite_load(L"./Data/Images/playButton.png");

        ++button_state;
        /*fallthrough*/

    case 1:
        // �p�����[�^�̐ݒ�
        button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };  // ���S�ʒu
        button.scale = { 1.0f, 1.0f };
        button.texPos = { 0, 0 };
        button.texSize = { BUTTON_TEX_W, BUTTON_TEX_H };
        button.pivot = { BUTTON_PIVOT_X, BUTTON_PIVOT_Y };
        button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button.radius = BUTTON_TEX_W / 4;

        ++button_state;
        /*fallthrough*/

    case 2:
        // �ʏ펞�̏���
        Button::button_act();

        break;
    }
}

void Button::button_render() {
   

    
    sprite_render(sprButton, button.position.x, button.position.y, 0.5f, 0.5f, 0, 0, 440, 440, 440 / 2, 440 / 2);
}

void Button::button_act() {
    // �{�^�������ō��N���b�N�������ꂽ�ꍇ
    if (TRG(0) & L_CLICK) {
        if (click()) {
            // �Q�[����ʂɑJ��
            timer_init();
            
            nextScene = SCENE_GAME;
            return;
        }
    }
}

bool Button::click() {
    // �}�E�X�J�[�\���̍��W�擾
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(window::getHwnd(), &point);

    // �~�̒��S���W
    float centerX = button.position.x;
    float centerY = button.position.y;

    // �}�E�X�J�[�\���Ɖ~�̒��S�Ƃ̋������v�Z
    float distance = sqrt(pow(point.x - centerX, 2) + pow(point.y - centerY, 2));

    // �������{�^���̔��a�ȉ��ł���΃N���b�N���L��
    return (distance <= button.radius);
}
