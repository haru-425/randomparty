#pragma once // ��d�C���N���[�h��h�����߂̃f�B���N�e�B�u
#include <math.h>
#include "all.h" // �K�v�ȃw�b�_�t�@�C�����C���N���[�h

// �G��|�����ۂɉ��Z�����|�C���g�̒�`
#define ENEMY_KILL_POINT 50

// �O���Œ�`����Ă���v���C���[�ƓG�̕ϐ����g�p���邽�߂ɐ錾
extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];

// �X�R�A���Ǘ�����N���X��`
class SCORE
{
private:
	int total_score;  // �����X�R�A��ۑ�����ϐ�
	int enemy_kill;   // �|�����G�̐����J�E���g����ϐ�
	int near_total;   // �ߋ����X�R�A��ۑ�����ϐ�

public:
	int time; // �Q�[�����̎��Ԃ��L�^����ϐ�
	// �R���X�g���N�^: ���������ɃX�R�A��|�����G�̐��Ȃǂ�0�ɐݒ�
	SCORE() :total_score(0), enemy_kill(0), near_total(0) {}

	// �f�X�g���N�^: ���\�[�X����Ȃǂ̏����i�����ł͓��ɕK�v�Ȃ��j
	~SCORE() {}

	// �����v�Z�Ɏg���ϐ�: �����l�͔��ɑ傫�Ȑ���0��ݒ�
	float distance[2] = { 1000000,0 }, dx, dy;

	// �v���C���[�ƓG�̋����ɉ����ăX�R�A�����Z����֐��i�����͕ʓr�s���j
	void near_score();

	// �G��|�������ɃX�R�A�����Z����֐�
	void enemy_kill_point();

	// �����X�R�A���擾����֐�
	int score_get()
	{
		return total_score;
	}

	// �|�����G�̐����擾����֐�
	int kill_score_get()
	{
		return enemy_kill;
	}

	// �ߋ����X�R�A���擾����֐�
	int distance_score_get()
	{
		return near_total;
	}

	// �X�R�A��G�̌��j�������Z�b�g����֐�
	void score_reset()
	{
		total_score = 0;  // �����X�R�A�����Z�b�g
		enemy_kill = 0;   // �G�̌��j�������Z�b�g
		near_total = 0;   // �ߋ����X�R�A�����Z�b�g
	}
};