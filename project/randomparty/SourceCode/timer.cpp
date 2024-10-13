#include "all.h"

using namespace std;

TIMER timer;



void timer_init() {
    
    timer.remaining_time = TIME_LIMIT/60;    // TIME_LIMIT �� 60*180 �Ƃ��Đݒ�
    timer.frame_count = 0;                // �t���[���J�E���g�����Z�b�g
}

void timer_deinit() {
    
}

void timer_update() {
    
    timer.frame_count++;

    // 60�t���[�����Ƃ�1�b���炷
    if (timer.frame_count >= 60) {
        timer.remaining_time--;   // �c�莞�Ԃ�1�b����
        timer.frame_count = 0;    // �t���[���J�E���g�����Z�b�g
    }

    // �c�莞�Ԃ�1�ȉ��ɂȂ�����^�C�}�[��~���A���U���g��ʂ�
    if (timer.remaining_time < 1) {
        timer.remaining_time = 0;
        game_end();
    }
}

void timer_render() {
    // �c�莞�Ԃ�1�b�ȏ�̏ꍇ�̂ݕ\��
    if (timer.remaining_time >= 1) {
        string time_text = "TIME: " + to_string(timer.remaining_time);
        text_out(1, time_text.c_str(), 0, 0, 2, 2, 1, 1, 1, 1);  // ���W (0, 0) �Ƀe�L�X�g�`��
    }
}
