#include "all.h"
#include <math.h>
int enemy_state;
bool enemies_active = true; // 敵の出現を制御するフラグ
int enemy_timer;


ENEMY enemy[ENEMY_MAX];

Sprite* sprEnemy;
Sprite* sprEnemyCore;
Sprite* sprTrackingRange;

void enemy_init() {
	enemy_state = 0;
	enemy_timer = 0;
}

void enemy_deinit() {
	safe_delete(sprEnemy);
	safe_delete(sprEnemyCore);

	safe_delete(sprTrackingRange);
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
		sprTrackingRange = sprite_load(L"./Data/Images/trackingRange.png");
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


				if (enemy[i].waitNum == 0) { enemy[i].set(); /*debug::setString("set")*/; enemy[i].waitNum--; }
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
	//for (int i = 0; i < ENEMY_MAX; i++) {
	//	//primitive::circle(enemy[i].position.x, enemy[i].position.y, enemy[i].trackingRange, 1, 1, ToRadian(0), 0, 1, 0);
	////	primitive::circle(enemy[i].position.x, enemy[i].position.y, enemy[i].trackingRange - 10, 1, 1, ToRadian(0), 0, 0, 0);

	//	sprite_render(
	//		sprTrackingRange,
	//		enemy[i].position.x, enemy[i].position.y,
	//		2 * enemy[i].scale.x * enemy[i].trackingRangeDiameter, 2 * enemy[i].scale.y * enemy[i].trackingRangeDiameter,
	//		//1, 1,
	//		enemy[i].texPos.x, enemy[i].texPos.y,
	//		enemy[i].texSize.x, enemy[i].texSize.y,
	//		enemy[i].pivot.x, enemy[i].pivot.y,
	//		0,
	//		enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, 0.3f

	//	);

	//	//debug::setString("trackingrange:%f", enemy[i].trackingRange * enemy[i].scale.x);
	//}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].waitNum <= 0)
		{

			if (enemy[i].position.x >= 0 && enemy[i].position.x <= SCREEN_W && enemy[i].position.y >= 0 && enemy[i].position.y <= SCREEN_H)
			{


				switch (enemy[i].type)
				{
				case REBOUND:
					for (int j = 0; j < 50; j++)
					{
						float posX, posY;
						posX = enemy[i].position.x + cosf(enemy[i].angle) * j * 25;
						posY = enemy[i].position.y + sinf(enemy[i].angle) * j * 25;
						if (posX < 0)
						{
							posX *= -1;
						}
						if (posY < 0)
						{
							posY *= -1;
						}
						if (posX > SCREEN_W)
						{
							posX = SCREEN_W - (posX - SCREEN_W);

							//posY -= posY - SCREEN_H;
							//posX *= -1;

						}
						if (posY > SCREEN_H)
						{

							posY = SCREEN_H - (posY - SCREEN_H);
						}

						primitive::circle(posX, posY, 5, 1, 1, ToRadian(0), 1, 1, 1, 0.3f);
					}

					break;
				}
			}
		}

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
			0, 0,
			ENEMY_CORE_TEX_W, ENEMY_CORE_TEX_H,
			ENEMY_CORE_PIVOT_X, ENEMY_CORE_PIVOT_Y,
			enemy[i].angle,
			enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w
		);

		//debug::setString("trackingrange:%f", enemy[i].trackingRange);
	}

	//debug::setString("timer:%d", enemy_timer);
}

void enemy_act() {
	if (!enemies_active) return; // 敵がオフなら動作処理なし


	for (int i = 0; i < ENEMY_MAX; i++) {

		//debug::setString("timer %d", enemy[i].timer);
		float speedX, speedY;

		if (enemy[i].waitNum <= 0)
		{

			float DistanceX, DistanceY, DIstance;
			DistanceX = player.position.x - enemy[i].position.x;
			DistanceY = player.position.y - enemy[i].position.y;
			DIstance = sqrtf(DistanceX * DistanceX + DistanceY * DistanceY);
			if (enemy[i].timer < 0)
			{
				if (DIstance <= enemy[i].trackingRange)//索敵範囲内かどうか
				{

					switch (enemy[i].type)
					{
					case APPROACH_SLOW:
						// 遅い動きの敵の処理

						enemy[i].angle = tracking(player.position, enemy[i].position);
						speedX = cosf(enemy[i].angle) * 1;
						speedY = sinf(enemy[i].angle) * 1;
						enemy[i].position.x += speedX * enemy[i].speed;
						enemy[i].position.y += speedY * enemy[i].speed;
						break;
					case APPROACH_FAST:
						// 速い動きの敵の処理

						enemy[i].angle = tracking(player.position, enemy[i].position);
						speedX = cosf(enemy[i].angle) * 1;
						speedY = sinf(enemy[i].angle) * 1;
						enemy[i].position.x += speedX * enemy[i].speed;
						enemy[i].position.y += speedY * enemy[i].speed;
						break;
					case CHARGE:

						if (DIstance <= enemy[i].trackingRange / 2)
						{
							if (enemy[i].state == 0)
								enemy[i].angle += ToRadian(float(-10 + rand() % 20));

							enemy[i].speed = 5;
							enemy[i].state = 1;

						}
						else
						{

							enemy[i].speed = 3;
							enemy[i].angle = tracking(player.position, enemy[i].position);

							enemy[i].state = 0;
						}

						speedX = cosf(enemy[i].angle) * 1;
						speedY = sinf(enemy[i].angle) * 1;
						enemy[i].position.x += speedX * enemy[i].speed;
						enemy[i].position.y += speedY * enemy[i].speed;

						break;
					case REBOUND:

						speedX = cosf(enemy[i].angle) * 1;
						speedY = sinf(enemy[i].angle) * 1;
						enemy[i].position.x += speedX * enemy[i].speed * 0.5f;
						enemy[i].position.y += speedY * enemy[i].speed * 0.5f;
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
					enemy[i].state = 0;
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
			else
			{

				enemy[i].angle = tracking(player.position, enemy[i].position);
				speedX = cosf(enemy[i].angle) * 1;
				speedY = sinf(enemy[i].angle) * 1;
				enemy[i].position.x += speedX * 2;
				enemy[i].position.y += speedY * 2;
				enemy[i].timer--;
				//debug::setString("oraoraoraoraoraoraoraora");
			}
		}


	}
}

