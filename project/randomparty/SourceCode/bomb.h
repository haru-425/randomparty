#pragma once // 二重インクルードを防ぐためのディレクティブ
#ifndef BOMB_H 
#define BOMB_H

#include "all.h"

// 爆弾の範囲スケールを定義（プレイヤーのテクスチャサイズとSCALEに基づいて計算）
#define BOMB_RANGE_SCALE ( PLAYER_TEX_W * SCALE)

// 爆弾の最大数を定義
#define BOMB_MAX 5

// 関数のプロトタイプ宣言
// これらは別のファイルで実装される爆弾の初期化、更新、描画などの処理関数
void bomb_init();        // 爆弾の初期化
void bomb_deinit();      // 爆弾のリセット
void bomb_set();         // プレイヤーが爆弾を設置する
void bomb_update();      // 爆弾の状態（タイマーなど）を更新
void bomb_explosion(int bomb_namber); // 爆弾の爆発処理
void bomb_render();      // 爆弾と爆風範囲の描画処理

// 爆弾に関する情報を保持するクラス
class BombInfo
{
public:
	int bomb_number;       // 爆弾の番号（ユニークな識別子）
	int bomb_type;         // 爆弾の種類（通常爆弾や特別な爆弾などを区別する）
	float bomb_range;      // 爆弾の爆風範囲
	int bomb_time;         // 爆発までの時間（タイマー）
	bool bomb_playerattack;// プレイヤーが仕掛けた爆弾かどうかを判別
	VECTOR2 bomb_position; // 爆弾の座標（位置情報）
	int bomb_explode_count;// 爆発カウント（時間経過のトラッキングに使用）
};

#endif // BOMB_H