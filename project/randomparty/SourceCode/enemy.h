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

#define ENEMY_SPAWN_RATE		(1.5f*60.0f)
#define  SCALE					(0.13f)

extern PLAYER player;

typedef enum
{
	APPROACH_SLOW,
	APPROACH_FAST,
	CHARGE,
	REBOUND,

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

	ENEMY() {
		position = { -1000,-1000 };//画面外
		scale = { SCALE, SCALE };
		texPos = { ENEMY_TEX_W * type, 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		trackingRange = 0;
		speed = 0;
		timer = -1;
	}
	void reset() {
		position = { -1000,-1000 };//画面外
		scale = { SCALE, SCALE };
		texPos = { ENEMY_TEX_W * type, 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		trackingRange = 0;
		speed = 0;
		timer = -1;

	}

	void set() {
		float spawnAngle = float(rand() % 360);
		float Probability = float(rand() % 100);
		//type = rand() % 4;
		if (Probability < 32.5)
		{
			type = APPROACH_SLOW;
		}
		else 	if (Probability < 65)
		{
			type = APPROACH_FAST;
		}
		else 	if (Probability < 95)
		{
			type = CHARGE;
		}
		else 	if (Probability < 100)
		{
			type = REBOUND;
		}
		timer = 60 * 5;
		angle = ToRadian(rand() % 360);
		position = { cosf(spawnAngle) * SCREEN_W / 2 * 1.5f + SCREEN_W / 2 ,sinf(spawnAngle) * SCREEN_H / 2 * 1.5f + SCREEN_H / 2 };
		//position = { static_cast<float>(rand() % SCREEN_W), static_cast<float>(rand() % SCREEN_H) };
		scale = { SCALE, SCALE };
		texPos = { ENEMY_TEX_W * type, 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		state = 0;
		switch (type)
		{
		case APPROACH_SLOW:
			speed = 0.5f + float(rand() % 2);
			trackingRangeDiameter = 10;
			trackingRange = PLAYER_TEX_W * player.scale.x * trackingRangeDiameter;
			break;
		case APPROACH_FAST:
			speed = 2.0f + float(rand() % 2);
			trackingRangeDiameter = 8;
			trackingRange = PLAYER_TEX_W * player.scale.x * trackingRangeDiameter;
			break;
		case CHARGE:
			speed = 2.0f;
			trackingRangeDiameter = 10;
			trackingRange = PLAYER_TEX_W * player.scale.x * trackingRangeDiameter;
			break;
		case REBOUND:
			speed = 10.0f;
			trackingRangeDiameter = 1980;
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

