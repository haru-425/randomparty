#include "all.h"

BombInfo bomb_def;
BombInfo stage[BOMB_MAX];


BombInfo normal = { 0,1,3.0,5,true };


extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];
void bomb_init() // ������
{
    bomb_def.bomb_number = 0;             // ���e�ԍ��� 0 �ɐݒ�i���g�p��ԁj
    bomb_def.bomb_playerattack = false;   // �v���C���[�ɂ��U���ł͂Ȃ�
    bomb_def.bomb_range = 0;              // �����͈̔͂� 0 �ɐݒ�
    bomb_def.bomb_time = -1;              // �^�C�}�[�𖢐ݒ�ɂ��� (-1)
    bomb_def.bomb_type = 0;               // ���e�̎�ނ� 0 �ɐݒ�
    bomb_def.bomb_position.x = -200;      // ���e�̈ʒu�������� (x = -200)
    bomb_def.bomb_position.y = -200;      // ���e�̈ʒu�������� (y = -200)

    // BOMB_MAX �̔��e�X�e�[�W�̏������i���ׂăf�t�H���g�l�ɐݒ�j
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def;
    }
}

void bomb_set()
{
	// BOMB_MAX �̃X���b�g����󂢂Ă���ꏊ��T��
	for (int i = 0; i < BOMB_MAX; i++)
	{
		if (bomb_def.bomb_number == 0) // �g���Ă��Ȃ��X���b�g�𔭌�
		{
			stage[i] = normal; // �V�������e�inormal�j��ݒ�
			stage[i].bomb_number = i + 1; // ���e�ԍ���ݒ�
			bomb_def.bomb_position = player.position; // ���e�̈ʒu���v���C���[�̌��݈ʒu�ɐݒ�
		}
	}
}

void bomb_update() // �����܂ł̃^�C�}�[����
{
    // ���ׂĂ̔��e���`�F�b�N
    for (int i = 0; i < BOMB_MAX; i++)
    {
        if (bomb_def.bomb_number != 0) // �g���Ă��锚�e�̂ݏ���
        {
            stage[i].bomb_time -= 1; // �^�C�}�[���f�N�������g
            if (stage[i].bomb_time == 0) // �^�C�}�[�� 0 �ɂȂ�����
            {
                bomb_explosion(i); // �����������Ăяo��
            }
        }
    }
}

void bomb_explosion(int bomb_number) // ���e�̔�������
{
    int waitTime = 1; // �G�����|�b�v����܂ł̑ҋ@���Ԃ�ݒ�
    float enemy_r = ENEMY_CORE_TEX_W * enemy[0].scale.x / 2; // �G�̔��a���v�Z

    // ���ׂĂ̓G�ɑ΂��ăq�b�g������s��
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        // ���e�̔����͈͂ƓG�̈ʒu���d�Ȃ��Ă��邩���`�F�b�N
        if (circle_hit(stage[bomb_number].bomb_position, enemy->position, stage[bomb_number].bomb_range, enemy_r))
        {
            // �G�̃��Z�b�g�i���|�b�v�����j
            enemy[i].reset();
            enemy[i].waitNum = waitTime; // ���|�b�v�܂ł̑ҋ@���Ԃ�ݒ�
            waitTime++; // ���̓G�̑ҋ@���Ԃ𑝉�

            // �����ŃX�R�A�ǉ������Ȃǂ��s���i�X�R�A�����͕ʓr�����j
        }
    }
    stage[bomb_number] = bomb_def;

}

void bomb_render()
{
    for (int i = 0; i < BOMB_MAX; i++)
    {
        //sprite_render();
    }
}


void bomb_deinit()
{
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def;
    }
}
