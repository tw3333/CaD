#include "gm_scene_title.h"
#include "gm_scene_selectphase.h"
#include "gm_scene_charaedit.h"

#include "../gm_manager.h"

void SceneTitle::initialzie() {
	title_img = LoadGraph("graphics/title_img.png");
}

void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || move == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		mgr->chengeScene( new SceneCharaEdit() );
	}

	if (move == 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		DxLib_End();
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		move -= 1;
	}
	else if (move < 0) {
		move = 0;
	}
	

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		move += 1;
	}
	else if (move > 1) {
		move = 1;
	}

}

void SceneTitle::render()
{
	//DrawGraph(0,0,title_img,false);
	DrawExtendGraph(0,0,DXE_WINDOW_WIDTH,DXE_WINDOW_HEIGHT,title_img,false);
	//DrawStringEx(50, 50, -1, "scene title");

	DrawStringEx(width1* 4 , height1 * (6 + move), -1, "Å®");

	DrawStringEx(width1 *4 + 50, height1 *6 , -1 ,"geme start");
	DrawStringEx(width1 * 4 + 50, height1 * 7 , -1, "game end");


	////ÉAÉ^Éäê¸
	//for (int i = 0; i < 10; ++i) {
	//	DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
	//	DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	//}
}
