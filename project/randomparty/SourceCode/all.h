#ifndef ALL_H
#define ALL_H

//******************************************************************************
//
//
//      all.h
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"

#include <windowsx.h>

#include "common.h"
#include "scene_game.h"
// 個々のヘッダーファイルは下の方へ
#include "scene_title.h"
#include "player.h"
#include "enemy.h"
#include "bomb.h"
#include "game_system.h"
#include "Button.h"
#include "timer.h"
#include "scene_result.h"

#ifdef USE_IMGUI
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#endif

#endif//ALL_H
