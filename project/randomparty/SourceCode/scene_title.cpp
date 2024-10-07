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
    //music::stop(3);

    safe_delete(backspr);
}

void title_update()
{

    using namespace input;

    switch (title_state) 
    {

    case 0:
        //////// �����ݒ� ////////
        backspr = sprite_load(L"./Data/Images/Title(��).png");
        title_state++;
        /*fallthrough*/
    case 1:
        //////// �p�����[�^�̐ݒ� ////////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        title_state++;
        /*fallthrough*/

    case 2:
        if (TRG(0) & PAD_START) {
            nextScene = SCENE_GAME;
            break;
        }
        break;
    }

    title_timer++;

#ifdef USE_IMGUI
    ImGui::Begin("ImGUI");

    static float value = 0;
    ImGui::DragFloat("value", &value, 0.001f);

    ImGui::End();
#endif

}

void title_render()
{
    // ��ʂ�œh��Ԃ�
    //GameLib::clear(0.3f, 0.5f, 1.0f);

    sprite_render(backspr, SCREEN_W/2,SCREEN_H/2, 2, 2, 0, 0, 640, 480, 640 / 2, 480 / 2);
}