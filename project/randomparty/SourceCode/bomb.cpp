#include "all.h"

// ���e�̏���ێ�����\����
BombInfo bomb_def;         // �f�t�H���g�̔��e���
BombInfo stage[BOMB_MAX];  // �e�X�e�[�W�ɑ��݂��锚�e����ێ�
int player_has_bomb;       // �v���C���[�������Ă��锚�e�̐�

// �ʏ�̔��e�̒�`�i���e�ԍ��A�v���C���[�U���t���O�A�����͈́A���ԁA���e�̗L�����j
BombInfo normal = { 0, 1, 3.0, 2, true };

// �X�v���C�g�i���e�̉摜�A�͈͂̉摜�j
Sprite* range_circl;   // �����͈͂̃X�v���C�g
Sprite* bomb;          // ���e�̃X�v���C�g

// �O���ϐ��̐錾�i�v���C���[�A�G�A�X�R�A�j
extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];
extern SCORE score;

float remainingAlpha;  // �X�v���C�g�̓����x���Ǘ����邽�߂̕ϐ�
extern POINT point;    // �O���Œ�`���ꂽ���W��ێ�����POINT�\����

// ���e�̏���������
void bomb_init()
{
    // �f�t�H���g�̔��e����ݒ�
    bomb_def.bomb_number = 0;             // ���e�ԍ��� 0 �ɐݒ�i���g�p��ԁj
    bomb_def.bomb_playerattack = false;   // �v���C���[�ɂ��U���ł͂Ȃ�
    bomb_def.bomb_range = 0;              // �����͈̔͂� 0 �ɐݒ�
    bomb_def.bomb_time = -1;              // �^�C�}�[�𖢐ݒ�ɂ��� (-1)
    bomb_def.bomb_type = 0;               // ���e�̎�ނ� 0 �ɐݒ�
    bomb_def.bomb_position.x = -200;      // ���e�̈ʒu�������� (x = -200)
    bomb_def.bomb_position.y = -200;      // ���e�̈ʒu�������� (y = -200)
    bomb_def.bomb_explode_count = 0;      // �����J�E���g�� 0 �ɐݒ�

    // BOMB_MAX �̔��e�X�e�[�W�̏������i���ׂăf�t�H���g�l�ɐݒ�j
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def; // �e���e���f�t�H���g�̐ݒ�ɂ���
    }

    // �X�v���C�g�̓ǂݍ���
    range_circl = sprite_load(L"./Data/Images/trackingRange.png");  // �����͈͂̃X�v���C�g
    bomb = sprite_load(L"./Data/Images/bomb.png");                 // ���e�X�v���C�g
    player_has_bomb = BOMB_MAX; // �v���C���[�������Ă��锚�e�̍ő吔��ݒ�
}

// �v���C���[�����e��ݒu���鏈��
void bomb_set()
{
    if (player_has_bomb > 0) // �v���C���[�����e�������Ă��邩���m�F
    {
        // BOMB_MAX �̃X���b�g����󂢂Ă���ꏊ��T��
        for (int i = 0; i < BOMB_MAX; i++)
        {
            if (stage[i].bomb_number == 0) // �g���Ă��Ȃ��X���b�g�𔭌�
            {
                stage[i] = normal;                  // �V�������e�inormal�j��ݒ�
                stage[i].bomb_number = i + 1;       // ���e�ԍ���ݒ�
                stage[i].bomb_position = player.position; // ���e�̈ʒu���v���C���[�̌��݈ʒu�ɐݒ�
                break;
            }
        }
        player_has_bomb--; // �v���C���[�̎����Ă��锚�e��������������

        sound::play(XWB_SYSTEM, XWB_SYSTEM_BOMB_SET); // ���e�ݒu�����Đ�
    }
    else
    {
        sound::play(XWB_SYSTEM, XWB_SYSTEM_BOMB_FAILURE); // ���e�ݒu���s�����Đ�
    }
}

