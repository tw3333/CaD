#include "gm_scene_deckedit.h"
#include "gm_scene_selectphase.h"
#include <iostream>
#include <vector>

#include "gm_scene_battle.h"


void SceneDeckEdit::initialzie() {
	//cmgr->LoadCardDate();
	//cmgr->LoadCardGraph();
	//cmgr->SortJobCard();

	//tab管理用フラグ
	tab = true;
	draw_tab = true;
	chara1_tab = false;
	chara2_tab = false;
	chara3_tab = false;
	chara4_tab = false;
	PushCheck = false;

}

void SceneDeckEdit::update(float delta_time) {
	GetMousePoint(&MouseX, &MouseY);
	
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		mgr->chengeScene(new SceneSelectPhase());
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
		mgr->chengeScene(new SceneBattle());
	}

	ListMouseCheck(MouseX, MouseY);

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

		if (0 < MouseX && MouseX < width1*1 && 0 < MouseY && MouseY < height1* 1) {
			mgr->chengeScene(new SceneSelectPhase());
		}
	}




	//tab操作用関数群
	/*opTab(tab);
	opChara01_Tab(chara1_tab);
	opChara02_Tab(chara2_tab);
	opChara03_Tab(chara3_tab);
	opChara04_Tab(chara4_tab);*/

}

void SceneDeckEdit::render() {

	//cmgr->LoadCardDate();
	//cmgr->LoadCardGraph();
	//cmgr->SortJobCard();

	//DrawBox(0, 0, width1 * 10, height1 * 10, white, true);

	//下地
	DrawBox(width1 * 0, height1 * 1, width1 * 3, height1 * 10, dsgray, true);
	DrawBox(width1 * 3, height1 * 1, width1 * 7, height1 * 10, dimgray, true);
	DrawBox(width1 * 7, height1 * 1, width1 * 10, height1 * 10, gray, true);
	DrawExtendGraph(width1 * 0, height1 * 0, width1 * 2, height1 * 1, chara01_face, true);

	//Tab(draw_tab);

	//Chara01_Tab(chara1_tab);


	DrawBox(0,0,width1*1,height1*1,gray,true);

	//DrawCardZone();
	DrawListZone();
	DrawDeckZone(); //選択されたカード（デッキの中身）

	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}

	DrawStringEx(1300, 60, -1, "X:%d Y:%d", MouseX, MouseY);
	DrawStringEx(480, 60, -1, "DeckCount:%d", c1deck_count);
	DrawStringEx(0,0,1,"戻る");

}


//関数
//tab描写用
void SceneDeckEdit::Tab(bool flag) {

	DrawGraph(width1 * 0, height1 / 2, t_chara, false);

	//chara_face
	DrawExtendGraph(width1 * 0, height1 * 1, width1 * 2, height1 * 2, chara01_face, false);
	DrawExtendGraph(width1 * 0, height1 * 2, width1 * 2, height1 * 3, chara02_face, false);
	DrawExtendGraph(width1 * 0, height1 * 3, width1 * 2, height1 * 4, chara03_face, false);
	DrawExtendGraph(width1 * 0, height1 * 4, width1 * 2, height1 * 5, chara04_face, false);
	//tab_flame
	DrawExtendGraph(width1 * 0, height1 * (1 + tab_flame_move), width1 * 2, height1 * (2 + tab_flame_move), tab_flame, true);

}

//tab操作関数群op
void SceneDeckEdit::opTab(bool flag) {

	if (flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			tab_flame_move -= 1;
		}
		else if (tab_flame_move < 0) {
			tab_flame_move = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			tab_flame_move += 1;
		}
		else if (tab_flame_move > 3) {
			tab_flame_move = 3;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && tab_flame_move == 0) {
			tab = false;
			chara1_tab = true;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && tab_flame_move == 1) {
			tab = false;
			chara2_tab = true;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && tab_flame_move == 2) {
			tab = false;
			chara3_tab = true;

		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && tab_flame_move == 3) {
			tab = false;
			chara4_tab = true;

		}
	}

}

//charaのtab描写用
//void SceneDeckEdit::Chara01_Tab(bool flag) {
//
//		DrawExtendGraph(width1 * 3, height1 * 1, width1 * 4, height1 * 3, c1deck[0], false);
//		DrawExtendGraph(width1 * 4, height1 * 1, width1 * 5, height1 * 3, c1deck[1], false);
//		DrawExtendGraph(width1 * 5, height1 * 1, width1 * 6, height1 * 3, c1deck[2], false);
//		DrawExtendGraph(width1 * 6, height1 * 1, width1 * 7, height1 * 3, c1deck[3], false);
//
//		DrawExtendGraph(width1 * 3, height1 * 3, width1 * 4, height1 * 5, c1deck[4], false);
//		DrawExtendGraph(width1 * 4, height1 * 3, width1 * 5, height1 * 5, c1deck[5], false);
//		DrawExtendGraph(width1 * 5, height1 * 3, width1 * 6, height1 * 5, c1deck[6], false);
//		DrawExtendGraph(width1 * 6, height1 * 3, width1 * 7, height1 * 5, c1deck[7], false);
//
//		DrawExtendGraph(width1 * 3, height1 * 5, width1 * 4, height1 * 7, c1deck[8], false);
//		DrawExtendGraph(width1 * 4, height1 * 5, width1 * 5, height1 * 7, c1deck[9], false);
//		DrawExtendGraph(width1 * 5, height1 * 5, width1 * 6, height1 * 7, c1deck[10], false);
//		DrawExtendGraph(width1 * 6, height1 * 5, width1 * 7, height1 * 7, c1deck[11], false);
//
//		DrawExtendGraph(width1 * 3, height1 * 7, width1 * 8, height1 * 9, c1deck[12], false);
//		DrawExtendGraph(width1 * 4, height1 * 7, width1 * 8, height1 * 9, c1deck[13], false);
//		DrawExtendGraph(width1 * 5, height1 * 7, width1 * 8, height1 * 9, c1deck[14], false);
//
//		DrawGraph(width1 * (2 + deck_fmove_x), height1 * (1 + deck_fmove_y), deck_flame, true);
//
//}


