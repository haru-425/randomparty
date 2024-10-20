#include "all.h"
using namespace input;

int button_state;
int end_button_state;
int help_button_state;
int set_button_state;
Button button;
Button EndButton;
Button HelpButton;
Button SetButton;
Button nextbutton;
Button backbutton;
Button select_player_button;
Button select_enemy_button;
Button select_score_button;

Sprite* sprButton;
Sprite* sprEnd;
Sprite* sprHelp;
Sprite* sprSet;

extern int render_mode;
extern int select_c;

extern Button bgm_volume_up;
extern Button bgm_volume_Down;
extern Button se_volume_up;
extern Button se_volume_Down;



void Button::button_init()
{
	button_state = 0;

}

void Button::end_button_init()
{
	end_button_state = 0;
}

void Button::help_button_init()
{
	help_button_state = 0;
}

void Button::set_button_init()
{
	set_button_state = 0;
}

void Button::button_deinit()
{
	safe_delete(sprButton);
}

void Button::end_button_deinit()
{
	safe_delete(sprEnd);
}

void Button::help_button_deinit()
{
	safe_delete(sprHelp);
}

void Button::set_button_deinit()
{
	safe_delete(sprSet);
}

void Button::button_update()
{
	switch (button_state)
	{
	case 0:
		// �����ݒ�
		sprButton = sprite_load(L"./Data/Images/playButton.png");

		++button_state;
		/*fallthrough*/

	case 1:
		// �p�����[�^�̐ݒ�
		button.position = { SCREEN_W * 0.5f, SCREEN_H * 0.7f };  // ���S�ʒu
		button.scale = { 1.0f, 1.0f };
		button.texPos = { 0, 0 };
		button.texSize = { BUTTON_TEX_W, BUTTON_TEX_H };
		button.pivot = { BUTTON_PIVOT_X, BUTTON_PIVOT_Y };
		button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		button.radius = BUTTON_TEX_W / 4;

		++button_state;
		/*fallthrough*/

	case 2:
		// �ʏ펞�̏���
		Button::button_act();

		break;
	}
}

void Button::end_button_update()
{
	switch (end_button_state)
	{
	case 0:
		// �����ݒ�
		sprEnd = sprite_load(L"./Data/Images/returnButton.png");

		++end_button_state;
		/*fallthrough*/

	case 1:
		// �p�����[�^�̐ݒ�
		EndButton.position = { 90, 60 };  // ���S�ʒu
		EndButton.scale = { 1.0f, 1.0f };
		EndButton.texPos = { 0, 0 };
		EndButton.texSize = { END_TEX_W, END_TEX_H };
		EndButton.pivot = { END_PIVOT_X, END_PIVOT_Y };
		EndButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };


		++end_button_state;
		/*fallthrough*/

	case 2:
		// �ʏ펞�̏���
		Button::end_button_act();

		break;
	}
}

void Button::help_button_update()
{
	switch (help_button_state)
	{
	case 0:
		// �����ݒ�
		sprHelp = sprite_load(L"./Data/Images/helpButton.png");

		++help_button_state;
		/*fallthrough*/

	case 1:
		// �p�����[�^�̐ݒ�
		HelpButton.position = { SCREEN_W * 0.3f, SCREEN_H * 0.8f };  // ���S�ʒu
		HelpButton.scale = { 1.0f, 1.0f };
		HelpButton.texPos = { 0, 0 };
		HelpButton.texSize = { HELP_TEX_W, HELP_TEX_H };
		HelpButton.pivot = { HELP_PIVOT_X, HELP_PIVOT_Y };
		HelpButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		HelpButton.radius = HELP_TEX_W / 6.7;


		++help_button_state;
		/*fallthrough*/

	case 2:
		// �ʏ펞�̏���
		Button::help_button_act();

		break;
	}
}

void Button::set_button_update()
{
	switch (set_button_state)
	{
	case 0:
		// �����ݒ�
		sprSet = sprite_load(L"./Data/Images/settingButton.png");

		++set_button_state;
		/*fallthrough*/

	case 1:
		// �p�����[�^�̐ݒ�
		SetButton.position = { SCREEN_W * 0.7f, SCREEN_H * 0.8f };  // ���S�ʒu
		SetButton.scale = { 1.0f, 1.0f };
		SetButton.texPos = { 0, 0 };
		SetButton.texSize = { SET_TEX_W, SET_TEX_H };
		SetButton.pivot = { SET_PIVOT_X, SET_PIVOT_Y };
		SetButton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		SetButton.radius = SET_TEX_W / 6.7;

		++set_button_state;
		/*fallthrough*/

	case 2:
		// �ʏ펞�̏���
		Button::set_button_act();

		break;
	}
}

void Button::button_render()
{

	sprite_render(sprButton, button.position.x, button.position.y, scale.x, scale.y, 0, 0, 440, 440, 440 / 2, 440 / 2);
}

