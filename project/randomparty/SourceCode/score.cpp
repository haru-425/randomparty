#include <math.h>
#include "all.h"
using namespace std;

// SCORE �N���X�̃����o�֐�: �v���C���[�ƓG�̋����ɉ����ăX�R�A�����Z
void SCORE::near_score()
{
	time++; // �^�C���ϐ���1�������i�Q�[�����̌o�ߎ��Ԃ��Ǘ��j

	// ���ׂĂ̓G�ɑ΂��ăv���C���[�Ƃ̋������v�Z
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �v���C���[�ƓG��x���W��y���W�̍����v�Z
		dx = player.position.x - enemy[i].position.x;
		dy = player.position.y - enemy[i].position.y;

		// �v���C���[�ƓG�̋��������[�N���b�h�����Ōv�Z
		distance[1] = sqrt(dx * dx + dy * dy);

		// �v�Z��������������܂ł̍ŏ�������菬�����ꍇ�A�����V�����ŏ������Ƃ��ĕۑ�
		if (distance[1] < distance[0])
		{
			distance[0] = distance[1];
		}
	}

	// �v���C���[�ƓG�̍ŏ�������300��菬�����ꍇ�A�X�R�A�����Z
	if (300 - distance[0] > 0 && time % 10 == 0) // 10�t���[�����ƂɃX�R�A���Z���������s
	{
		// �����ɉ������X�R�A���v�Z���ĉ��Z�i300�����̋����ɑ΂��ăX�R�A�𑝉��j
		near_total += (300 - distance[0]) / 30;
		total_score += (300 - distance[0]) / 30;
	}

	//// ���݂̑����X�R�A���f�o�b�O���Ƃ��ďo��
	//debug::setString("%d", total_score);

	// ����̌v�Z�ɔ����čŏ���������ɑ傫�Ȓl�Ƀ��Z�b�g
	distance[0] = 1000000;
}

// SCORE �N���X�̃����o�֐�: �G��|�����ۂɃX�R�A�����Z
void SCORE::enemy_kill_point()
{
	enemy_kill++; // �|�����G�̐���1����
	total_score += ENEMY_KILL_POINT; // �G��|�����ۂɌ��߂�ꂽ�|�C���g�����Z
}