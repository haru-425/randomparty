#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MAX (50)

#define ENEMY_TEX_W        (400.0f)   // 敵の画像1つの幅
#define ENEMY_TEX_H        (400.0f)   // 敵の画像1つの高さ
#define ENEMY_PIVOT_X      (ENEMY_TEX_W/2)    // 敵の横方向の中心
#define ENEMY_PIVOT_Y      (ENEMY_TEX_H/2)   // 敵の縦方向の下端



#define ENEMY_CORE_TEX_W        (128.0f)   // 敵の画像1つの幅
#define ENEMY_CORE_TEX_H        (128.0f)   // 敵の画像1つの高さ
#define ENEMY_CORE_PIVOT_X      (ENEMY_CORE_TEX_W/2)    // 敵の横方向の中心
#define ENEMY_CORE_PIVOT_Y      (ENEMY_CORE_TEX_H/2)   // 敵の縦方向の下端

#define ENEMY_SPAWN_RATE		(4*60.0f)


extern PLAYER player;

typedef enum
{
	APPROACH_SLOW,
	APPROACH_FAST,
	CHARGE,

} ENEMY_TYPE;

class ENEMY {
private:
public:
	int type;
	int timer;
	int waitNum;
	int state;

	int trackingRangeDiameter;
	float angle;
	float speed;
	float trackingRange;
	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

	void reset() {
		position = { -1000,-1000 };//画面外
		scale = { 0.1f, 0.1f };
		texPos = { ENEMY_TEX_W * type, 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		trackingRange = 0;
		speed = 0;

	}

	void set() {
		type = rand() % 3;

		angle = ToRadian(rand() % 360);
		position = { static_cast<float>(rand() % SCREEN_W), static_cast<float>(rand() % SCREEN_H) };
		scale = { 0.1f, 0.1f };
		texPos = { ENEMY_TEX_W * type, 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		state = 0;
		switch (type)
		{
		case APPROACH_SLOW:
			speed = 1.5f + float(rand() % 2);
			trackingRangeDiameter = 15;
			trackingRange = PLAYER_TEX_W * player.scale.x * trackingRangeDiameter;
			break;
		case APPROACH_FAST:
			speed = 3.0f + float(rand() % 2);
			trackingRangeDiameter = 8;
			trackingRange = PLAYER_TEX_W * player.scale.x * trackingRangeDiameter;
			break;
		case CHARGE:
			timer = 0;
			speed = 3.0f;
			trackingRangeDiameter = 15;
			trackingRange = PLAYER_TEX_W * player.scale.x * trackingRangeDiameter;
			break;
		}

	}


};
void enemy_init();
void enemy_deinit();
void enemy_update();
void enemy_render();
void enemy_act();


#endif//ENEMY_H

