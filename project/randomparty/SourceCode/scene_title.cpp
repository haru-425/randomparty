#include "all.h"

#define SELECT_COUNT 2              //�I�����̐�

int title_state;
int title_timer;

int select_c;

Sprite* backspr;

//--------------------------------------
//  �����ݒ�
//--------------------------------------
void title_init()
{
    title_state = 0;
    title_timer = 0;
    select_c = 0;
}

//--------------------------------------
//  �I������
//--------------------------------------
void title_deinit()
{
    music::stop(3);

    safe_delete(backspr);
}

void title_update()
{
}
void title_render()
{
    // ��ʂ�œh��Ԃ�
    GameLib::clear(0.3f, 0.5f, 1.0f);
}