#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
	float x, y, radius;
	bool click;

	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
};



void button_init();
void button_deinit();
void button_update();
void button_render();


#endif//BUTTON_H
