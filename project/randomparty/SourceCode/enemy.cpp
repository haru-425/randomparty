#include "all.h"
#include <math.h>

// 敵の状態を管理する変数
int enemy_state;
// 敵の出現を制御するフラグ。falseの場合、敵の更新や描画が行われない
bool enemies_active = true;
// 敵の出現を制御するタイマー
int enemy_timer;

// 敵の配列（最大数分の敵を管理）
ENEMY enemy[ENEMY_MAX];

// 敵のスプライトオブジェクト
Sprite* sprEnemy;          // 敵の見た目
Sprite* sprEnemyCore;      // 敵のコアの見た目
Sprite* sprTrackingRange;  // 索敵範囲の見た目

// 敵の初期化関数
void enemy_init() {
    enemy_state = 0;    // 敵の状態を初期化
    enemy_timer = 0;    // 敵のタイマーを初期化
}

// 敵の終了処理。メモリの解放など
void enemy_deinit() {
    safe_delete(sprEnemy);
    safe_delete(sprEnemyCore);
    safe_delete(sprTrackingRange);
}

// 敵の更新処理
void enemy_update() {
    // 敵が無効化されている場合、処理をスキップ
    if (!enemies_active) return;

    enemy_timer++;

    // 敵の状態に応じた処理
    switch (enemy_state) {
    case 0:
        // 初期設定: スプライトの読み込み
        sprEnemy = sprite_load(L"./Data/Images/enemy_approach_slow.png");
        sprEnemyCore = sprite_load(L"./Data/Images/enemyCore.png");
        sprTrackingRange = sprite_load(L"./Data/Images/trackingRange.png");
        ++enemy_state; // 次の状態に移行
        /*fallthrough*/

    case 1:
        // パラメータの設定: 敵をリセットし、待機番号を設定
        for (int i = 0; i < ENEMY_MAX; i++) {
            enemy[i].reset();
            enemy[i].waitNum = i + 1;  // 順番に待機するための番号
        }
        ++enemy_state; // 次の状態に移行
        /*fallthrough*/

    case 2:
        // 通常時の更新処理: 一定間隔で敵を生成
        enemy_timer++;
        if (enemy_timer > ENEMY_SPAWN_RATE) {
            for (int i = 0; i < ENEMY_MAX; i++) {
                enemy[i].waitNum--;
                if (enemy[i].waitNum < 0) {
                    enemy[i].waitNum = -1;
                }
                if (enemy[i].waitNum == 0) {
                    enemy[i].set();  // 敵をセット
                    enemy[i].waitNum--;
                }
            }
            enemy_timer = 0;  // タイマーをリセット
        }

        // 敵の動作処理
        enemy_act();
        break;
    }
}

// 敵の描画処理
void enemy_render() {
    // 敵が無効化されている場合、描画をスキップ
    if (!enemies_active) return;

    for (int i = 0; i < ENEMY_MAX; i++) {
        // 敵が待機状態でない場合、描画を行う
        if (enemy[i].waitNum <= 0) {
            // 画面内にいる場合にのみ描画
            if (enemy[i].position.x >= 0 && enemy[i].position.x <= SCREEN_W && enemy[i].position.y >= 0 && enemy[i].position.y <= SCREEN_H) {
                switch (enemy[i].type) {
                case REBOUND:
                    // 反射するタイプの敵の軌跡を描画
                    for (int j = 0; j < 50; j++) {
                        float posX, posY;
                        posX = enemy[i].position.x + cosf(enemy[i].angle) * j * 25;
                        posY = enemy[i].position.y + sinf(enemy[i].angle) * j * 25;

                        // 画面外に出た場合の処理
                        if (posX < 0) posX *= -1;
                        if (posY < 0) posY *= -1;
                        if (posX > SCREEN_W) posX = SCREEN_W - (posX - SCREEN_W);
                        if (posY > SCREEN_H) posY = SCREEN_H - (posY - SCREEN_H);

                        primitive::circle(posX, posY, 5, 1, 1, ToRadian(0), 1, 1, 1, 0.3f);
                    }
                    break;
                }
            }
        }

        // 敵本体とそのコアの描画
        sprite_render(sprEnemy, enemy[i].position.x, enemy[i].position.y, enemy[i].scale.x, enemy[i].scale.y, enemy[i].texPos.x, enemy[i].texPos.y, enemy[i].texSize.x, enemy[i].texSize.y, enemy[i].pivot.x, enemy[i].pivot.y, enemy[i].angle, enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w);
        sprite_render(sprEnemyCore, enemy[i].position.x, enemy[i].position.y, enemy[i].scale.x, enemy[i].scale.y, 0, 0, ENEMY_CORE_TEX_W, ENEMY_CORE_TEX_H, ENEMY_CORE_PIVOT_X, ENEMY_CORE_PIVOT_Y, enemy[i].angle, enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w);
    }
}

