#pragma once // 二重インクルードを防ぐためのディレクティブ
#include <math.h>
#include "all.h" // 必要なヘッダファイルをインクルード

// 敵を倒した際に加算されるポイントの定義
#define ENEMY_KILL_POINT 50

// 外部で定義されているプレイヤーと敵の変数を使用するために宣言
extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];

// スコアを管理するクラス定義
class SCORE
{
private:
	int total_score;  // 総合スコアを保存する変数
	int enemy_kill;   // 倒した敵の数をカウントする変数
	int near_total;   // 近距離スコアを保存する変数

public:
	int time; // ゲーム内の時間を記録する変数
	// コンストラクタ: 初期化時にスコアや倒した敵の数などを0に設定
	SCORE() :total_score(0), enemy_kill(0), near_total(0) {}

	// デストラクタ: リソース解放などの処理（ここでは特に必要なし）
	~SCORE() {}

	// 距離計算に使う変数: 初期値は非常に大きな数と0を設定
	float distance[2] = { 1000000,0 }, dx, dy;

	// プレイヤーと敵の距離に応じてスコアを加算する関数（実装は別途行う）
	void near_score();

	// 敵を倒した時にスコアを加算する関数
	void enemy_kill_point();

	// 総合スコアを取得する関数
	int score_get()
	{
		return total_score;
	}

	// 倒した敵の数を取得する関数
	int kill_score_get()
	{
		return enemy_kill;
	}

	// 近距離スコアを取得する関数
	int distance_score_get()
	{
		return near_total;
	}

	// スコアや敵の撃破数をリセットする関数
	void score_reset()
	{
		total_score = 0;  // 総合スコアをリセット
		enemy_kill = 0;   // 敵の撃破数をリセット
		near_total = 0;   // 近距離スコアをリセット
	}
};