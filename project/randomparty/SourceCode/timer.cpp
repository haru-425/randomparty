#include "all.h"

// �^�C�}�[��ԕϐ�
int timer_state;
int remaining_time;  // �c�莞��
int frame_count;     // �t���[���J�E���g

void timer_init() {
    // �c�莞�Ԃ��������i30�b �~ 60�t���[���j
    remaining_time = TIME_LIMIT;    // TIME_LIMIT �� 60*30 �Ƃ��Đݒ�
    frame_count = 0;                // �t���[���J�E���g�����Z�b�g
}

void timer_deinit() {
    
}

void timer_update() {
    // �t���[�����ƂɃJ�E���g�𑝉�
    frame_count++;

    // 1�t���[�����u1�b�v�Ɍ����Ă�60�t���[���o�߂��Ƃ�1�b���炷
    if (frame_count  >= 0) {
        --remaining_time;   // �c�莞�Ԃ�1�b����
    }

    // �c�莞�Ԃ�0�ȉ��ɂȂ�����^�C�}�[��~
    if (remaining_time < 0) {
        remaining_time = 0;
        nextScene = SCENE_TITLE;
    }
}

void timer_render() {
    // �c�莞�Ԃ�b�P�ʂŕ\������
    int seconds = remaining_time / 60;  // �t���[���J�E���g�ŕb�P�ʂɕϊ�
    std::string time_text = "TIME: " + std::to_string(seconds) ;
    text_out(1, time_text.c_str(), 200, 0, 1, 1, 1, 1, 1, 1);  // ���W (200, 0) �Ƀe�L�X�g�`��
}