#include "all.h"

BombInfo bomb_def;
BombInfo stage[BOMB_MAX];


BombInfo normal = { 0,1,3.0,5,true };


extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];
void bomb_init() // 初期化
{
    bomb_def.bomb_number = 0;             // 爆弾番号を 0 に設定（未使用状態）
    bomb_def.bomb_playerattack = false;   // プレイヤーによる攻撃ではない
    bomb_def.bomb_range = 0;              // 爆風の範囲を 0 に設定
    bomb_def.bomb_time = -1;              // タイマーを未設定にする (-1)
    bomb_def.bomb_type = 0;               // 爆弾の種類を 0 に設定
    bomb_def.bomb_position.x = -200;      // 爆弾の位置を初期化 (x = -200)
    bomb_def.bomb_position.y = -200;      // 爆弾の位置を初期化 (y = -200)

    // BOMB_MAX 個の爆弾ステージの初期化（すべてデフォルト値に設定）
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def;
    }
}

void bomb_set()
{
	// BOMB_MAX 個のスロットから空いている場所を探す
	for (int i = 0; i < BOMB_MAX; i++)
	{
		if (bomb_def.bomb_number == 0) // 使われていないスロットを発見
		{
			stage[i] = normal; // 新しい爆弾（normal）を設定
			stage[i].bomb_number = i + 1; // 爆弾番号を設定
			bomb_def.bomb_position = player.position; // 爆弾の位置をプレイヤーの現在位置に設定
		}
	}
}

void bomb_update() // 爆発までのタイマー処理
{
    // すべての爆弾をチェック
    for (int i = 0; i < BOMB_MAX; i++)
    {
        if (bomb_def.bomb_number != 0) // 使われている爆弾のみ処理
        {
            stage[i].bomb_time -= 1; // タイマーをデクリメント
            if (stage[i].bomb_time == 0) // タイマーが 0 になったら
            {
                bomb_explosion(i); // 爆発処理を呼び出す
            }
        }
    }
}

void bomb_explosion(int bomb_number) // 爆弾の爆発処理
{
    int waitTime = 1; // 敵がリポップするまでの待機時間を設定
    float enemy_r = ENEMY_CORE_TEX_W * enemy[0].scale.x / 2; // 敵の半径を計算

    // すべての敵に対してヒット判定を行う
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        // 爆弾の爆発範囲と敵の位置が重なっているかをチェック
        if (circle_hit(stage[bomb_number].bomb_position, enemy->position, stage[bomb_number].bomb_range, enemy_r))
        {
            // 敵のリセット（リポップ処理）
            enemy[i].reset();
            enemy[i].waitNum = waitTime; // リポップまでの待機時間を設定
            waitTime++; // 次の敵の待機時間を増加

            // ここでスコア追加処理などを行う（スコア処理は別途実装）
        }
    }
    stage[bomb_number] = bomb_def;

}

void bomb_render()
{
    for (int i = 0; i < BOMB_MAX; i++)
    {
        //sprite_render();
    }
}


void bomb_deinit()
{
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def;
    }
}
