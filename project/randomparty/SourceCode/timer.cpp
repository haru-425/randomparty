#include "all.h"

using namespace std;


int timer_state;
int remaining_time;  // �c�莞��
int frame_count;     // �t���[���J�E���g

void timer_init() {
    // �c�莞�Ԃ��������i30�b �~ 60�t���[���j
    remaining_time = TIME_LIMIT/60;    // TIME_LIMIT �� 60*30 �Ƃ��Đݒ�
    frame_count = 0;                // �t���[���J�E���g�����Z�b�g
}

void timer_deinit() {
    
}

void timer_update() {
    
    frame_count++;

    // 60�t���[�����Ƃ�1�b���炷
    if (frame_count >= 60) {
        remaining_time--;   // �c�莞�Ԃ�1�b����
        frame_count = 0;    // �t���[���J�E���g�����Z�b�g
    }

    // �c�莞�Ԃ�1�ȉ��ɂȂ�����^�C�}�[��~���A���U���g��ʂ�
    if (remaining_time < 1) {
        remaining_time = 1;
        game_end();
    }
}

void timer_render() {
    // �c�莞�Ԃ�1�b�ȏ�̏ꍇ�̂ݕ\��
    if (remaining_time >= 1) {
        string time_text = "TIME: " + to_string(remaining_time);
        text_out(1, time_text.c_str(), 0, 0, 2, 2, 1, 1, 1, 1);  // ���W (0, 0) �Ƀe�L�X�g�`��
    }
}
