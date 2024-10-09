#include "all.h"
using namespace input;

int     player_state;

PLAYER player;

Sprite* sprPlayer;
Sprite* sprPlayerCore;

POINT point;
POINT screenPoint;

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
		player.scale = { 0.1f, 0.1f };
		player.texPos = { 0, 0 };
		player.texSize = { PLAYER_TEX_W, PLAYER_TEX_H };
		player.pivot = { PLAYER_PIVOT_X, PLAYER_PIVOT_Y };
		player.color = { 1.000f, 1.0f, 1.0f, 1.0f };

		++player_state;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////
		if (TRG(0) & R_CLICK) 
		{
			bomb_set();
		}
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

	ScreenToClient(window::getHwnd(), &point);

	VECTOR2 subVector;
	subVector.x = point.x - player.position.x;
	subVector.y = point.y - player.position.y;

	player.angle = (float)atan2(subVector.y, subVector.x);

	float speedX = cosf(player.angle) * 1;
	float speedY = sinf(player.angle) * 1;
	player.position.x += speedX * PLAYER_SPEED;
	player.position.y += speedY * PLAYER_SPEED;
}