void Button::end_button_render()
{
	sprite_render(sprEnd, EndButton.position.x, EndButton.position.y, scale.x, scale.y, 0, 0, 128, 64, 128 / 2, 64 / 2);
}

void Button::help_button_render()
{
	sprite_render(sprHelp, HelpButton.position.x, HelpButton.position.y, scale.x, scale.y, 0, 0, 440, 440, 440 / 2, 440 / 2);

}

void Button::set_button_render()
{
	sprite_render(sprSet, SetButton.position.x, SetButton.position.y, scale.x, scale.y, 0, 0, 440, 440, 440 / 2, 440 / 2);

}

void Button::button_act()
{
	// �{�^�������ō��N���b�N�������ꂽ�ꍇ
	if (TRG(0) & L_CLICK) {
		if (click()) {
			// �Q�[����ʂɑJ��

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			game_start();
			return;
		}
	}

	if (click())
	{
		scale = { 0.6f,0.6f };
	}
	else {
		scale = { 0.5f,0.5f };
	}
}

void Button::end_button_act()
{
	if (select_c != 0)
	{
		if (TRG(0) & L_CLICK) {
			if (end_click()) {

				sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
				render_mode = 0;
				select_c = 0;
				return;
			}
		}
	}
	// �{�^�������ō��N���b�N�������ꂽ�ꍇ
	if (TRG(0) & L_CLICK) {
		if (end_click()) {

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			result_end();
			return;
		}
	}
	if (end_click())
	{
		scale = { 1.6f,1.6f };
	}
	else {
		scale = { 1.5f,1.5f };
	}
}

void Button::help_button_act()
{
	// �{�^�������ō��N���b�N�������ꂽ�ꍇ
	if (TRG(0) & L_CLICK) {
		if (help_click()) {

			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			help_start();
			return;
		}
	}
	if (help_click())
	{
		scale = { 0.4f,0.4f };
	}
	else {
		scale = { 0.3f,0.3f };
	}
}

void Button::set_button_act()
{
	// �{�^�������ō��N���b�N�������ꂽ�ꍇ
	if (TRG(0) & L_CLICK) {
		if (set_click()) {
			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);
			nextScene = SCENE_SETTING;
			return;
		}
	}
	if (set_click())
	{
		scale = { 0.4f,0.4f };
	}
	else {
		scale = { 0.3f,0.3f };
	}
}

bool Button::click() {
	// �}�E�X�J�[�\���̍��W�擾
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);

	// �~�̒��S���W
	float centerX = button.position.x;
	float centerY = button.position.y;

	// �}�E�X�J�[�\���Ɖ~�̒��S�Ƃ̋������v�Z
	float distance = sqrt(pow(point.x - centerX, 2) + pow(point.y - centerY, 2));

	// �������{�^���̔��a�ȉ��ł���΃N���b�N���L��
	return (distance <= button.radius);
}

bool Button::end_click() {
	// �}�E�X�J�[�\���̍��W�擾
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(window::getHwnd(), &point);

	// �{�^���̎l�ӂ��擾
	float button_right = EndButton.position.x + EndButton.texSize.x / 1.3;
	float button_left = EndButton.position.x - EndButton.texSize.x / 1.3;
	float button_top = EndButton.position.y - EndButton.texSize.y / 1.3;
	float button_bottom = EndButton.position.y + EndButton.texSize.y / 1.3;

	// �}�E�X�̍��W���{�^���͈͓̔����`�F�b�N
	bool isWithinX = (point.x >= button_left && point.x <= button_right);
	bool isWithinY = (point.y >= button_top && point.y <= button_bottom);

	// �}�E�X���{�^���͈͓��Ȃ�N���b�N���ꂽ�Ɣ���
	return isWithinX && isWithinY;
}

bool Button::help_click()
{
	// �}�E�X�J�[�\���̍��W�擾
	POINT Helppoint;
	GetCursorPos(&Helppoint);
	ScreenToClient(window::getHwnd(), &Helppoint);

	// �~�̒��S���W
	float HelpcenterX = HelpButton.position.x;
	float HelpcenterY = HelpButton.position.y;

	// �}�E�X�J�[�\���Ɖ~�̒��S�Ƃ̋������v�Z
	float Helpdistance = sqrt(pow(Helppoint.x - HelpcenterX, 2) + pow(Helppoint.y - HelpcenterY, 2));

	// �������{�^���̔��a�ȉ��ł���΃N���b�N���L��
	return (Helpdistance <= HelpButton.radius);
}

bool Button::set_click()
{
	// �}�E�X�J�[�\���̍��W�擾
	POINT Setpoint;
	GetCursorPos(&Setpoint);
	ScreenToClient(window::getHwnd(), &Setpoint);

	// �~�̒��S���W
	float SetcenterX = SetButton.position.x;
	float SetcenterY = SetButton.position.y;

	// �}�E�X�J�[�\���Ɖ~�̒��S�Ƃ̋������v�Z
	float Setdistance = sqrt(pow(Setpoint.x - SetcenterX, 2) + pow(Setpoint.y - SetcenterY, 2));

	// �������{�^���̔��a�ȉ��ł���΃N���b�N���L��
	return (Setdistance <= SetButton.radius);
}

