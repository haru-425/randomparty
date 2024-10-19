#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_TEX_W        (440.0f)   
#define BUTTON_TEX_H        (440.0f)   
#define BUTTON_PIVOT_X      (BUTTON_TEX_W/2)   
#define BUTTON_PIVOT_Y      (BUTTON_TEX_H/2)   

#define END_TEX_W           (128.0f)
#define END_TEX_H           (64.0f)
#define END_PIVOT_X         (END_TEX_W/2)
#define END_PIVOT_Y         (END_TEX_H/2)

#define HELP_TEX_W           (440.0f)
#define HELP_TEX_H           (440.0)
#define HELP_PIVOT_X         (HELP_TEX_W/2)
#define HELP_PIVOT_Y         (HELP_TEX_H/2)

#define SET_TEX_W           (440.0f)
#define SET_TEX_H           (440.0)
#define SET_PIVOT_X         (HELP_TEX_W/2)
#define SET_PIVOT_Y         (HELP_TEX_H/2)

class Button {
public:

	float  radius;

	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

	void button_init();
	void button_deinit();
	void button_update();
	void button_render();
	void button_act();
	bool click();

	void end_button_init();
	void end_button_deinit();
	void end_button_update();
	void end_button_render();
	void end_button_act();
	bool end_click();
	
	void help_button_init();
	void help_button_deinit();
	void help_button_update();
	void help_button_render();
	void help_button_act();
	bool help_click();

	void set_button_init();
	void set_button_deinit();
	void set_button_update();
	void set_button_render();
	void set_button_act();
	bool set_click();

	void next_button_init();
	void back_button_init();
	void tuto_player_button_init();
	void tyto_enemy_button_init();
	void descript_score_button_init();
	bool rect_click(Button button_info);

};

#endif//BUTTON_H
