#ifndef TIMER_H
#define TIMER_H

#define TIME_LIMIT  (60*180)


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
