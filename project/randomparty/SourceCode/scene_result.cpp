#include"all.h"

#include <sstream>
extern SCORE score;
extern Button EndButton;
extern int player_has_bomb;


extern Sprite* sprBG;
extern Sprite* sprOverley;
Sprite* sprScore;
Sprite* sprScore_c;

int DrawScoreState;
int result_state;
int result_timer;
RESULT r_score;
RESULT d_score;
int music_timer;


VECTOR2 scorePos;
int score_move_timer;
float score_angle;

void result_init()
{
	d_score.bomb = 0;
	d_score.kill = 0;
	d_score.Nearby = 0;
	d_score.result = 0;

	result_timer = 0;
	music_timer = 0;

	sprBG = sprite_load(L"./Data/Images/title_layer01.png");
	sprOverley = sprite_load(L"./Data/Images/title_layer02.png");
	sprScore = sprite_load(L"./Data/Images/result.png");

	sprScore_c = sprite_load(L"./Data/Images/result_score.png");

	DrawScoreState = 0;

	r_score.kill = score.kill_score_get() * ENEMY_KILL_POINT;
	int used_bomb = BOMB_MAX - player_has_bomb;

	r_score.bomb = used_bomb * ENEMY_KILL_POINT * 3 * -1;
	r_score.Nearby = score.distance_score_get();
	r_score.result = r_score.kill + r_score.bomb + r_score.Nearby;

	EndButton.end_button_init();

	music::play(BGM_RESULT, true);

	score_angle = 0;

}

void result_deinit()
{
	EndButton.end_button_deinit();
	safe_delete(sprBG);
	safe_delete(sprOverley);
	safe_delete(sprScore);
	safe_delete(sprScore_c);

	music::stop(BGM_RESULT);


}

void result_update()
{
	//result_end();
	EndButton.end_button_update();


	score_move_timer++;
	scorePos.x = cos(score_angle) * 20;
	scorePos.y = sin(4 * score_angle) * 10;
	score_angle += ToRadian(1);
	result_timer++;
}

void result_render()
{
	GameLib::clear(0.0, 0.0, 0.0);


	sprite_render(sprBG, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);

	sprite_render(sprOverley, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	ScoreDisplay();

	sprite_render(sprScore, SCREEN_W / 2, SCREEN_H / 2, 1, 1, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);
	//text_out(1, "“G‚ÌƒLƒ‹”F", SCREEN_W / 2, SCREEN_H * 2, 2, 2, 1, 1, 1, 0.5f, TEXT_ALIGN::MIDDLE_RIGHT);

	EndButton.end_button_render();


	sprite_render(sprScore_c, scorePos.x, scorePos.y, 1, 1, 0, 0, 1920, 1080, 0, 0);
	//sprite_render(sprScore_c, SCREEN_W / 2, SCREEN_H / 2, 0.5f, 0.5f, 0, 0, 1920, 1080, 1920 / 2, 1080 / 2);





	//debug::setString("r%d d%d", r_score.result, d_score.result);
	//debug::setString("state%d", DrawScoreState);
}


void ScoreDisplay() {
	using namespace input;
	music_timer++;
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
		if (music_timer % 10 == 0)
		{
			sound::play(XWB_SYSTEM, XWB_SYSTEM_RESULT);
		}
		if (TRG(0) & L_CLICK) {
			DrawScoreState++;
			d_score.kill = r_score.kill;
			music_timer = 0;
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
		if (music_timer % 10 == 0)
		{
			sound::play(XWB_SYSTEM, XWB_SYSTEM_RESULT);
		}
		if (TRG(0) & L_CLICK) {
			DrawScoreState++;
			d_score.bomb = r_score.bomb;
			music_timer = 0;
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
		if (music_timer % 10 == 0)
		{
			sound::play(XWB_SYSTEM, XWB_SYSTEM_RESULT);
		}
		if (TRG(0) & L_CLICK) {
			DrawScoreState++;
			d_score.Nearby = r_score.Nearby;
			music_timer = 0;
		}
		break;
	case 3:
		if (r_score.result == d_score.result || r_score.result < 0)
		{
			DrawScoreState++;

			break;
		}
		if (r_score.result >= 0)
		{

			if (d_score.result > r_score.result - 500)
			{

				d_score.result++;

			}
			else {

				d_score.result += ENEMY_KILL_POINT / 2;
			}
		}
		if (music_timer % 10 == 0)
		{
			sound::play(XWB_SYSTEM, XWB_SYSTEM_RESULT);
		}
		if (TRG(0) & L_CLICK) {

			d_score.result = r_score.result;
			music_timer = 0;
		}
		break;
	}




	GameLib::text_out(6, "kill:", SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(d_score.kill), SCREEN_W / 2, SCREEN_H / 10 * 2, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);

	GameLib::text_out(6, "bomb:", SCREEN_W / 2, SCREEN_H / 10 * 4, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(d_score.bomb), SCREEN_W / 2, SCREEN_H / 10 * 4, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);

	GameLib::text_out(6, "near by:", SCREEN_W / 2, SCREEN_H / 10 * 6, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(d_score.Nearby), SCREEN_W / 2, SCREEN_H / 10 * 6, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);


	GameLib::text_out(6, "result:", SCREEN_W / 2, SCREEN_H / 10 * 8, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(d_score.result), SCREEN_W / 2, SCREEN_H / 10 * 8, 2, 2, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);

}
