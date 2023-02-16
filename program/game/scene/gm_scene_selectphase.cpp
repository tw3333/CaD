#include "gm_scene_selectphase.h"

#include "../gm_manager.h"	

#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "gm_scene_deckedit.h"
#include "../gm_person_manager.h"



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
	cmgr->LoadCardDate();
	cmgr->LoadCardGraph();
	cmgr->SortJobCard();

	dungeonWindow = true; //最初はダンジョンWindow表示
	charaWindow = false;
	dungeonWindow = false;
	storageWindow = false;
	shopWindow = false;
	guildWindow = false;

	edit_chara1 = true; //最初はchara1表示
	edit_chara2 = false;
	edit_chara3 = false;
	edit_chara4 = false;

}


void SceneSelectPhase::update(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();
	

	//シーン遷移
	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
	//	mgr->chengeScene(new SceneTitle());
	//}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	mgr->chengeScene(new ScenePlay());
	//}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && dun_flame_move == 0) {
	//	mgr->chengeScene(new ScenePlay());
	//}


	
	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
	//	mgr->chengeScene(new SceneDeckEdit());
	//}

	//マウスの座標を引数に取得
	GetMousePoint(&MouseX, &MouseY);

	


	//Windowをマウスで選択
	SelectMouseWindow(MouseX, MouseY);



	OpDungeonWindow(dungeonWindow, MouseX, MouseY);
	OpCharaWindow(charaWindow, MouseX, MouseY);

	//各タブをフラグで管理するオペレーター関数
	
	
	//TODO 
	//OpCharaWindowないでこのコードが動かないのでここで書いている
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
	
		if (charaWindow && 10 < MouseX && MouseX < width1 * 2 - 10 && height1 * 2 + 10 + 10 < MouseY && MouseY < height1 * 3 + 10 + 10) {
			mgr->chengeScene(new SceneDeckEdit());
		}

	}


}

