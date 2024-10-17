#include <math.h>
#include "all.h"
using namespace std;

// SCORE クラスのメンバ関数: プレイヤーと敵の距離に応じてスコアを加算
void SCORE::near_score()
{
	time++; // タイム変数を1ずつ増加（ゲーム内の経過時間を管理）

	// すべての敵に対してプレイヤーとの距離を計算
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// プレイヤーと敵のx座標とy座標の差を計算
		dx = player.position.x - enemy[i].position.x;
		dy = player.position.y - enemy[i].position.y;

		// プレイヤーと敵の距離をユークリッド距離で計算
		distance[1] = sqrt(dx * dx + dy * dy);

		// 計算した距離がこれまでの最小距離より小さい場合、それを新しい最小距離として保存
		if (distance[1] < distance[0])
		{
			distance[0] = distance[1];
		}
	}

	// プレイヤーと敵の最小距離が300より小さい場合、スコアを加算
	if (300 - distance[0] > 0 && time % 10 == 0) // 10フレームごとにスコア加算処理を実行
	{
		// 距離に応じたスコアを計算して加算（300未満の距離に対してスコアを増加）
		near_total += (300 - distance[0]) / 30;
		total_score += (300 - distance[0]) / 30;
	}

	//// 現在の総合スコアをデバッグ情報として出力
	//debug::setString("%d", total_score);

	// 次回の計算に備えて最小距離を非常に大きな値にリセット
	distance[0] = 1000000;
}

// SCORE クラスのメンバ関数: 敵を倒した際にスコアを加算
void SCORE::enemy_kill_point()
{
	enemy_kill++; // 倒した敵の数を1増加
	total_score += ENEMY_KILL_POINT; // 敵を倒した際に決められたポイントを加算
}