#include "all.h"
using namespace input;

int     player_state;

PLAYER player;

Sprite* sprPlayer;
Sprite* sprPlayerCore;

POINT point;
POINT screenPoint;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
	player_state = 0;
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
	safe_delete(sprPlayer);
	safe_delete(sprPlayerCore);
}
//

//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
	switch (player_state)
	{
	case 0:
		//////// �����ݒ� ////////
		sprPlayer = sprite_load(L"./Data/Images/player.png");
		sprPlayerCore = sprite_load(L"./Data/Images/playerCore.png");


		++player_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////
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
		//////// �ʏ펞 ////////
		if (TRG(0) & R_CLICK) 
		{
			bomb_set();
		}
		// �s���̑J��
		player_act();


		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`��
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
//  �v���C���[�̍s���̑J��
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

