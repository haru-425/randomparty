#include "all.h"

int     player_state;

PLAYER player;

Sprite* sprPlayer;
Sprite* sprPlayerCore;

POINT point;


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
		//player.scale = { 1.0f, 1.0f };
		player.scale = { 0.1f, 0.1f };
		player.texPos = { 0, 0 };
		player.texSize = { PLAYER_TEX_W, PLAYER_TEX_H };
		player.pivot = { PLAYER_PIVOT_X, PLAYER_PIVOT_Y };
		player.color = { 1.000f, 1.0f, 1.0f, 1.0f };

		++player_state;
		/*fallthrough*/

	case 2:
		//////// �ʏ펞 ////////

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

