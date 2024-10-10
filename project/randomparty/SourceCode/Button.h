#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_TEX_W        (440.0f)   
#define BUTTON_TEX_H        (440.0f)   
#define BUTTON_PIVOT_X      (ENEMY_TEX_W/2)   
#define BUTTON_PIVOT_Y      (ENEMY_TEX_H/2)   

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

};





#endif//BUTTON_H
