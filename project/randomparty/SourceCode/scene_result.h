#ifndef SCENE_RESULT_H
#define SCENE_RESULT_H
class RESULT
{
private:


public:
	RESULT() {
		kill = 0;
		bomb = 0;
		Nearby = 0
			;
		result = 0;
	}
	int kill;
	int bomb;
	int Nearby;
	int result;
};

void result_init();
void result_deinit();
void result_update();
void result_render();
void ScoreDisplay();
#endif//SCENE_RESULT_H