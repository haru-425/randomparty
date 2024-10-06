#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MAX (10)

class ENEMY {
private:
public:
	int type;
};
void enemy_init();
void enemy_deinit();
void enemy_update();
void enemy_render();
void enemy_act();

#endif//ENEMY_H

