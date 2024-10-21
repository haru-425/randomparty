#include "all.h"
using namespace input;

// ゲームのシステム状態を管理する変数
int system_state;
// 外部で定義されたスコア管理用の構造体
extern SCORE score;

// システムの初期化処理
void system_init()
{
	// システムの初期状態を0に設定
	system_state = 0;
}

// システムの終了処理
void system_deinit()
{
	// ここでは特に何も処理を行わないが、後で追加する可能性がある
}

// システムの更新処理
void system_update()
{
	// システムの状態に応じた処理を行う
	switch (system_state)
	{
	case 0:
		//////// 初期設定 ////////
		// 初期状態から次の状態に遷移
		++system_state;
		/*fallthrough*/  // 次のケースにもそのまま進む

	case 1:
		//////// パラメータの設定 ////////
		// 必要なパラメータを設定し、次の状態に遷移
		++system_state;
		/*fallthrough*/  // 次のケースにもそのまま進む

	case 2:
		//////// 通常時 ////////
		// 通常のゲーム進行中の処理を行う
		// 行動の遷移を制御する（現在は何も行っていない）
		break;
	}
}

// システムの描画処理
void system_render()
{
	// 現在のところ、描画する内容はない
}

// 指定されたターゲットを追跡する角度を計算する関数
// target: 追跡対象の座標
// tracking_person: 追跡する人物の座標
// return: 追跡するための角度
float tracking(VECTOR2 target, VECTOR2 tracking_person) {
	VECTOR2 subVector;
	float angle;

	// ターゲットと追跡者の座標差分を計算
	subVector.x = target.x - tracking_person.x;
	subVector.y = target.y - tracking_person.y;

	// 差分から角度を計算
	angle = (float)atan2(subVector.y, subVector.x);
	return angle;
}

// 2つの円の衝突を判定する関数
// pos1: 円1の座標
// pos2: 円2の座標
// r1: 円1の半径
// r2: 円2の半径
// return: 衝突しているかどうか（true: 衝突, false: 非衝突）
bool circle_hit(VECTOR2 pos1, VECTOR2 pos2, float r1, float r2)
{
	// 2つの円の中心間の距離の平方を計算
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	float r = r1 + r2;

	// 距離の平方が半径の和の平方以下であれば衝突している
	if (dx * dx + dy * dy <= r * r)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ゲームの開始処理
void game_start()
{
	// ゲームシーンに遷移
	nextScene = SCENE_GAME;
}

// ゲームの終了処理
void game_end()
{
	// 結果画面シーンに遷移
	nextScene = SCENE_RESULT;
}

// 結果画面の終了処理
void result_end()
{
	// タイトル画面に遷移
	nextScene = SCENE_TITLE;

	// スコアをリセット
	score.score_reset();

	// 全ての敵をリセット
	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy[i].reset();
	}
}

// ヘルプ画面の開始処理
void help_start()
{
	// ヘルプ画面に遷移
	nextScene = SCENE_HELP;
}
