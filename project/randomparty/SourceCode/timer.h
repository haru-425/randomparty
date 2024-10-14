#ifndef TIMER_H
#define TIMER_H

#define TIME_LIMIT  (60*180)


class TIMER {
public:
	
	int remaining_time;  // 残り時間
	int frame_count;     // フレームカウント
	
	
};

	void timer_init();
	void timer_deinit();
	void timer_update();
	void timer_render();
	

#endif//TIMER_H
