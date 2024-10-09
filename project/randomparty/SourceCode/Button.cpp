#include"all.h"
using namespace input;

int button_state;
Button button;

void Button::button_init() {
	button_state = 0;

	button = { 100, 100, 50 };

}

void Button::button_deinit() {

}

void Button::button_update() {
	switch (button_state)
	{
	case 0:
		//////// �����ݒ� ////////


		++button_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////



		button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };
		button.scale = { 1.0f, 1.0f };
		button.texPos = { 0, 0 };
		button.texSize = { button.x, button.y };
		button.pivot = { button.x / 2, button.y / 2 };
		button.color = { 1.000f, 1.0f, 1.0f, 1.0f };


		++button_state;
		/*fallthrough*/

	case 2:
		//////// �ʏ펞 ////////

		// �s���̑J��
		Button::button_act();

		break;
	}
}






void Button::button_render() {
	// �~�`�̃{�^���̕`��
	primitive::circle(button.position.x, button.position.y, button.radius, 1, 1, ToRadian(0), 0, 0, 0);


}

void Button::button_act() {
	



	// �{�^���̓����ō��N���b�N�������ꂽ�ꍇ
	if (TRG(0) & L_CLICK) {
		if (click()) {
			// �Q�[����ʂɑJ��
			nextScene = SCENE_GAME;
			return;
		}

	}

}


bool Button::click() {
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);

	// �~�̒��S���W
	float centerX = button.position.x;
	float centerY = button.position.y;

	// �~�̔��a
	float radius = button.texSize.x / 2;  // texSize.x �̓{�^���̒��a�Ƃ��Ďg�p

	// �}�E�X�̍��W�Ɖ~�̒��S�Ƃ̋������v�Z
	float distance = sqrt(pow(point.x - centerX, 2) + pow(point.y - centerY, 2));

	// ���������a�ȉ��ł���΃N���b�N���L��
	if (distance <= radius) {
		return true;
	}
	return false;
}


