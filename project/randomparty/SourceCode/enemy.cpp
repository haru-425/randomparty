#include "all.h"

int enemy_state;
bool enemies_active = true; // �G�̏o���𐧌䂷��t���O
extern PLAYER player;

typedef enum
{
	APPROACH_SLOW,
	APPROACH_FAST,

} ENEMY_TYPE;

ENEMY enemy[ENEMY_MAX];

Sprite* sprEnemy;
Sprite* sprEnemyCore;

void enemy_init() {
	enemy_state = 0;
}

void enemy_deinit() {
	safe_delete(sprEnemy);
	safe_delete(sprEnemyCore);
}

void enemy_update() {
	if (!enemies_active) return; // �G���I�t�Ȃ�X�V�����Ȃ�

	switch (enemy_state)
	{
	case 0:
		//////// �����ݒ� ////////
		sprEnemy = sprite_load(L"./Data/Images/enemy_approach_slow.png");
		sprEnemyCore = sprite_load(L"./Data/Images/enemyCore.png");
		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////
		for (int i = 0; i < ENEMY_MAX; i++) {
			enemy[i] = set_enemy(enemy[i]);

		}

		++enemy_state;
		/*fallthrough*/

	case 2:
		//////// �ʏ펞 ////////

		// �s���̑J��
		enemy_act();

		break;
	}
}

void enemy_render() {
	if (!enemies_active) return; // �G���I�t�Ȃ�`�揈���Ȃ�

	for (int i = 0; i < ENEMY_MAX; i++) {
		sprite_render(
			sprEnemy,
			enemy[i].position.x, enemy[i].position.y,
			enemy[i].scale.x, enemy[i].scale.y,
			enemy[i].texPos.x, enemy[i].texPos.y,
			enemy[i].texSize.x, enemy[i].texSize.y,
			enemy[i].pivot.x, enemy[i].pivot.y,
			enemy[i].angle,
			enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w
		);

		sprite_render(
			sprEnemyCore,
			enemy[i].position.x, enemy[i].position.y,
			enemy[i].scale.x, enemy[i].scale.y,
			enemy[i].texPos.x, enemy[i].texPos.y,
			ENEMY_CORE_TEX_W, ENEMY_CORE_TEX_H,
			ENEMY_CORE_PIVOT_X, ENEMY_CORE_PIVOT_Y,
			enemy[i].angle,
			enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w
		);
	}
}

void enemy_act() {
	if (!enemies_active) return; // �G���I�t�Ȃ瓮�쏈���Ȃ�

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy[i].angle = tracking(player.position, enemy[i].position);
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		float speedX, speedY;
		switch (enemy[i].type)
		{
		case APPROACH_SLOW:
			// �x�������̓G�̏���

			speedX = cosf(enemy[i].angle) * 1;
			speedY = sinf(enemy[i].angle) * 1;
			enemy[i].position.x += speedX * enemy[i].speed;
			enemy[i].position.y += speedY * enemy[i].speed;
			break;
		case APPROACH_FAST:
			// ���������̓G�̏���

			speedX = cosf(enemy[i].angle) * 1;
			speedY = sinf(enemy[i].angle) * 1;
			enemy[i].position.x += speedX * enemy[i].speed;
			enemy[i].position.y += speedY * enemy[i].speed;
			break;
		}


	}
}

ENEMY set_enemy(ENEMY enemy) {
	enemy.type = rand() % 2;

	enemy.angle = ToRadian(0);
	enemy.position = { static_cast<float>(rand() % SCREEN_W), static_cast<float>(rand() % SCREEN_H) };
	enemy.scale = { 0.1f, 0.1f };
	enemy.texPos = { 0, 0 };
	enemy.texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
	enemy.pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
	enemy.color = { 1.000f, 1.0f, 1.0f, 1.0f };
	switch (enemy.type)
	{
	case APPROACH_SLOW:
		enemy.speed = 2 + float(rand() % 2);
		break;
	case APPROACH_FAST:

		enemy.speed = 3 + float(rand() % 2);
		break;
	}

	return enemy;
}

