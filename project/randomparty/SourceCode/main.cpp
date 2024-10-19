//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< namespace >-----------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;

//------------------------------------------------------------------------------
//  WinMain（エントリポイント）
//------------------------------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)// 使用しない変数は記述しない
{
	// ゲームライブラリの初期設定
	GameLib::init(L"FIGAVOID", SCREEN_W, SCREEN_H, FULLSCREEN);

	//game_init();
	audio_init();
	while (GameLib::gameLoop())
	{

		// シーン切り替え処理
		if (curScene != nextScene)
		{
			// 現在のシーンに応じた終了処理
			switch (curScene)
			{
			case SCENE_TITLE:
				title_deinit();
				break;
			case SCENE_GAME:
				game_deinit();
				break;

			case SCENE_RESULT:
				result_deinit();
				break;

			case SCENE_HELP:
				help_deinit();
				break;

			case SCENE_SETTING:
				setting_deinit();
				break;
			}

			// 次のシーンに応じた初期設定処理
			switch (nextScene)
			{
			case SCENE_TITLE:
				title_init();
				break;
			case SCENE_GAME:
				game_init();
				break;

			case SCENE_RESULT:
				result_init();
				break;
			case SCENE_HELP:
				help_init();
				break;

			case SCENE_SETTING:
				setting_init();
				break;
			}
			// nextScene が curScene になる
			curScene = nextScene;
		}

		// 入力処理
		input::update();
		music::update();
		// 現在のシーンに応じた更新・描画処理
		switch (curScene)
		{
		case SCENE_TITLE:
			title_update();
			title_render();
			break;
		case SCENE_GAME:
			game_update();
			game_render();
			break;
		case SCENE_RESULT:
			result_update();
			result_render();
			break;

		case SCENE_HELP:
			help_update();
			help_render();
			break;

		case SCENE_SETTING:
			setting_update();
			setting_render();
			break;
		}

#ifdef USE_IMGUI
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
#endif

		// 現在のシーンを更新・描画
		/*game_update();
		game_render();*/

#ifdef USE_IMGUI
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

		// デバッグ文字列を描画
		debug::display(1.0f, 1.0f, 1.0f, 1, 1);

		//debug::setString("GP1_01 SAMPLE");

		// バックバッファの内容を表示
		GameLib::present(1, 0);
	}

	// 現在のシーンに応じた終了処理を行う
	switch (curScene)
	{
	case SCENE_TITLE:
		title_deinit();
		break;
	case SCENE_GAME:
		game_deinit();
		break;
	case SCENE_RESULT:
		result_deinit();
		break;
	case SCENE_HELP:
		help_deinit();
		break;
	case SCENE_SETTING:
		setting_deinit();
		break;
	}

	// ゲームシーンの終了
	//game_deinit();
	audio_deinit();
	// ゲームライブラリの終了処理
	GameLib::uninit();

	return 0;
}