void Button::next_button_init()
{
	nextbutton.position = { SCREEN_W - 50.0f, SCREEN_H / 2.0f };  // ���S�ʒu
	nextbutton.scale = { 1.0f, 1.0f };
	nextbutton.texPos = { 0, 0 };
	nextbutton.texSize = { 100, 300 };
	nextbutton.pivot = { 0, 0 };
	nextbutton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Button::back_button_init()
{
	backbutton.position = { 50.0f, SCREEN_H / 2.0f };  // ���S�ʒu
	backbutton.scale = { 1.0f, 1.0f };
	backbutton.texPos = { 0, 0 };
	backbutton.texSize = { 100, 300 };
	backbutton.pivot = { 0, 0 };
	backbutton.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Button::tuto_player_button_init()
{
	select_player_button.position = { SCREEN_W / 2.0f, SCREEN_H / 2.0f - 200 };  // ���S�ʒu
	select_player_button.scale = { 0.3f, 0.3f };
	select_player_button.texPos = { 0, 0 };
	select_player_button.texSize = { 1500, 500 };
	select_player_button.pivot = { 0, 0 };
	select_player_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Button::tyto_enemy_button_init()
{
	select_enemy_button.position = { SCREEN_W / 2.0f, SCREEN_H / 2.0f };  // ���S�ʒu
	select_enemy_button.scale = { 0.3f, 0.3f };
	select_enemy_button.texPos = { 0, 0 };
	select_enemy_button.texSize = { 1500, 500 };
	select_enemy_button.pivot = { 0, 0 };
	select_enemy_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Button::descript_score_button_init()
{
	select_score_button.position = { SCREEN_W / 2.0f, SCREEN_H / 2.0f + 200 };  // ���S�ʒu
	select_score_button.scale = { 0.3f, 0.3f };
	select_score_button.texPos = { 0, 0 };
	select_score_button.texSize = { 1500, 500 };
	select_score_button.pivot = { 0, 0 };
	select_score_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Button::bgm_volume_Down_init()
{
	bgm_volume_Down.position = { 1027, 390 };
	bgm_volume_Down.scale = { 0.3f, 0.2f };
	bgm_volume_Down.texPos = { 0, 0 };
	bgm_volume_Down.texSize = { 400, 400 };
	bgm_volume_Down.pivot = { 0, 0 };
	bgm_volume_Down.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}
void Button::bgm_volume_up_init()
{
	bgm_volume_up.position = { 1513, 390 };  // ���S�ʒu
	bgm_volume_up.scale = { 0.3f, 0.2f };
	bgm_volume_up.texPos = { 0, 0 };
	bgm_volume_up.texSize = { 400, 400 };
	bgm_volume_up.pivot = { 0, 0 };
	bgm_volume_up.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}
void Button::se_volume_Down_init()
{
	se_volume_Down.position = { 1027, 590 };  // ���S�ʒu
	se_volume_Down.scale = { 0.3f, 0.2f };
	se_volume_Down.texPos = { 0, 0 };
	se_volume_Down.texSize = { 400, 400 };
	se_volume_Down.pivot = { 0, 0 };
	se_volume_Down.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}
void Button::se_volume_up_init()
{
	se_volume_up.position = { 1513, 590 };  // ���S�ʒu
	se_volume_up.scale = { 0.3f, 0.2f };
	se_volume_up.texPos = { 0, 0 };
	se_volume_up.texSize = { 400, 400 };
	se_volume_up.pivot = { 0, 0 };
	se_volume_up.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

bool Button::rect_click(Button button_info)
{
	// �}�E�X�J�[�\���̍��W�擾
	POINT nextpoint;
	GetCursorPos(&nextpoint);
	ScreenToClient(window::getHwnd(), &nextpoint);
	// �{�^���̎l�ӂ��擾
	float button_right = button_info.position.x + button_info.texSize.x * button_info.scale.x / 2;
	float button_left = button_info.position.x - button_info.texSize.x * button_info.scale.x / 2;
	float button_top = button_info.position.y - button_info.texSize.y * button_info.scale.y / 2;
	float button_bottom = button_info.position.y + button_info.texSize.y * button_info.scale.y / 2;

	// �}�E�X�̍��W���{�^���͈͓̔����`�F�b�N
	bool isWithinX = (nextpoint.x >= button_left && nextpoint.x <= button_right);
	bool isWithinY = (nextpoint.y >= button_top && nextpoint.y <= button_bottom);

	// �}�E�X���{�^���͈͓��Ȃ�N���b�N���ꂽ�Ɣ���
	return isWithinX && isWithinY;
}

