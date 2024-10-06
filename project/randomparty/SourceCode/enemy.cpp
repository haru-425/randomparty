#include"all.h"

int enemy_state;
extern PLAYER player;
typedef enum
{
	APPROACH_SLOW,
	APPROACH_FAST,

}ENEMY_TYPE;
ENEMY enemy[ENEMY_MAX];

Sprite* sprEnemy;
Sprite* sprEnemyCore;
void enemy_init() {
	enemy_state = 0;
}

void enemy_deinit() {
	safe_delete(sprEnemy);
	safe_delete(sprEnemyCore);
}

void enemy_update() {

	switch (enemy_state)
	{
	case 0:
		//////// 初期設定 ////////
		sprEnemy = sprite_load(L"./Data/Images/enemy_approach_slow.png");
		sprEnemyCore = sprite_load(L"./Data/Images/enemyCore.png");
		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		for (int i = 0; i < ENEMY_MAX; i++) {
			enemy[i].angle = ToRadian(0);
			enemy[i].position = { static_cast<float>(rand() % SCREEN_W),static_cast<float>(rand() % SCREEN_H) };
			enemy[i].scale = {0.1f, 0.1f};
			enemy[i].texPos = {0, 0};
			enemy[i].texSize = {ENEMY_TEX_W, ENEMY_TEX_H};
			enemy[i].pivot = {ENEMY_PIVOT_X, ENEMY_PIVOT_Y};
			enemy[i].color = {1.000f, 1.0f, 1.0f, 1.0f};

		}
		

		++enemy_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		enemy_act();


		break;
	}
}

void enemy_render() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		sprite_render(
			sprEnemy,
			enemy[i].position.x, enemy[i].position.y,
			enemy[i].scale.x, enemy[i].scale.y,
			enemy[i].texPos.x, enemy[i].texPos.y,
			enemy[i].texSize.x, enemy[i].texSize.y,
			enemy[i].pivot.x, enemy[i].pivot.y,
			enemy[i].angle,
			enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w
		);

		sprite_render(
			sprEnemyCore,
			enemy[i].position.x, enemy[i].position.y,
			enemy[i].scale.x, enemy[i].scale.y,
			enemy[i].texPos.x, enemy[i].texPos.y,
			ENEMY_CORE_TEX_W, ENEMY_CORE_TEX_H,
			ENEMY_CORE_PIVOT_X, ENEMY_CORE_PIVOT_Y,
			enemy[i].angle,
			enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w
		);

	}
	

}

void enemy_act() {
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		VECTOR2 subVector;
		subVector.x = player.position.x - enemy[i].position.x;
		subVector.y = player.position.y - enemy[i].position.y;

		enemy[i].angle = (float)atan2(subVector.y, subVector.x);
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (enemy[i].type)
		{
		case APPROACH_SLOW:
			break;
		case APPROACH_FAST:
			break;
		}
	}


}