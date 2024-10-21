#include "all.h"
using namespace input;

// プレイヤーの状態を管理する変数
int player_state;

// プレイヤーの情報を保持する構造体
PLAYER player;

// 敵情報の外部参照（別のファイルで定義されている）
extern ENEMY enemy[ENEMY_MAX];
// カウントダウン完了フラグの外部参照
extern bool countdownComplete;

// プレイヤーのスプライトを管理するポインタ
Sprite* sprPlayer;
Sprite* sprPlayerCore;

// マウスカーソルの位置を格納するPOINT構造体
POINT point;
POINT screenPoint;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
	// プレイヤーの状態を初期化
	player_state = 0;
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
	// プレイヤーのスプライトを安全に削除
	safe_delete(sprPlayer);
	safe_delete(sprPlayerCore);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
	switch (player_state)
	{
	case 0:
		//////// 初期設定 ////////
		// プレイヤーとコアのスプライトをロード
		sprPlayer = sprite_load(L"./Data/Images/player.png");
		sprPlayerCore = sprite_load(L"./Data/Images/playerCore.png");

		// 次の状態に遷移
		++player_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		// プレイヤーの初期位置、角度、スケール、色などを設定
		player.angle = ToRadian(0);
		player.position = { SCREEN_W / 2.0f, SCREEN_H / 2.0f };
		player.scale = { SCALE, SCALE };
		player.texPos = { 0, 0 };
		player.texSize = { PLAYER_TEX_W, PLAYER_TEX_H };
		player.pivot = { PLAYER_PIVOT_X, PLAYER_PIVOT_Y };
		player.color = { 1.000f, 1.0f, 1.0f, 1.0f };

		// 次の状態に遷移
		++player_state;
		/*fallthrough*/

	case 2:
		// ヘルプシーンでなく、カウントダウンが完了したら次の状態に遷移
		if (curScene != SCENE_HELP && countdownComplete == true)
		{
			player_state++;
		}
		// プレイヤーの行動を処理
		player_act();
		break;

	case 3:
		//////// 通常時 ////////
		// 右クリックが押されたら爆弾を設置
		if (TRG(0) & R_CLICK)
		{
			bomb_set();
		}
		// プレイヤーの行動を処理
		player_act();
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void player_render()
{
	// プレイヤーのスプライトを描画
	sprite_render(
		sprPlayer,
		player.position.x, player.position.y,
		player.scale.x, player.scale.y,
		player.texPos.x, player.texPos.y,
		player.texSize.x, player.texSize.y,
		player.pivot.x, player.pivot.y,
		player.angle,
		player.color.x, player.color.y, player.color.z, player.color.w
	);

	// プレイヤーコアのスプライトを描画
	sprite_render(
		sprPlayerCore,
		player.position.x, player.position.y,
		player.scale.x, player.scale.y,
		player.texPos.x, player.texPos.y,
		PLAYER_CORE_TEX_W, PLAYER_CORE_TEX_H,
		PLAYER_CORE_PIVOT_X, PLAYER_CORE_PIVOT_Y,
		player.angle,
		player.color.x, player.color.y, player.color.z, player.color.w
	);
}

//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void player_act()
{
	// マウスカーソルの現在位置を取得
	GetCursorPos(&point);

	// スクリーン座標をクライアント座標に変換
	ScreenToClient(window::getHwnd(), &point);

	// プレイヤーとマウスカーソルの位置差分を計算
	VECTOR2 subVector;
	subVector.x = point.x - player.position.x;
	subVector.y = point.y - player.position.y;

	// 差分からプレイヤーの向きを計算
	player.angle = (float)atan2(subVector.y, subVector.x);

	// プレイヤーの移動速度を計算
	float speedX = cosf(player.angle) * 1;
	float speedY = sinf(player.angle) * 1;

	// プレイヤーの位置を更新
	player.position.x += speedX * PLAYER_SPEED;
	player.position.y += speedY * PLAYER_SPEED;

	// 全ての敵に対して当たり判定をチェック
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// プレイヤーと敵の中心が衝突しているかを判定
		if (circle_hit(player.position, enemy[i].position, PLAYER_CORE_TEX_W * SCALE / 2, ENEMY_CORE_TEX_W * SCALE / 2)) {
			// 衝突した場合、死亡音を再生してゲーム終了処理を呼び出す
			sound::play(XWB_SYSTEM, XWB_SYSTEM_DEATH);
			game_end();
		}
	}
}