void SceneSelectPhase::render() {

	////UI描写
	//DrawExtendGraph(0,0,width1*10,height1*10,background,false);
	//DrawBox(0, 0, width1 * 10, height1 * 1, gray, true);
	//DrawExtendGraph(0, 0, width1 * 2, height1 * 1, s_guild_tile, false);

	//DrawBox(0,height1*9,width1*10,height1*10,gray,true);

	////DrawBox(0, 0, width1 * 3, height1 * 10, 0, true);

	//DrawTab(0, 1, 3, 2, select_dungeon);
	//DrawTab(0, 2, 3, 3, select_chara);
	//DrawTab(0, 3, 3, 4, select_party);

	//DrawTab(0, 4, 3, 5, select_tab);
	///*drawTab(0, 5, 3, 6, select_tab);
	//drawTab(0, 6, 3, 7, select_tab);
	//drawTab(0, 7, 3, 8, select_tab);
	//drawTab(0, 8, 3, 9, select_tab);
	//drawTab(0, 9, 3, 10, select_tab);*/


	//DrawTab(0, 1 + flame_move, 3, 2 + flame_move, select_flame);
	////drawTab(0,1,3,2,select_);

	//if (select_dungeon_tab) {
	//	//DrawExtendGraph(width1 * 3, height1 * 1, width1 * 7, height1 * 10, select_tab, false);

	//	DrawBox(width1 * 3, height1 * 1, width1 * 7, height1 * 10, gray2, true);

	//	DrawExtendGraph(width1 * 4, height1 * 1, width1 * 6, height1 * 2, dungeon_1, true);
	//	DrawExtendGraph(width1 * 4, height1 * 2, width1 * 6, height1 * 3, dungeon_2, true);
	//	DrawExtendGraph(width1 * 4, height1 * 3, width1 * 6, height1 * 4, dungeon_3, true);
	//	DrawExtendGraph(width1 * 4, height1 * 4, width1 * 6, height1 * 5, dungeon_4, true);
	//	DrawExtendGraph(width1 * 4, height1 * 5, width1 * 6, height1 * 6, dungeon_5, true);
	//	DrawExtendGraph(width1 * 4, height1 * 7, width1 * 6, height1 * 7, dungeon_6, true);

	//	DrawExtendGraph(width1 * 4, height1 * (1 + dun_flame_move), width1 * 6, height1 * (2 + dun_flame_move), dungeon_select_flame, true);

	//	DrawBox(width1 * 7, height1 * 1, width1 * 10, height1 * 10, black, true);

	//	if (dun_flame_move == 0) {
	//		DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン１");
	//		DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★☆☆☆☆");
	//	}

	//	if (dun_flame_move == 1) {
	//		DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン２");
	//		DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★☆☆☆");
	//	}
	//	if (dun_flame_move == 2) {
	//		DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン３");
	//		DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★★☆☆");
	//	}
	//	if (dun_flame_move == 3) {
	//		DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン４");
	//		DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★★★☆");
	//	}

	//	if (dun_flame_move == 4) {
	//		DrawStringEx(width1 * 7, height1 * 1, -1, "ダンジョン５");
	//		DrawStringEx(width1 * 7, height1 * 1 + 50, -1, "難易度：★★★★★");
	//	}
	//}

	//if (select_party_tab) {
	//	
	//	DrawBox(width1 * 3, height1 * 1, width1 * 10, height1 * 10, gray2, true);
	//	DrawGraph(width1 * 4, height1 * 1 + (height1 / 2), member_img, true);
	//	DrawGraph(width1 * 4, height1 * 2, x2y1_flame_B, true);

	//	//選ばれたキャラ描写
	//	//pickCheck(pick_chara1, pick_chara2, pick_chara3, pick);
	//	DrawExtendGraph(width1 * 4, height1 * 2,width1*6,height1*3, pick_chara1, false);
	//	DrawExtendGraph(width1 * 4, height1 * 3,width1*6,height1*4, pick_chara2, false);
	//	DrawExtendGraph(width1 * 4, height1 * 4,width1*6,height1*5, pick_chara3, false);

	//	DrawGraph(width1 * 4, height1 * 2, x2y1_flame_1, true);
	//	DrawGraph(width1 * 4, height1 * 3, x2y1_flame_2, true);
	//	DrawGraph(width1 * 4, height1 * 4, x2y1_flame_3, true);


	//	DrawExtendGraph(width1 * 7, height1 * 2, width1 * 9, height1 * 3, chara01, false);
	//	DrawExtendGraph(width1 * 7, height1 * 3, width1 * 9, height1 * 4, chara02, false);
	//	DrawExtendGraph(width1 * 7, height1 * 4, width1 * 9, height1 * 5, chara03, false);
	//	DrawExtendGraph(width1 * 7, height1 * 5, width1 * 9, height1 * 6, chara04, false);
	//	DrawGraph(width1 * 7, height1 * (2 + p_flame_move), x2y1_flame_R, true);

	//	DrawBox(width1*3,height1*7,width1*10,height1*10,10,true);

	//	DrawStringEx(width1 * 3, height1 * 7, -1, "[z]:全て取り消し　[x]:選択");
	//	DrawStringEx(width1 * 3, height1 * 7 + 30, -1, "３人をパーティ編成してください");

	//	//DrawExtendGraph();

	//}


	//DrawStringEx(850, 50, -1, "scene selectphase");
	//DrawStringEx(width1 * 0, height1 * 4, 100, "[space]:決定　[C]:戻る");
	//DrawStringEx(width1 * 0, height1 * 4 + 50, 100, "[↑↓]：ウエ/シタ");
	
	
	DrawBox(0,0,width1*10,height1*10,white,true);

	DrawDungeonWindow(dungeonWindow);
	DrawCharaWindow(charaWindow);
	DrawStorageWindow(storageWindow);
	DrawShopWindow(shopWindow);
	DrawGuildWindow(guildWindow);

	DrawStringEx(0,0,1,"dungeon");
	DrawStringEx(width1*2, 0, 1, "chara");
	DrawStringEx(width1*4, 0, 1, "guild(未実装)");
	DrawStringEx(width1*6, 0, 1, "shop(未実装)");
	DrawStringEx(width1*8, 0, 1, "souko(未実装)");

	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}
}