// ���e�̃^�C�}�[���X�V���鏈��
void bomb_update()
{
    // ���ׂĂ̔��e���`�F�b�N
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i].bomb_explode_count++; // �����J�E���g���C���N�������g

        if (stage[i].bomb_number != 0) // �g���Ă��锚�e�̂ݏ���
        {
            if (stage[i].bomb_explode_count % 60 == 0) // 60�t���[�����Ƃ�
            {
                stage[i].bomb_time -= 1; // �^�C�}�[���f�N�������g
                if (stage[i].bomb_time == 0) // �^�C�}�[�� 0 �ɂȂ�����
                {
                    bomb_explosion(i); // �����������Ăяo��

                    sound::play(XWB_SYSTEM, XWB_SYSTEM_EXPLODE); // ���������Đ�
                }
            }
        }
    }

    // �v���C���[�̈ʒu�Ɋ�Â��ăX�v���C�g�̓����x��ݒ�
    if ((player.position.x - (SCREEN_W - 70)) * (player.position.x - (SCREEN_W - 70)) + (player.position.y - (SCREEN_H - 70)) * (player.position.y - (SCREEN_H - 70)) <= 200 * 200)
    {
        remainingAlpha = 0.5f; // �v���C���[���͈͓��Ȃ瓧���x��ύX
    }
    else
    {
        remainingAlpha = 1; // �ʏ�̓����x�ɖ߂�
    }
}

// ���e�̔�������
void bomb_explosion(int bomb_number)
{
    int waitTime = 1; // �G�����|�b�v����܂ł̑ҋ@���Ԃ�ݒ�
    float enemy_r = ENEMY_CORE_TEX_W * enemy[0].scale.x / 2; // �G�̔��a���v�Z

    // ���ׂĂ̓G�ɑ΂��ăq�b�g������s��
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        // ���e�̔����͈͂ƓG�̈ʒu���d�Ȃ��Ă��邩���`�F�b�N
        if (circle_hit(stage[bomb_number].bomb_position, enemy[i].position, BOMB_RANGE_SCALE * stage[bomb_number].bomb_range, enemy_r))
        {
            enemy[i].reset();             // �G�̃��Z�b�g�i���|�b�v�����j
            enemy[i].waitNum = waitTime;   // ���|�b�v�܂ł̑ҋ@���Ԃ�ݒ�
            waitTime++;                    // ���̓G�̑ҋ@���Ԃ𑝉�

            // �X�R�A�ǉ������i�X�R�A�����͕ʓr�����j
            score.enemy_kill_point();
        }
    }

    // �������I�������A���e��������Ԃɖ߂�
    stage[bomb_number] = bomb_def;
}

// ���e�̕`�揈��
void bomb_render()
{
    for (int i = 0; i < BOMB_MAX; i++)
    {
        // �����͈̔͂�`��
        sprite_render(range_circl, stage[i].bomb_position.x, stage[i].bomb_position.y, SCALE * stage[i].bomb_range * 2, SCALE * stage[i].bomb_range * 2, 0, 0, 400, 400, 200, 200, 0, 1, 0, 0);

        // ���e�{�̂�`��
        sprite_render(bomb, stage[i].bomb_position.x, stage[i].bomb_position.y, SCALE * stage[i].bomb_range * 0.5, SCALE * stage[i].bomb_range * 0.5, 0, 0, 400, 400, 200, 200, 0);

        // ���e�̎c�莞�Ԃ�`��
        std::string bomb_time = std::to_string(stage[i].bomb_time);
        text_out(1, bomb_time.c_str(), stage[i].bomb_position.x - 17, stage[i].bomb_position.y - 12, 1, 1, 1, 1, 1, 1);  // ���e�̈ʒu�Ƀ^�C�}�[��`��
    }

    // ���e�̃A�C�R����`��
    sprite_render(bomb, SCREEN_W - 70, SCREEN_H - 70, 0.5f, 0.5f, 1, 1, 400, 400, 200, 200, 0, 1, 1, 1, remainingAlpha);

    // �v���C���[�������Ă��锚�e����`��
    text_out(1, std::to_string(player_has_bomb), SCREEN_W - 40, SCREEN_H - 40, 2, 2, 1, 1, 1, remainingAlpha, TEXT_ALIGN::MIDDLE);
}

// ���e�̃��Z�b�g����
void bomb_deinit()
{
    // ���ׂĂ̔��e���f�t�H���g��ԂɃ��Z�b�g
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def;
    }

    // �X�v���C�g�����S�ɍ폜
    safe_delete(range_circl);
    safe_delete(bomb);
}