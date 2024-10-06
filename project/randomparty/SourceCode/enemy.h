#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MAX (10)

class ENEMY {
private:
public:
	int type;
	float angle;
	float speed;
	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

};
void enemy_init();
void enemy_deinit();
void enemy_update();
void enemy_render();
void enemy_act();

#endif//ENEMY_H

