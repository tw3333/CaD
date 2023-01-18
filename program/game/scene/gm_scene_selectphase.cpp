#include "gm_scene_selectphase.h"

#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "gm_scene_deckedit.h"



void SceneSelectPhase::initialzie() {

	LoadSelectPhaseGraph();

	select_dungeon_tab = false;
	select_dungeon_tab2 = false;
	select_chara_tab = false;
	select_party_tab = false;

	tab = true;
	tab_dungeon = false;
	tab_party = false;

	tab2 = false;

}


void SceneSelectPhase::update(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();

	//シーン遷移
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		mgr->chengeScene(new SceneTitle());
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new ScenePlay());
	}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && dun_flame_move == 0) {
	//	mgr->chengeScene(new ScenePlay());
	//}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && flame_move == 1) {
		mgr->chengeScene(new SceneDeckEdit());
	}

	//各タブをフラグで管理するオペレーター関数
	opTab(tab);
	opTabDungeon(tab_dungeon);
	opTabParty(tab_party);

}

void SceneSelectPhase::render() {

	//UI描写
	DrawExtendGraph(0,0,width1*10,height1*10,background,false);
	DrawBox(0, 0, width1 * 10, height1 * 1, gray, true);
	DrawExtendGraph(0, 0, width1 * 2, height1 * 1, s_guild_tile, false);

	DrawBox(0,height1*9,width1*10,height1*10,gray,true);

	//DrawBox(0, 0, width1 * 3, height1 * 10, 0, true);

	drawTab(0, 1, 3, 2, select_dungeon);
	drawTab(0, 2, 3, 3, select_chara);
	drawTab(0, 3, 3, 4, select_party);

	drawTab(0, 4, 3, 5, select_tab);
	/*drawTab(0, 5, 3, 6, select_tab);
	drawTab(0, 6, 3, 7, select_tab);
	drawTab(0, 7, 3, 8, select_tab);
	drawTab(0, 8, 3, 9, select_tab);
	drawTab(0, 9, 3, 10, select_tab);*/


	drawTab(0, 1 + flame_move, 3, 2 + flame_move, select_flame);
	//drawTab(0,1,3,2,select_);

	if (select_dungeon_tab) {
		//DrawExtendGraph(width1 * 3, height1 * 1, width1 * 7, height1 * 10, select_tab, false);

		DrawBox(width1 * 3, height1 * 1, width1 * 7, height1 * 10, gray2, true);

		DrawExtendGraph(width1 * 4, height1 * 1, width1 * 6, height1 * 2, dungeon_1, true);
		DrawExtendGraph(width1 * 4, height1 * 2, width1 * 6, height1 * 3, dungeon_2, true);
		DrawExtendGraph(width1 * 4, height1 * 3, width1 * 6, height1 * 4, dungeon_3, true);
		DrawExtendGraph(width1 * 4, height1 * 4, width1 * 6, height1 * 5, dungeon_4, true);
		DrawExtendGraph(width1 * 4, height1 * 5, width1 * 6, height1 * 6, dungeon_5, true);
		DrawExtendGraph(width1 * 4, height1 * 7, width1 * 6, height1 * 7, dungeon_6, true);

		DrawExtendGraph(width1 * 4, height1 * (1 + dun_flame_move), width1 * 6, height1 * (2 + dun_flame_move), dungeon_select_flame, true);

		DrawBox(width1 * 7, height1 * 1, width1 * 10, height1 * 10, black, true);

		if (dun_flame_move == 0) {
			DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン１");
			DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★☆☆☆☆");
		}

		if (dun_flame_move == 1) {
			DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン２");
			DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★☆☆☆");
		}
		if (dun_flame_move == 2) {
			DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン３");
			DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★★☆☆");
		}
		if (dun_flame_move == 3) {
			DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン４");
			DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★★★☆");
		}

		if (dun_flame_move == 4) {
			DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン５");
			DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★★★★");
		}
	}

	if (select_party_tab) {
		DrawBox(width1 * 3, height1 * 1, width1 * 10, height1 * 10, gray2, true);
		DrawGraph(width1 * 4, height1 * 1 + (height1 / 2), member_img, true);
		DrawGraph(width1 * 4, height1 * 2, x2y1_flame_B, true);

		//選ばれたキャラ描写
		//pickCheck(pick_chara1, pick_chara2, pick_chara3, pick);
		DrawExtendGraph(width1 * 4, height1 * 2,width1*6,height1*3, pick_chara1, false);
		DrawExtendGraph(width1 * 4, height1 * 3,width1*6,height1*4, pick_chara2, false);
		DrawExtendGraph(width1 * 4, height1 * 4,width1*6,height1*5, pick_chara3, false);

		DrawGraph(width1 * 4, height1 * 2, x2y1_flame_1, true);
		DrawGraph(width1 * 4, height1 * 3, x2y1_flame_2, true);
		DrawGraph(width1 * 4, height1 * 4, x2y1_flame_3, true);


		DrawExtendGraph(width1 * 7, height1 * 2, width1 * 9, height1 * 3, chara01, false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 9, height1 * 4, chara02, false);
		DrawExtendGraph(width1 * 7, height1 * 4, width1 * 9, height1 * 5, chara03, false);
		DrawExtendGraph(width1 * 7, height1 * 5, width1 * 9, height1 * 6, chara04, false);
		DrawGraph(width1 * 7, height1 * (2 + p_flame_move), x2y1_flame_R, true);

		DrawBox(width1*3,height1*7,width1*10,height1*10,10,true);

		DrawStringEx(width1 * 3, height1 * 7, -1, "[z]:全て取り消し　[x]:選択");
		DrawStringEx(width1 * 3, height1 * 7 + 30, -1, "３人をパーティ編成してください");

		//DrawExtendGraph();

	}


	DrawStringEx(850, 50, -1, "scene selectphase");
	DrawStringEx(width1 * 0, height1 * 4, 100, "[space]:決定　[C]:戻る");
	DrawStringEx(width1 * 0, height1 * 4 + 50, 100, "[↑↓]：ウエ/シタ");


	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}
}




