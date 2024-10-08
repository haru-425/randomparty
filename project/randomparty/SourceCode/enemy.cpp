#include "all.h"
#include <math.h>
int enemy_state;
bool enemies_active = true; // 敵の出現を制御するフラグ
int enemy_timer;


ENEMY enemy[ENEMY_MAX];

Sprite* sprEnemy;
Sprite* sprEnemyCore;

void enemy_init() {
	enemy_state = 0;
	enemy_timer = 0;
}

void enemy_deinit() {
	safe_delete(sprEnemy);
	safe_delete(sprEnemyCore);
}

void enemy_update() {
	if (!enemies_active) return; // 敵がオフなら更新処理なし
	enemy_timer++;
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
			//enemy[i] = set_enemy(enemy[i]);
			enemy[i].reset();



			enemy[i].waitNum = i + 1;
		}

		++enemy_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		enemy_timer++;
		if (enemy_timer > ENEMY_SPAWN_RATE)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i].waitNum--;
				if (enemy[i].waitNum < 0)
				{

					enemy[i].waitNum = -1;
				}


				if (enemy[i].waitNum == 0) { enemy[i].set(); debug::setString("set"); enemy[i].waitNum--; }
			}
			enemy_timer = 0;
		}

		enemy_act();

		break;
	}
}

void enemy_render() {
	if (!enemies_active) return; // 敵がオフなら描画処理なし

	//TODO:00 索敵範囲描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		primitive::circle(enemy[i].position.x, enemy[i].position.y, enemy[i].trackingRange, 1, 1, ToRadian(0), 0, 1, 0);
		primitive::circle(enemy[i].position.x, enemy[i].position.y, enemy[i].trackingRange - 10, 1, 1, ToRadian(0), 0, 0, 0);
	}

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

		debug::setString("waitNum:%d", enemy[i].waitNum);
	}

	debug::setString("timer:%d", enemy_timer);
}

void enemy_act() {
	if (!enemies_active) return; // 敵がオフなら動作処理なし


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].waitNum <= 0)
		{

			float speedX, speedY;
			float DistanceX, DistanceY, DIstance;
			DistanceX = player.position.x - enemy[i].position.x;
			DistanceY = player.position.y - enemy[i].position.y;
			DIstance = sqrtf(DistanceX * DistanceX + DistanceY * DistanceY);


			if (DIstance <= enemy[i].trackingRange)//索敵範囲内かどうか
			{

				enemy[i].angle = tracking(player.position, enemy[i].position);
				switch (enemy[i].type)
				{
				case APPROACH_SLOW:
					// 遅い動きの敵の処理

					speedX = cosf(enemy[i].angle) * 1;
					speedY = sinf(enemy[i].angle) * 1;
					enemy[i].position.x += speedX * enemy[i].speed;
					enemy[i].position.y += speedY * enemy[i].speed;
					break;
				case APPROACH_FAST:
					// 速い動きの敵の処理
					speedX = cosf(enemy[i].angle) * 1;
					speedY = sinf(enemy[i].angle) * 1;
					enemy[i].position.x += speedX * enemy[i].speed;
					enemy[i].position.y += speedY * enemy[i].speed;
					break;
				}

			}
			else
			{
				enemy[i].angle += ToRadian(rand() % 7 - 3);
				speedX = cosf(enemy[i].angle) * 1;
				speedY = sinf(enemy[i].angle) * 1;
				enemy[i].position.x += speedX * enemy[i].speed * 0.5f;
				enemy[i].position.y += speedY * enemy[i].speed * 0.5f;
			}

			if (enemy[i].position.x < 0 || enemy[i].position.x>SCREEN_W)
			{
				speedX *= -1;
				enemy[i].angle = (float)atan2(speedY, speedX);
			}
			if (enemy[i].position.y < 0 || enemy[i].position.y>SCREEN_H)
			{
				speedY *= -1;
				enemy[i].angle = (float)atan2(speedY, speedX);
			}
		}
	}
}

