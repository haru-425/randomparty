#include"all.h"

#include <sstream>
extern SCORE score;
extern int player_has_bomb;


extern Sprite* sprBG;
extern Sprite* sprOverley;
Sprite* sprScore;

int DrawScoreState;
int result_state;
int result_timer;
RESULT r_score;
RESULT d_score;
void result_init()
{
	result_timer = 0;

	sprBG = sprite_load(L"./Data/Images/title_layer01.png");
	sprOverley = sprite_load(L"./Data/Images/title_layer02.png");
	sprScore = sprite_load(L"./Data/Images/result.png");


	DrawScoreState = 0;

	r_score.kill = score.kill_score_get() * ENEMY_KILL_POINT;
	int used_bomb = BOMB_MAX - player_has_bomb;

	r_score.bomb = used_bomb * ENEMY_KILL_POINT * 3 * -1;
	r_score.Nearby = score.distance_score_get();
	r_score.result = r_score.kill + r_score.bomb + r_score.Nearby;

}

void result_deinit()
{

	safe_delete(sprBG);
	safe_delete(sprOverley);
	safe_delete(sprScore);
}

void result_update()
{
	result_end();

	result_timer++;
}

void result_render()
{
	GameLib::clear(0.0, 0.0, 0.0);

	//仮のEnterキー表示
	//text_out(1, "push enter key", SCREEN_W * 0.275, SCREEN_H * 0.7, 2, 2);
	sprite_render(sprBG, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);

	sprite_render(sprOverley, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	ScoreDisplay();

	sprite_render(sprScore, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	//text_out(1, "敵のキル数：", SCREEN_W / 2, SCREEN_H * 2, 2, 2, 1, 1, 1, 0.5f, TEXT_ALIGN::MIDDLE_RIGHT);

	debug::setString("r%d d%d", r_score.result, d_score.result);
	debug::setString("state%d", DrawScoreState);
}


void ScoreDisplay() {

	switch (DrawScoreState)
	{
	case 0:
		if (r_score.kill == d_score.kill)
		{
			DrawScoreState++;

			break;
		}
		if (d_score.kill > r_score.kill - 200)
		{
			d_score.kill++;
		}
		else {

			d_score.kill += ENEMY_KILL_POINT / 2;
		}
		break;
	case 1:
		if (r_score.bomb == d_score.bomb)
		{
			DrawScoreState++;

			break;
		}
		if (d_score.bomb < r_score.bomb + 200)
		{
			d_score.bomb--;
		}
		else {

			d_score.bomb -= ENEMY_KILL_POINT / 2;
		}
		break;
	case 2:
		if (r_score.Nearby == d_score.Nearby)
		{
			DrawScoreState++;

			break;
		}
		if (d_score.Nearby > r_score.Nearby - 200)
		{
			d_score.Nearby++;
		}
		else {

			d_score.Nearby += ENEMY_KILL_POINT / 2;
		}
		break;
	case 3:
		if (r_score.result == d_score.result)
		{
			DrawScoreState++;

			break;
		}
		if (r_score.result >= 0)
		{

			if (d_score.result > r_score.result - 500)
			{
				if (d_score.result > r_score.result - 200)
				{
					d_score.result++;
				}
				d_score.result += 13;
			}
			else {

				d_score.result += ENEMY_KILL_POINT / 2;
			}
		}

		break;
	}




	text_out(6, "kill:", SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	text_out(6, std::to_string(d_score.kill), SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);

	text_out(6, "bomb:", SCREEN_W / 2, SCREEN_H / 10 * 4, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	text_out(6, std::to_string(d_score.bomb), SCREEN_W / 2, SCREEN_H / 10 * 4, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);

	text_out(6, "near by:", SCREEN_W / 2, SCREEN_H / 10 * 6, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	text_out(6, std::to_string(d_score.Nearby), SCREEN_W / 2, SCREEN_H / 10 * 6, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);


	text_out(6, "result:", SCREEN_W / 2, SCREEN_H / 10 * 8, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	text_out(6, std::to_string(d_score.result), SCREEN_W / 2, SCREEN_H / 10 * 8, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
}