//文字アリtab描写用関数
void SceneSelectPhase::drawTab(int x, int y, int x2, int y2, int load) {
	DrawExtendGraph(width1 * x, height1 * y, width1 * x2, height1 * y2, load, true);
}

//void SceneSelectPhase::DrawPartyTab() {
//}


//tab操作用関数
void SceneSelectPhase::opTab(bool flag) {

	if (flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			flame_move -= 1;
		}
		else if (flame_move < 0) {
			flame_move = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			flame_move += 1;
		}
		else if (flame_move > 2) {
			flame_move = 2;
		}


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && flame_move == 0) {
			tab = false;
			select_dungeon_tab = true;
			tab_dungeon = true;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && flame_move == 2) {
			tab = false;
			select_party_tab = true;
			tab_party = true;
		}

	}

}
void SceneSelectPhase::opTabDungeon(bool flag) {
	
	if (tab_dungeon) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			dun_flame_move -= 1;
		}
		else if (dun_flame_move <= 0) {
			dun_flame_move = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			dun_flame_move += 1;
		}
		else if (dun_flame_move > 4) {
			dun_flame_move = 4;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
			select_dungeon_tab = false;
			tab = true;
			tab_dungeon = false;

		}
	}
}
void SceneSelectPhase::opTabParty(bool flag) {
	
	if (tab_party) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			p_flame_move -= 1;
		}
		else if (p_flame_move < 0) {
			p_flame_move = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			p_flame_move += 1;
		}
		else if (p_flame_move > 3) {
			p_flame_move = 3;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 0) {
			
			if (pick_chara1 == 0) {
				pick_chara1 = chara01;
			} else if (pick_chara1 != 0  && pick_chara2 == 0) {
				pick_chara2 = chara01;
			}else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
				pick_chara3 = chara01;
			}
			
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 1) {
			
			if (pick_chara1 == 0) {
				pick_chara1 = chara02;
			}
			else if (pick_chara1 != 0 && pick_chara2 == 0) {
				pick_chara2 = chara02;
			}
			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
				pick_chara3 = chara02;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 2) {
			if (pick_chara1 == 0) {
				pick_chara1 = chara03;
			}
			else if (pick_chara1 != 0 && pick_chara2 == 0) {
				pick_chara2 = chara03;
			}
			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
				pick_chara3 = chara03;
			}
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 3) {
			if (pick_chara1 == 0) {
				pick_chara1 = chara04;
			}
			else if (pick_chara1 != 0 && pick_chara2 == 0) {
				pick_chara2 = chara04;
			}
			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
				pick_chara3 = chara04;
			}
		}
		
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {
			pick_chara1 = 0;
			pick_chara2 = 0;
			pick_chara3 = 0;

		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
			select_party_tab = false;
			tab_party = false;
			tab = true;
			
		}

	}
	
}

//ロード関数
void SceneSelectPhase::LoadSelectPhaseGraph() {
	background = LoadGraph("graphics/select_back.jpg");
	s_guild_tile = LoadGraph("graphics/s_guild_tile.png");

	select_tab = LoadGraph("graphics/selectphase_selectflame.png");
	select_chara = LoadGraph("graphics/selectphase_selectflame_chara.png");
	select_dungeon = LoadGraph("graphics/selectphase_selectflame_dungeon.png");
	select_party = LoadGraph("graphics/selectphase_selectflame_party.png");
	select_flame = LoadGraph("graphics/selectphase_selectflame_red.png");

	dungeon_1 = LoadGraph("graphics/dungeon_1.png");
	dungeon_2 = LoadGraph("graphics/dungeon_2.png");
	dungeon_3 = LoadGraph("graphics/dungeon_3.png");
	dungeon_4 = LoadGraph("graphics/dungeon_4.png");
	dungeon_5 = LoadGraph("graphics/dungeon_5.png");
	dungeon_6 = LoadGraph("graphics/dungeon_6.png");
	dungeon_select_flame = LoadGraph("graphics/dungeon_select_flame.png");

	member_img = LoadGraph("graphics/member.png");
	x2y1_flame_B = LoadGraph("graphics/x2y1_flame_B.png");
	x2y1_flame_1 = LoadGraph("graphics/x2_y1_flame_1.png");
	x2y1_flame_2 = LoadGraph("graphics/x2_y1_flame_2.png");
	x2y1_flame_3 = LoadGraph("graphics/x2_y1_flame_3.png");

	x2y1_flame_R = LoadGraph("graphics/x2_y1_flame_R.png");
	chara01 = LoadGraph("graphics/chara1_face.png");
	chara02 = LoadGraph("graphics/chara2_face.png");
	chara03 = LoadGraph("graphics/chara3_face.png");
	chara04 = LoadGraph("graphics/chara4_face.png");

}

//キャラ選択描写用関数
void SceneSelectPhase::pickCheck(int pick1,int pick2, int pick3, int pick_chara) {
	
	if (pick1 == 0) {
		pick1 = pick_chara;
		
	}
	else if(pick1 != 0 && pick2 == 0) {
		pick2 == pick_chara;
	}
	else if (pick1 != 0 && pick2 != 0 && pick3 == 0) {
		pick3 = pick_chara;
	}

}