//文字アリtab描写用関数
void SceneSelectPhase::DrawTab(int x, int y, int x2, int y2, int load) {
	DrawExtendGraph(width1 * x, height1 * y, width1 * x2, height1 * y2, load, true);
}

//void SceneSelectPhase::DrawPartyTab() {
//}





//void SceneSelectPhase::opTabParty(bool flag) {
//	
//	if (tab_party) {
//
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
//			p_flame_move -= 1;
//		}
//		else if (p_flame_move < 0) {
//			p_flame_move = 0;
//		}
//
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
//			p_flame_move += 1;
//		}
//		else if (p_flame_move > 3) {
//			p_flame_move = 3;
//		}
//
//		//chara1pick
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 0) {
//			
//			if (pick_chara1 == 0) {
//				pick_chara1 = chara01;
//			} 
//			else if (pick_chara1 != 0  && pick_chara2 == 0) {
//				pick_chara2 = chara01;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
//				pick_chara3 = chara01;
//			}
//			
//			pmgr->person1->PICK = true;
//			
//		}
//
//		//chara2pick
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 1) {
//			
//			if (pick_chara1 == 0) {
//				pick_chara1 = chara02;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 == 0) {
//				pick_chara2 = chara02;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
//				pick_chara3 = chara02;
//			}
//
//			pmgr->person2->PICK = true;
//		}
//
//		//chara3pick
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 2) {
//			
//			if (pick_chara1 == 0) {
//				pick_chara1 = chara03;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 == 0) {
//				pick_chara2 = chara03;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
//				pick_chara3 = chara03;
//			}
//
//			pmgr->person3->PICK = true;
//		}
//
//		//chara4pick
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && p_flame_move == 3) {
//			
//			if (pick_chara1 == 0) {
//				pick_chara1 = chara04;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 == 0) {
//				pick_chara2 = chara04;
//			}
//			else if (pick_chara1 != 0 && pick_chara2 != 0 && pick_chara3 == 0) {
//				pick_chara3 = chara04;
//			}
//
//			pmgr->person4->PICK = true;
//
//		}
//		
//		//全て取り消し
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {
//			pick_chara1 = 0;
//			pick_chara2 = 0;
//			pick_chara3 = 0;
//
//			pmgr->person1->PICK = false;
//			pmgr->person2->PICK = false;
//			pmgr->person3->PICK = false;
//			pmgr->person4->PICK = false;
//
//
//		}
//
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
//			select_party_tab = false;
//			tab_party = false;
//			tab = true;
//			
//		}
//
//	}
//	
//}

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
void SceneSelectPhase::PickCheck(int pick1,int pick2, int pick3, int pick_chara) {
	
	if (pick1 == 0) {
		pick1 = pick_chara;
		
	}
	else if(pick1 != 0 && pick2 == 0) {
		pick2 = pick_chara;
	}
	else if (pick1 != 0 && pick2 != 0 && pick3 == 0) {
		pick3 = pick_chara;
	}

}

void SceneSelectPhase::DrawDungeonWindow(bool f) {

	if (f) {

		DrawBox(0,0,width1*2,height1*1,gray,true);

		DrawBox(10,height1*1 + 10,width1*2 -10,height1*2 + 10,gray2,true);
		DrawBox(10, height1 * 2 + 10 + 10, width1 * 2 -10 , height1 * 3 + 10 + 10 , gray2, true);


		DrawStringEx(10, height1 * 1 + 10,1,"dungeon");
		DrawStringEx(10, height1 * 2 + 10 + 10, 1, "party編成");


		if (tab1_dw) {

			DrawBox(width1 * 2 + 10, height1 * 1 + 10, width1 * 10 - 10, height1 * 10 - 10, gray2, true);
			DrawStringEx(width1 * 2 + 10, height1 * 1 + 10,1,"tab1");


		}

		if (tab2_dw) {

			DrawBox(width1 * 2 + 10, height1 * 1 + 10, width1 * 10 - 10, height1 * 10 - 10, gray2, true);
			DrawStringEx(width1 * 2 + 10, height1 * 1 + 10, 1, "tab2");


		}


	}
}

void SceneSelectPhase::DrawCharaWindow(bool f) {

	if (f) {
		
		DrawBox(width1*2, 0, width1 * 4, height1 * 1, gray, true);

		DrawBox(10, height1 * 1 + 10, width1 * 2 - 10, height1 * 2 + 10, gray2, true);
		DrawBox(10, height1 * 2 + 10 + 10, width1 * 2 - 10, height1 * 3 + 10 + 10, gray2, true); //deck
		DrawBox(10, height1 * 3 + 10 + 20, width1 * 2 - 10, height1 * 4 + 10 + 20, gray2, true); //skill
		DrawBox(10, height1 * 4 + 10 + 30, width1 * 2 - 10, height1 * 5 + 10 + 30, gray2, true); //soubi
		DrawBox(10, height1 * 5 + 10 + 40, width1 * 2 - 10, height1 * 6 + 10 + 40, gray2, true); //item


		if (tab1_cw) {

			DrawBox(width1 * 2 + 10, height1 * 1 + 10, width1 * 10 - 10, height1 * 10 - 10, gray2, true);


			DrawBox(width1 * 2 + 100, height1 * 1 + 40, width1 * 4 + 100, height1 * 2 + 40, gray, true);
			DrawBox(width1 * 4 + 100 + 50, height1 * 1 + 40, width1 * 6 + 100 + 50, height1 * 2 + 40, gray, true);
			DrawBox(width1 * 6 + 100 + 50 + 50, height1 * 1 + 40, width1 * 8 + 100 + 50 + 50, height1 * 2 + 40, gray, true);
			DrawBox(width1 * 2 + 100, height1 * 2 + 40 + 60, width1 * 4 + 100, height1 * 3 + 40 + 60, gray, true);

			DrawStringEx(width1 * 2 + 100, height1 * 1 + 40,1,"chara1");
			DrawStringEx(width1 * 4 + 100 + 50, height1 * 1 + 40, 1, "chara2");
			DrawStringEx(width1 * 6 + 100 + 50 + 50, height1 * 1 + 40, 1, "chara3");
			DrawStringEx(width1 * 2 + 100, height1 * 2 + 100, 1, "chara4");

		}

		if (pmgr->person1->EDIT == true) {
			DrawStringEx(10, height1 * 1 + 10,1,"Chara1");
		}
		if (pmgr->person2->EDIT == true) {
			DrawStringEx(10, height1 * 1 + 10, 1, "Chara2");
		}
		if (pmgr->person3->EDIT == true) {
			DrawStringEx(10, height1 * 1 + 10, 1, "Chara3");
		}
		if (pmgr->person4->EDIT == true) {
			DrawStringEx(10, height1 * 1 + 10, 1, "Chara4");
		}


		DrawStringEx(10, height1 * 2 + 10 + 10,1,"deck");
		DrawStringEx(10, height1 * 3 + 10 + 20, 1, "skill(未実装)");
		DrawStringEx(10, height1 * 4 + 10 + 30, 1, "soubi(未実装)");
		DrawStringEx(10, height1 * 5 + 10 + 40, 1, "item(未実装)");

	}

}

void SceneSelectPhase::DrawGuildWindow(bool f) {

	if (f) {
		
		DrawBox(width1 * 4, 0, width1 * 6, height1 * 1, gray, true);
		//DrawBox(width1 * 4, 0,1,"");
	}
	


}

void SceneSelectPhase::DrawShopWindow(bool f) {

	if (f) {
		DrawBox(width1 * 6, 0, width1 * 8, height1 * 1, gray, true);
	}
}

void SceneSelectPhase::DrawStorageWindow(bool f) {

	if (f) {
		DrawBox(width1 * 8, 0, width1 * 10, height1 * 1, gray, true);
	}




}
void SceneSelectPhase::SelectMouseWindow(int mx, int my) {

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

		if (0 < mx && mx < width1* 2 && 0 < my && my < height1*1) {
			
			dungeonWindow = true;
			
			charaWindow = false;
			storageWindow = false;
			shopWindow = false;
			guildWindow = false;

		}

		if (width1*2 < mx && mx < width1 * 4 && 0 < my && my < height1*1) {

			charaWindow = true;

			dungeonWindow = false;
			storageWindow = false;
			shopWindow = false;
			guildWindow = false;

		}

		if (width1 * 4 < mx && mx < width1 * 6 && 0 < my && my < height1 * 1) {

			guildWindow = true;

			dungeonWindow = false;
			charaWindow = false;
			storageWindow = false;
			shopWindow = false;

		}

		if (width1 * 6 < mx && mx < width1 * 8 && 0 < my && my < height1 * 1) {

			shopWindow = true;

			guildWindow = false;
			dungeonWindow = false;
			charaWindow = false;
			storageWindow = false;

		}


		if (width1 * 8 < mx && mx < width1 * 10 && 0 < my && my < height1 * 1) {

			storageWindow = true;

			guildWindow = false;
			dungeonWindow = false;
			charaWindow = false;
			shopWindow = false;

		}

	}
}

void SceneSelectPhase::OpDungeonWindow(bool f, int mx , int my) {

	if (f) {

		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

			if (10 < mx && mx < width1 * 2 - 10 && height1 * 1 + 10 < my && my < height1 * 2 + 10) {

				tab1_dw = true;
				tab2_dw = false;
			}

			if (10 < mx && mx < width1 * 2 - 10 && height1 * 2 + 10 + 10 < my && my < height1 * 3 + 10 + 10) {

				tab2_dw = true;
				tab1_dw = false;

			}

		}


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {

			tab1_dw = false;
			tab2_dw = false;
		}

	}

}