// 敵の行動処理
void enemy_act() {
    // 敵が無効化されている場合、動作処理をスキップ
    if (!enemies_active) return;

    for (int i = 0; i < ENEMY_MAX; i++) {
        float speedX, speedY;

        if (enemy[i].waitNum <= 0) {
            // プレイヤーとの距離を計算
            float DistanceX = player.position.x - enemy[i].position.x;
            float DistanceY = player.position.y - enemy[i].position.y;
            float Distance = sqrtf(DistanceX * DistanceX + DistanceY * DistanceY);

            // 敵のタイマーが0未満なら索敵範囲に基づいて行動
            if (enemy[i].timer < 0) {
                if (Distance <= enemy[i].trackingRange) {  // 索敵範囲内かどうか
                    switch (enemy[i].type) {
                    case APPROACH_SLOW:
                        // 遅い動きの敵
                        enemy[i].angle = tracking(player.position, enemy[i].position);
                        speedX = cosf(enemy[i].angle) * 1;
                        speedY = sinf(enemy[i].angle) * 1;
                        enemy[i].position.x += speedX * enemy[i].speed;
                        enemy[i].position.y += speedY * enemy[i].speed;
                        break;
                    case APPROACH_FAST:
                        // 速い動きの敵
                        enemy[i].angle = tracking(player.position, enemy[i].position);
                        speedX = cosf(enemy[i].angle) * 1;
                        speedY = sinf(enemy[i].angle) * 1;
                        enemy[i].position.x += speedX * enemy[i].speed;
                        enemy[i].position.y += speedY * enemy[i].speed;
                        break;
                    case CHARGE:
                        // 一定距離内に近づくとチャージ状態になる敵
                        if (Distance <= enemy[i].trackingRange / 2) {
                            if (enemy[i].state == 0)
                                enemy[i].angle += ToRadian(float(-10 + rand() % 20));  // 多少ランダムな動き
                            enemy[i].speed = 5;
                            enemy[i].state = 1;
                        }
                        else {
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
                        // 反射するタイプの敵
                        speedX = cosf(enemy[i].angle) * 1;
                        speedY = sinf(enemy[i].angle) * 1;
                        enemy[i].position.x += speedX * enemy[i].speed * 0.5f;
                        enemy[i].position.y += speedY * enemy[i].speed * 0.5f;
                        break;
                    }
                }
                else {
                    // 索敵範囲外の場合、ランダムな動きをする
                    enemy[i].angle += ToRadian(rand() % 7 - 3);
                    speedX = cosf(enemy[i].angle) * 1;
                    speedY = sinf(enemy[i].angle) * 1;
                    enemy[i].position.x += speedX * enemy[i].speed * 0.5f;
                    enemy[i].position.y += speedY * enemy[i].speed * 0.5f;
                    enemy[i].state = 0;
                }

                // 画面外に出た場合の反射処理
                if (enemy[i].position.x < 0 || enemy[i].position.x > SCREEN_W) {
                    speedX *= -1;
                    enemy[i].angle = (float)atan2(speedY, speedX);
                }
                if (enemy[i].position.y < 0 || enemy[i].position.y > SCREEN_H) {
                    speedY *= -1;
                    enemy[i].angle = (float)atan2(speedY, speedX);
                }
            }
            else {
                // 敵のタイマーが有効な場合、追跡行動を行う
                enemy[i].angle = tracking(player.position, enemy[i].position);
                speedX = cosf(enemy[i].angle) * 1;
                speedY = sinf(enemy[i].angle) * 1;
                enemy[i].position.x += speedX * 2;
                enemy[i].position.y += speedY * 2;
                enemy[i].timer--;
            }
        }
    }
}