void SceneDeckEdit::DrawCardZone() {

}

void SceneDeckEdit::DrawDeckZone() {

	if (pmgr->person[0]->EDIT == true) {
		for (int i = 0; i < cmgr->chara1Deck.size(); ++i) {
			int x = i % 4;
			int y = i / 4;

			DrawExtendGraph(width1 * (3 + x), height1 * (1 + y * 2), width1 * (4 + x), height1 * (3 + y * 2), cmgr->chara1Deck[i]->c_graph, false);

		}
	}

	if (pmgr->person[1]->EDIT == true) {
		for (int i = 0; i < cmgr->chara2Deck.size(); ++i) {
			int x = i % 4;
			int y = i / 4;

			DrawExtendGraph(width1 * (3 + x), height1 * (1 + y * 2), width1 * (4 + x), height1 * (3 + y * 2), cmgr->chara2Deck[i]->c_graph, false);

		}

	}

	if (pmgr->person[2] ->EDIT == true) {
		for (int i = 0; i < cmgr->chara3Deck.size(); ++i) {
			int x = i % 4;
			int y = i / 4;

			DrawExtendGraph(width1 * (3 + x), height1 * (1 + y * 2), width1 * (4 + x), height1 * (3 + y * 2), cmgr->chara3Deck[i]->c_graph, false);

		}
	}

	if (pmgr->person[3]->EDIT == true) {
		for (int i = 0; i < cmgr->chara4Deck.size(); ++i) {
			int x = i % 4;
			int y = i / 4;

			DrawExtendGraph(width1 * (3 + x), height1 * (1 + y * 2), width1 * (4 + x), height1 * (3 + y * 2), cmgr->chara4Deck[i]->c_graph, false);

		}
	}

	//for (int i = 0; i < cmgr->chara1Deck.size(); ++i) {
	//	int x = i % 4;
	//	int y = i / 4;

	//	DrawExtendGraph(width1 * (3 + x), height1 * (1 + y * 2), width1 * (4 + x), height1 * (3 + y * 2), cmgr->chara1Deck[i]->c_graph, false);

	//}

}

void SceneDeckEdit::DrawListZone() {

	//TODO
	//枚数に応じて表示できるようにする
	//カードの実装の全体図ができるまでとばし
	

	if (pmgr->person[0]->EDIT == true) {
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, cmgr->cardDataChara1[0]->c_graph, false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, cmgr->cardDataChara1[1]->c_graph, false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, cmgr->cardDataChara1[2]->c_graph, false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, cmgr->cardDataChara1[3]->c_graph, false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, cmgr->cardDataChara1[4]->c_graph, false);

	}

	//if (pmgr->person2->EDIT == true) {
	//	DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, cmgr->cardDataChara2[0]->c_graph, false);
	//	DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, cmgr->cardDataChara2[1]->c_graph, false);
	//	DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, cmgr->cardDataChara2[2]->c_graph, false);
	//	DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, cmgr->cardDataChara2[3]->c_graph, false);
	//	DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, cmgr->cardDataChara2[4]->c_graph, false);

	//}

	if (pmgr->person[2]->EDIT == true) {
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, cmgr->cardDataChara3[0]->c_graph, false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, cmgr->cardDataChara3[1]->c_graph, false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, cmgr->cardDataChara3[2]->c_graph, false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, cmgr->cardDataChara3[3]->c_graph, false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, cmgr->cardDataChara3[4]->c_graph, false);

	}

	if (pmgr->person[3]->EDIT == true) {
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, cmgr->cardDataChara4[0]->c_graph, false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, cmgr->cardDataChara4[1]->c_graph, false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, cmgr->cardDataChara4[2]->c_graph, false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, cmgr->cardDataChara4[3]->c_graph, false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, cmgr->cardDataChara4[4]->c_graph, false);

	}
	


}




//選択されたカードのかぶりを監視しつつ、カードをデッキに挿入する関数
void SceneDeckEdit::CheckHandle(std::vector<Card*>& deck, Card* card) {


	int count = 0;
	for (auto d : deck) {
		if (d == card) count++;
	}
	if (count < 3) {
		deck.push_back(card);
	}


}

//グラフィック描写用
void SceneDeckEdit::LoadDeckEditGraph() {


}


void SceneDeckEdit::ListMouseCheck(int mx, int my) {

	//if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		

		if (pmgr->person[0]->EDIT == true) {

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[0]);
				CheckHandle(pmgr->person[0]->deck, cmgr->cardDataChara1[0]);

			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[1]);
			}

			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[2]);
			}

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[3]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[4]);
			}

		}

		if (pmgr->person[1]->EDIT == true) {

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[0]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[1]);
			}

			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[2]);
			}

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[3]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[4]);
			}

		}

		if (pmgr->person[2]->EDIT == true) {

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara3Deck, cmgr->cardDataChara3[0]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara3Deck, cmgr->cardDataChara3[1]);
			}

			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara3Deck, cmgr->cardDataChara3[2]);
			}

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara3Deck, cmgr->cardDataChara3[3]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara3Deck, cmgr->cardDataChara3[4]);
			}

		}
		
		if (pmgr->person[3]->EDIT == true) {

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[0]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[1]);
			}

			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
				CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[2]);
			}

			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[3]);
			}

			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
				CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[4]);
			}
		}
	}

}