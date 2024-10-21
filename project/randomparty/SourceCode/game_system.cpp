#include "all.h"
using namespace input;

// �Q�[���̃V�X�e����Ԃ��Ǘ�����ϐ�
int system_state;
// �O���Œ�`���ꂽ�X�R�A�Ǘ��p�̍\����
extern SCORE score;

// �V�X�e���̏���������
void system_init()
{
	// �V�X�e���̏�����Ԃ�0�ɐݒ�
	system_state = 0;
}

// �V�X�e���̏I������
void system_deinit()
{
	// �����ł͓��ɉ����������s��Ȃ����A��Œǉ�����\��������
}

// �V�X�e���̍X�V����
void system_update()
{
	// �V�X�e���̏�Ԃɉ������������s��
	switch (system_state)
	{
	case 0:
		//////// �����ݒ� ////////
		// ������Ԃ��玟�̏�ԂɑJ��
		++system_state;
		/*fallthrough*/  // ���̃P�[�X�ɂ����̂܂ܐi��

	case 1:
		//////// �p�����[�^�̐ݒ� ////////
		// �K�v�ȃp�����[�^��ݒ肵�A���̏�ԂɑJ��
		++system_state;
		/*fallthrough*/  // ���̃P�[�X�ɂ����̂܂ܐi��

	case 2:
		//////// �ʏ펞 ////////
		// �ʏ�̃Q�[���i�s���̏������s��
		// �s���̑J�ڂ𐧌䂷��i���݂͉����s���Ă��Ȃ��j
		break;
	}
}

// �V�X�e���̕`�揈��
void system_render()
{
	// ���݂̂Ƃ���A�`�悷����e�͂Ȃ�
}

// �w�肳�ꂽ�^�[�Q�b�g��ǐՂ���p�x���v�Z����֐�
// target: �ǐՑΏۂ̍��W
// tracking_person: �ǐՂ���l���̍��W
// return: �ǐՂ��邽�߂̊p�x
float tracking(VECTOR2 target, VECTOR2 tracking_person) {
	VECTOR2 subVector;
	float angle;

	// �^�[�Q�b�g�ƒǐՎ҂̍��W�������v�Z
	subVector.x = target.x - tracking_person.x;
	subVector.y = target.y - tracking_person.y;

	// ��������p�x���v�Z
	angle = (float)atan2(subVector.y, subVector.x);
	return angle;
}

// 2�̉~�̏Փ˂𔻒肷��֐�
// pos1: �~1�̍��W
// pos2: �~2�̍��W
// r1: �~1�̔��a
// r2: �~2�̔��a
// return: �Փ˂��Ă��邩�ǂ����itrue: �Փ�, false: ��Փˁj
bool circle_hit(VECTOR2 pos1, VECTOR2 pos2, float r1, float r2)
{
	// 2�̉~�̒��S�Ԃ̋����̕������v�Z
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	float r = r1 + r2;

	// �����̕��������a�̘a�̕����ȉ��ł���ΏՓ˂��Ă���
	if (dx * dx + dy * dy <= r * r)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �Q�[���̊J�n����
void game_start()
{
	// �Q�[���V�[���ɑJ��
	nextScene = SCENE_GAME;
}

// �Q�[���̏I������
void game_end()
{
	// ���ʉ�ʃV�[���ɑJ��
	nextScene = SCENE_RESULT;
}

// ���ʉ�ʂ̏I������
void result_end()
{
	// �^�C�g����ʂɑJ��
	nextScene = SCENE_TITLE;

	// �X�R�A�����Z�b�g
	score.score_reset();

	// �S�Ă̓G�����Z�b�g
	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy[i].reset();
	}
}

// �w���v��ʂ̊J�n����
void help_start()
{
	// �w���v��ʂɑJ��
	nextScene = SCENE_HELP;
}
