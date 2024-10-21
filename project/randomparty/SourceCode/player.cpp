#include "all.h"
using namespace input;

// �v���C���[�̏�Ԃ��Ǘ�����ϐ�
int player_state;

// �v���C���[�̏���ێ�����\����
PLAYER player;

// �G���̊O���Q�Ɓi�ʂ̃t�@�C���Œ�`����Ă���j
extern ENEMY enemy[ENEMY_MAX];
// �J�E���g�_�E�������t���O�̊O���Q��
extern bool countdownComplete;

// �v���C���[�̃X�v���C�g���Ǘ�����|�C���^
Sprite* sprPlayer;
Sprite* sprPlayerCore;

// �}�E�X�J�[�\���̈ʒu���i�[����POINT�\����
POINT point;
POINT screenPoint;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
	// �v���C���[�̏�Ԃ�������
	player_state = 0;
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
	// �v���C���[�̃X�v���C�g�����S�ɍ폜
	safe_delete(sprPlayer);
	safe_delete(sprPlayerCore);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
	switch (player_state)
	{
	case 0:
		//////// �����ݒ� ////////
		// �v���C���[�ƃR�A�̃X�v���C�g�����[�h
		sprPlayer = sprite_load(L"./Data/Images/player.png");
		sprPlayerCore = sprite_load(L"./Data/Images/playerCore.png");

		// ���̏�ԂɑJ��
		++player_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////
		// �v���C���[�̏����ʒu�A�p�x�A�X�P�[���A�F�Ȃǂ�ݒ�
		player.angle = ToRadian(0);
		player.position = { SCREEN_W / 2.0f, SCREEN_H / 2.0f };
		player.scale = { SCALE, SCALE };
		player.texPos = { 0, 0 };
		player.texSize = { PLAYER_TEX_W, PLAYER_TEX_H };
		player.pivot = { PLAYER_PIVOT_X, PLAYER_PIVOT_Y };
		player.color = { 1.000f, 1.0f, 1.0f, 1.0f };

		// ���̏�ԂɑJ��
		++player_state;
		/*fallthrough*/

	case 2:
		// �w���v�V�[���łȂ��A�J�E���g�_�E�������������玟�̏�ԂɑJ��
		if (curScene != SCENE_HELP && countdownComplete == true)
		{
			player_state++;
		}
		// �v���C���[�̍s��������
		player_act();
		break;

	case 3:
		//////// �ʏ펞 ////////
		// �E�N���b�N�������ꂽ�甚�e��ݒu
		if (TRG(0) & R_CLICK)
		{
			bomb_set();
		}
		// �v���C���[�̍s��������
		player_act();
		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`�揈��
//--------------------------------------
void player_render()
{
	// �v���C���[�̃X�v���C�g��`��
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

	// �v���C���[�R�A�̃X�v���C�g��`��
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
//  �v���C���[�̍s������
//--------------------------------------
void player_act()
{
	// �}�E�X�J�[�\���̌��݈ʒu���擾
	GetCursorPos(&point);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�
	ScreenToClient(window::getHwnd(), &point);

	// �v���C���[�ƃ}�E�X�J�[�\���̈ʒu�������v�Z
	VECTOR2 subVector;
	subVector.x = point.x - player.position.x;
	subVector.y = point.y - player.position.y;

	// ��������v���C���[�̌������v�Z
	player.angle = (float)atan2(subVector.y, subVector.x);

	// �v���C���[�̈ړ����x���v�Z
	float speedX = cosf(player.angle) * 1;
	float speedY = sinf(player.angle) * 1;

	// �v���C���[�̈ʒu���X�V
	player.position.x += speedX * PLAYER_SPEED;
	player.position.y += speedY * PLAYER_SPEED;

	// �S�Ă̓G�ɑ΂��ē����蔻����`�F�b�N
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �v���C���[�ƓG�̒��S���Փ˂��Ă��邩�𔻒�
		if (circle_hit(player.position, enemy[i].position, PLAYER_CORE_TEX_W * SCALE / 2, ENEMY_CORE_TEX_W * SCALE / 2)) {
			// �Փ˂����ꍇ�A���S�����Đ����ăQ�[���I���������Ăяo��
			sound::play(XWB_SYSTEM, XWB_SYSTEM_DEATH);
			game_end();
		}
	}
}
