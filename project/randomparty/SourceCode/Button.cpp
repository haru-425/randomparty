#include"all.h"

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
		button.pivot = { button.x/2, button.y/2 };
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
	using namespace input;

	
	
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
	float button_right = button.position.x + button.texSize.x / 2;
	float button_left = button.position.x - button.texSize.x / 2;
	float button_top = button.position.y - button.texSize.y / 2;
	float button_buttom = button.position.y + button.texSize.y / 2;
	if (point.x <= button_right && button_left <= point.x)
	{
		
		if (point.y <= button_buttom && button_top <= point.y)
		{
			
			return true;
		}
	}
	return false;
}

