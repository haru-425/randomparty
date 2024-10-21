#include "all.h"

// �Q�[���̉��ʊǗ��p�̊O���ϐ�
extern Bolume game_volume;

// �����̏������֐�
void audio_init()
{
    // �Q�[���Ŏg�p���鉹�y�t�@�C����ǂݍ���
    music::load(0, L"./Data/Musics/9th_Attempt.wav");          
    music::load(1, L"./Data/Musics/�����]�o�g��.wav");         
    music::load(2, L"./Data/Musics/�}�b�h�T�C�G���e�B�X�q.wav");
    music::load(3, L"./Data/Musics/���_�����~�b�V����.wav");    

    // �V�X�e�����i���j���[�ȂǂŎg�p����SE�j���܂Ƃ߂��T�E���h�t�@�C����ǂݍ���
    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");   
}

// �������\�[�X�̉���֐�
void audio_deinit()
{
    // ���y���\�[�X�����
    music::clear;  // �������Ƀ��[�h���ꂽ���y�f�[�^��S�ăN���A
}