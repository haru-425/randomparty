#ifndef TIMER_H
#define TIMER_H
//frame*second*minute
#define TIME_LIMIT  (60*60*1)


class TIMER {
public:

	int remaining_time;  // �c�莞��
	int frame_count;     // �t���[���J�E���g


};

void timer_init();
void timer_deinit();
void timer_update();
void timer_render();


#endif//TIMER_H
