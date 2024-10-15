#pragma once // ��d�C���N���[�h��h�����߂̃f�B���N�e�B�u
#ifndef BOMB_H 
#define BOMB_H

#include "all.h"

// ���e�͈̔̓X�P�[�����`�i�v���C���[�̃e�N�X�`���T�C�Y��SCALE�Ɋ�Â��Čv�Z�j
#define BOMB_RANGE_SCALE ( PLAYER_TEX_W * SCALE)

// ���e�̍ő吔���`
#define BOMB_MAX 5

// �֐��̃v���g�^�C�v�錾
// �����͕ʂ̃t�@�C���Ŏ�������锚�e�̏������A�X�V�A�`��Ȃǂ̏����֐�
void bomb_init();        // ���e�̏�����
void bomb_deinit();      // ���e�̃��Z�b�g
void bomb_set();         // �v���C���[�����e��ݒu����
void bomb_update();      // ���e�̏�ԁi�^�C�}�[�Ȃǁj���X�V
void bomb_explosion(int bomb_namber); // ���e�̔�������
void bomb_render();      // ���e�Ɣ����͈͂̕`�揈��

// ���e�Ɋւ������ێ�����N���X
class BombInfo
{
public:
	int bomb_number;       // ���e�̔ԍ��i���j�[�N�Ȏ��ʎq�j
	int bomb_type;         // ���e�̎�ށi�ʏ픚�e����ʂȔ��e�Ȃǂ���ʂ���j
	float bomb_range;      // ���e�̔����͈�
	int bomb_time;         // �����܂ł̎��ԁi�^�C�}�[�j
	bool bomb_playerattack;// �v���C���[���d�|�������e���ǂ����𔻕�
	VECTOR2 bomb_position; // ���e�̍��W�i�ʒu���j
	int bomb_explode_count;// �����J�E���g�i���Ԍo�߂̃g���b�L���O�Ɏg�p�j
};

#endif // BOMB_H