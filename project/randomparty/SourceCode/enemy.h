#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MAX (50)

#define ENEMY_TEX_W        (400.0f)   // “G‚Ì‰æ‘œ1‚Â‚Ì•
#define ENEMY_TEX_H        (400.0f)   // “G‚Ì‰æ‘œ1‚Â‚Ì‚‚³
#define ENEMY_PIVOT_X      (ENEMY_TEX_W/2)    // “G‚Ì‰¡•ûŒü‚Ì’†S
#define ENEMY_PIVOT_Y      (ENEMY_TEX_H/2)   // “G‚Ìc•ûŒü‚Ì‰º’[



#define ENEMY_CORE_TEX_W        (128.0f)   // “G‚Ì‰æ‘œ1‚Â‚Ì•
#define ENEMY_CORE_TEX_H        (128.0f)   // “G‚Ì‰æ‘œ1‚Â‚Ì‚‚³
#define ENEMY_CORE_PIVOT_X      (ENEMY_CORE_TEX_W/2)    // “G‚Ì‰¡•ûŒü‚Ì’†S
#define ENEMY_CORE_PIVOT_Y      (ENEMY_CORE_TEX_H/2)   // “G‚Ìc•ûŒü‚Ì‰º’[

class ENEMY {
private:
public:
	int type;
	float angle;
	float speed;
	float trackingRange;
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
ENEMY set_enemy(ENEMY enemy);


#endif//ENEMY_H

