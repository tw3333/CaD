#include "gm_scene_charaedit.h"

#include "gm_scene_battle.h"

#include "../gm_person_manager.h"

void SceneCharaEdit::initialzie() {

	//画像ハンドル用
	LoadCharaEditGraph();

	//Chara* chara = new Chara();
	//chara->chara_[1].img_chara;

	flame = true;
}



void SceneCharaEdit::update(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();
	


	//シーン切り替え
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneBattle());
	}


	FlameMove(flame);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && f_trans == 0) {
		deckTab = true;
		flame = false;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {
		deckTab = false;
		flame = true;
	}



}

void SceneCharaEdit::render() {
//	PersonManager* pmgr = PersonManager::getInstance();
	
	//静的グラフィック
	DrawBox(0, 0, width1 * 10, height1 * 1, gray, true);
	DrawBox(0, 0, width1 * 2, height1 * 10, gray, true);
	DrawExtendGraph(0, height1 * 0, width1 * 2, height1 * 1, s_chara_tile, false); //キャラの顔タイル
	DrawExtendGraph(0, height1 * 2, width1 * 2, height1 * 3, chara_tile, false); //キャラの顔タイル
	DrawExtendGraph(0, height1 * 3, width1 * 2, height1 * 4, deck_tile, true); //デッキのタイル
	DrawExtendGraph(0, height1 * 4, width1 * 2, height1 * 5, equip_tile, true); //装備の顔タイル

	DrawExtendGraph(0, height1 * (3 + f_trans), width1 * 2, height1 * (4 + f_trans), select_flame, true); //選択フレームのタイル
	DrawDeckTab(deckTab);

	//DrawExtendGraph(0,height1*2,width1*2,height1*3,chara_[0].img_chara,false);

	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}

	//DrawStringEx(1300, 20, 1, "chara1HP:%d", pmgr.person1->HP);
	DrawCharaStatus();
}

//ここから関数

void SceneCharaEdit::LoadCharaEditGraph() {

	select_flame = LoadGraph("graphics/select_flame.png");
	s_chara_tile = LoadGraph("graphics/s_chara_tile.png");
	chara_tile = LoadGraph("graphics/chara1_face.png");
	deck_tile = LoadGraph("graphics/img_decktile.png");
	equip_tile = LoadGraph("graphics/img_EquipTile.png");

}

void SceneCharaEdit::FlameMove(bool f) {

	if (f) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
			f_trans -= 1;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S)) {
			f_trans += 1;
		}

		if (f_trans < 0) {
			f_trans = 0;
		}
		else if (f_trans > 1) {
			f_trans = 1;
		}
	}

}

void SceneCharaEdit::DrawDeckTab(bool f) {

	if (f) {
		DrawBox(width1 * 2, height1 * 1, width1 * 10, height1 * 10, dsgray, true);
		DrawBox(width1 * 2, height1 * 1, width1 * 4, height1 * 10, 0, false);
		DrawBox(width1 * 4, height1 * 1, width1 * 7, height1 * 10, 0, false);
		DrawBox(width1 * 7, height1 * 2, width1 * 10, height1 * 10, 0, false);
	}

}

void SceneCharaEdit::DrawCharaStatus() {

	DrawStringEx(width1*3,height1*2,-1,"Status : chara1");
	DrawStringEx(width1 * 3 + 50, height1 * 2 + 50, -1, "HP:%d",pmgr->person1->HPMAX);
	DrawStringEx(width1 * 3 + 50, height1 * 2 + 100, -1, "COST:%d",pmgr->person1->COSTMAX);
	DrawStringEx(width1 * 3 + 50, height1 * 2 + 150, -1, "%d", cmgr->CardList[0].c_hate);



}

