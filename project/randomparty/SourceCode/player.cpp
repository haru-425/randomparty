#include "all.h"

int     player_state;

PLAYER player;

Sprite* sprPlayer;
Sprite* sprPlayerCore;

POINT point;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
	player_state = 0;
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
	safe_delete(sprPlayer);
	safe_delete(sprPlayerCore);
}
//

//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
	switch (player_state)
	{
	case 0:
		//////// 初期設定 ////////
		sprPlayer = sprite_load(L"./Data/Images/player.png");
		sprPlayerCore = sprite_load(L"./Data/Images/playerCore.png");


		++player_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		player.angle = ToRadian(0);
		player.position = { SCREEN_W / 2.0f, SCREEN_H / 2.0f };
		//player.scale = { 1.0f, 1.0f };
		player.scale = { 0.1f, 0.1f };
		player.texPos = { 0, 0 };
		player.texSize = { PLAYER_TEX_W, PLAYER_TEX_H };
		player.pivot = { PLAYER_PIVOT_X, PLAYER_PIVOT_Y };
		player.color = { 1.000f, 1.0f, 1.0f, 1.0f };

		++player_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////

		// 行動の遷移
		player_act();


		break;
	}
}

//--------------------------------------
//  プレイヤーの描画
//--------------------------------------
void player_render()
{

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
//  プレイヤーの行動の遷移
//--------------------------------------
void player_act()
{

	GetCursorPos(&point);
	//↓これが必要臭いけど、window_handleの所に入れる変数が見当たらない
	/*マウス座標の取得方法が異なる
	マウス座標は GetCursorPos を使用して取得していますが、この関数が返す座標は スクリーン座標系(モニター全体の座標) です。
	ゲームで通常使用される座標系は ウィンドウ座標系 なので、これを直接使うとズレが生じます。
	対策
	ウィンドウ内の座標に変換するためには、ScreenToClient 関数を使用して、マウスのスクリーン座標をウィンドウ座標に変換する必要があります。
	window_handle は、ゲームウィンドウのハンドルを渡します（通常は、ウィンドウを作成したときに取得しているはずです）。

	座標系が一致していない
	取得したマウス座標とプレイヤーの座標が同じ基準でない場合、向きや位置がずれる可能性があります。
	たとえば、ウィンドウの左上が(0, 0)の座標系なのか、中心が(0, 0)の座標系なのかで変わってきます。
	もし画面中央を基準にしているなら、その調整が必要です。 */
	//// マウスのスクリーン座標をウィンドウ座標に変換
 //   GetCursorPos(&point);
 //   ScreenToClient(window_handle, &point);  // window_handleを正しいウィンドウハンドルに置き換える
	VECTOR2 subVector;
	//subVector.x = player.position.x - point.x;
	subVector.x = point.x - player.position.x;
	//subVector.x = player.position.x;
	//subVector.y = player.position.y - point.x;
	subVector.y = point.y - player.position.y;
	//subVector.y = player.position.y;

	//subVector.x = 1.0f / subVector.x;
	//subVector.y = 1.0f / subVector.y;

	player.angle = (float)atan2(subVector.y, subVector.x) + ToRadian(180);

	float speedX = cosf(-player.angle) /** 40.0f*/ * -1;
	float speedY = sinf(-player.angle) /** 40.0f */ * 1;
	player.position.x += speedX * 10;
	//player.position.x = point.x;
	player.position.y += speedY * 10;
	//player.position.y = point.y;
}