void SceneSelectPhase::OpCharaWindow(bool f, int mx, int my) {

	if (f) {

		if(tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

			if (10 < mx && mx < width1 * 2 - 10 && height1 * 1 + 10 < my && my < height1 * 2 + 10) {

				tab1_cw = true;

			}

			if (10 < mx && mx < width1 * 2 - 10 && height1 * 2 + 10 + 10 < my && my < height1 * 3 + 10 + 10) {

		
			}

			
			if (tab1_cw) {

				if (width1 * 2 + 100 < mx && mx < width1 * 4 + 100 && height1 * 1 + 40 < my && my < height1 * 2 + 40) {

				
					pmgr->person1->EDIT = true;

					pmgr->person2->EDIT = false;
					pmgr->person3->EDIT = false;
					pmgr->person4->EDIT = false;

				}

				if (width1 * 4 + 100 + 50 < mx && mx < width1 * 6 + 100 + 50 && height1 * 1 + 40 < my && my < height1 * 2 + 40) {


					pmgr->person2->EDIT = true;

					pmgr->person1->EDIT = false;
					pmgr->person3->EDIT = false;
					pmgr->person4->EDIT = false;


				}

				if (width1 * 6 + 200 < mx && mx < width1 * 8 + 200 && height1 * 1 + 40 < my && my < height1 * 2 + 40) {

					pmgr->person3->EDIT = true;

					pmgr->person1->EDIT = false;
					pmgr->person2->EDIT = false;
					pmgr->person4->EDIT = false;


				}

				if (width1 * 2 + 100 < mx && mx < width1 * 4 + 100 && height1 * 2 + 40 + 60 < my && my < height1 * 3 + 40 + 60) {
					
					pmgr->person4->EDIT = true;

					pmgr->person1->EDIT = false;
					pmgr->person2->EDIT = false;
					pmgr->person3->EDIT = false;

				}

	
			}
		
		}

		
		
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {

			tab1_cw = false;
		}


	}


}