#include "gm_scene_deckedit.h"
#include "gm_scene_selectphase.h"
#include <iostream>
#include <vector>

#include "gm_scene_battle.h"


void SceneDeckEdit::initialzie() {

	//tab�Ǘ��p�t���O
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

		if (0 < MouseX && MouseX < width1 * 1 && 0 < MouseY && MouseY < height1 * 1) {
			mgr->chengeScene(new SceneSelectPhase());
		}
	}

}

void SceneDeckEdit::render() {
	
	//SetFontSize(30);
	// 
	//���n(�w�i)
	DrawBox(0,0,width1*10,height1*10,white,true);
	//DrawBox(width1 * 0, height1 * 1, width1 * 3, height1 * 10, dsgray, true);
	//DrawBox(width1 * 3, height1 * 1, width1 * 7, height1 * 10, dimgray, true);
	//DrawBox(width1 * 7, height1 * 1, width1 * 10, height1 * 10, gray, true);
	DrawExtendGraph(width1 * 0, height1 * 0, width1 * 2, height1 * 1, chara01_face, true);

	//UIBOX
	DrawBox(10, height1 * 1 + 10, 286 , height1 * 10 - 10, ui, true); //�J�[�h�̕\��BOX
	DrawBox(296, height1 * 1 + 10, width1 * 6 + (width1 * 1 / 2), height1 * 10 - 10, ui, true); //�f�b�L�̕\��BOX
	DrawBox(width1 * 6 + (width1 * 1 / 2) + 10, height1 * 1 + 10, width1 * 10 -10, height1 * 10 - 10, ui, true); //CardList��BOX

	//view�֐��I�����ꂽ�J�[�h�̕\��
	DrawExtendGraph(20, height1 * 1 + 20, 276, height1 * 4 + 20, viewCard, false);


	DrawBox(0, 0, width1 * 1, height1 * 1, gray, true);
	
	//�J�[�h�̕\��
    DrawListZone(); //Person���������Ă���J�[�h�ꗗ
	DrawDeckZone(); //�I�����ꂽ�J�[�h�i�f�b�L�̒��g�j

	//�J�[�h�N���b�N�ō��ɃJ�[�h��傫���\��
	ClickDisPlayCardInDeck(pmgr->person,MouseX,MouseY);

	for (int i = 0; i < pmgr->person.size(); i++) {

		if (pmgr->person[i]->EDIT == true) {

			DrawStringEx(296, 60, 1, "DeckCount:%d/15", pmgr->person[i]->deck.size());

		}

	}

	DrawStringEx(296, 80, 1, "[Z]:�S�Ď�����");


	DrawStringEx(1300, 60, 1, "X:%d Y:%d", MouseX, MouseY);
	DrawStringEx(0, 0, 1, "�߂�");


	//�A�^����
	//for (int i = 0; i < 10; ++i) {
	//	DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
	//	DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	//}
}


//�֐�
//tab�`�ʗp
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

//tab����֐��Qop
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

//chara��tab�`�ʗp
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

	for (int i = 0; i < pmgr->person.size(); i++) { //�T��

		if (pmgr->person[i]->EDIT == true) {

			for (int k = 0; k < pmgr->person[i]->deck.size(); ++k) {

				int x = k % 4;
				int y = k / 4;

				int z = 10 * (k / 4);


				DrawExtendGraph((318 + (x * 20)) + (width1 * x), height1 * (1 + y * 2) + 20 + z, (318 + (x * 20)) + (width1 * (1 + x)), height1 * (3 + y * 2) + 20 + z, pmgr->person[i]->deck[k]->c_graph, false);

			}

		}

	}

}

void SceneDeckEdit::DrawListZone() {

	//TODO
	//�����ɉ����ĕ\���ł���悤�ɂ���
	//�J�[�h�̎����̑S�̐}���ł���܂łƂ΂�


	for (int i = 0; i < pmgr->person.size(); i++) { //Edit��TURE���ǂ����T��

		if (pmgr->person[i]->EDIT == true) { //Edit��TRUE��Person�̎��J�[�h���X�g��\��

			for (int k = 0; k < pmgr->person[i]->cardList.size(); k++) {

				int x = k % 3;
				int y = k / 3;
				int z = 12 * (k % 3);
				int q = 10 * (k / 3);

				//DrawExtendGraph(width1 * 6 + (width1 * 1 / 2) + 20, height1 * 1 + 20, width1 * 7 + (width1 * 1 / 2) + 20, height1 * 3 + 20, pmgr->person[i]->cardList[k]->c_graph, false);
				//DrawExtendGraph(width1 * (7 + x), height1 * (1 + y * 2), width1 * (8 + x), height1 * (3 + y * 2), pmgr->person[i]->cardList[k]->c_graph, false);


				DrawExtendGraph(width1 * (6 + x) + (width1 * 1 / 2) + 32 + z, height1 * (1 + y * 2) + 20 +q, width1 * (7 + x) + (width1 * 1 / 2) + 32 + z, height1 * (3 + y * 2) + 20 + q, pmgr->person[i]->cardList[k]->c_graph, false);
				//DrawExtendGraph(width1 * 6 + (width1 * 1 / 2) + 21, height1 * 1 + 20, width1 * 7 + (width1 * 1 / 2) + 31, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
				//DrawExtendGraph(width1 * 7 + (width1 * 1 / 2) + 43, height1 * 1 + 20, width1 * 8 + (width1 * 1 / 2) + 43, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
				//DrawExtendGraph(width1 * 8 + (width1 * 1 / 2) + 56, height1 * 1 + 20, width1 * 9 + (width1 * 1 / 2) + 56, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
			}


		}

	}

}


//�I�����ꂽ�J�[�h�̂��Ԃ���Ď����A�J�[�h���f�b�L�ɑ}������֐�
void SceneDeckEdit::CheckHandle(std::vector<Card*>& deck, Card* card) {


	int count = 0;
	for (auto d : deck) {
		if (d == card) count++;
	}
	if (count < 3) {
		deck.push_back(card);
	}


}

//�O���t�B�b�N�`�ʗp
void SceneDeckEdit::LoadDeckEditGraph() {


}


//TODO
//Person���ɐE�Ƃ��Ƃ̃J�[�h�f�[�^����������for���ŉ񂹂�悤�ɂ���
void SceneDeckEdit::ListMouseCheck(int mx, int my) {

	for (int i = 0; i < pmgr->person.size(); i++) {

		if (pmgr->person[i]->EDIT == true) {

			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

				if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
					//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[0]);
					CheckHandle(pmgr->person[i]->deck, pmgr->person[i]->cardList[0]);

				}

				if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
					//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[1]);
					CheckHandle(pmgr->person[i]->deck, pmgr->person[i]->cardList[1]);

				}

				if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
					//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[2]);
					CheckHandle(pmgr->person[i]->deck, pmgr->person[i]->cardList[2]);

				}

				if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
					//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[3]);
					CheckHandle(pmgr->person[i]->deck, pmgr->person[i]->cardList[3]);

				}

				if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
					//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[4]);
					CheckHandle(pmgr->person[i]->deck, pmgr->person[i]->cardList[4]);

				}
			}

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {

				pmgr->person[i]->deck.erase(pmgr->person[i]->deck.begin(), pmgr->person[i]->deck.end());
			}

		}

	}


}

void SceneDeckEdit::ClickDisPlayCardInDeck(std::vector<Person*> &person, int mx, int my) {

	for (int i = 0; i < person.size(); i++) {

		if (person[i]->EDIT == true) {

			for (int k = 0; k < pmgr->person[i]->deck.size(); k++) {

					int x = k % 4;
					int y = k / 4;

					int z = 10 * (k / 4);

					if ((318 + (x * 20)) + (width1 * x) < mx && mx < (318 + (x * 20)) + (width1 * (1 + x)) && height1 * (1 + y * 2) + 20 + z < my && my < height1 * (3 + y * 2) + 20 + z) {

						if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

							viewCard = pmgr->person[i]->deck[k]->c_graph;

						}
						
					}

			}



		}


	}


}


//memo(���������R�[�h�Ȃ�)

	//	//if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
	//	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
	//		
	//
	//		if (pmgr->person[0]->EDIT == true) {
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
	////				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[0]);
	//				CheckHandle(pmgr->person[0]->deck, cmgr->cardDataChara1[0]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
	////				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[1]);
	//				CheckHandle(pmgr->person[0]->deck, cmgr->cardDataChara1[1]);
	//
	//			}
	//
	//		if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
	////				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[2]);
	//				CheckHandle(pmgr->person[0]->deck, cmgr->cardDataChara1[2]);
	//
	//			}
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
	////				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[3]);
	//				CheckHandle(pmgr->person[0]->deck, cmgr->cardDataChara1[3]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
	////				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara1[4]);
	//				CheckHandle(pmgr->person[0]->deck, cmgr->cardDataChara1[4]);
	//
	//			}
	//
	//		}
	//
	//		if (pmgr->person[1]->EDIT == true) {
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
	////				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[0]);
	//				CheckHandle(pmgr->person[1]->deck, cmgr->cardDataChara2[1]);
	//
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
	//	//			CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[1]);
	//				CheckHandle(pmgr->person[1]->deck, cmgr->cardDataChara2[1]);
	//
	//			}
	//
	//			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
	////				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[2]);
	//				CheckHandle(pmgr->person[1]->deck, cmgr->cardDataChara2[2]);
	//
	//			}
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
	//	//			CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[3]);
	//				CheckHandle(pmgr->person[1]->deck, cmgr->cardDataChara2[3]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
	////				CheckHandle(cmgr->chara2Deck, cmgr->cardDataChara2[4]);
	//				CheckHandle(pmgr->person[1]->deck, cmgr->cardDataChara2[4]);
	//
	//			}
	//
	//		}
	//
	//		if (pmgr->person[2]->EDIT == true) {
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
	//	//			CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara3[0]);
	//				CheckHandle(pmgr->person[2]->deck, cmgr->cardDataChara3[0]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
	////				CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara3[1]);
	//				CheckHandle(pmgr->person[2]->deck, cmgr->cardDataChara3[1]);
	//
	//			}
	//
	//			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
	//				//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara3[2]);
	//				CheckHandle(pmgr->person[2]->deck, cmgr->cardDataChara3[2]);
	//
	//			}
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
	//				//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara3[3]);
	//				CheckHandle(pmgr->person[2]->deck, cmgr->cardDataChara3[3]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
	//				//CheckHandle(cmgr->chara1Deck, cmgr->cardDataChara3[4]);
	//				CheckHandle(pmgr->person[2]->deck, cmgr->cardDataChara3[4]);
	//
	//			}
	//
	//		}
	//		
	//		if (pmgr->person[3]->EDIT == true) {
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 1 < my && my < height1 * 3) {
	//				//CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[0]);
	//				CheckHandle(pmgr->person[3]->deck, cmgr->cardDataChara4[0]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 1 < my && my < height1 * 3) {
	//				//CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[1]);
	//				CheckHandle(pmgr->person[3]->deck, cmgr->cardDataChara4[1]);
	//
	//			}
	//
	//			if (width1 * 9 < mx && mx < width1 * 10 && height1 * 1 < my && my < height1 * 3) {
	//				//CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[2]);
	//				CheckHandle(pmgr->person[3]->deck, cmgr->cardDataChara4[2]);
	//
	//			}
	//
	//			if (width1 * 7 < mx && mx < width1 * 8 && height1 * 3 < my && my < height1 * 5) {
	//				//CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[3]);
	//				CheckHandle(pmgr->person[3]->deck, cmgr->cardDataChara4[3]);
	//
	//			}
	//
	//			if (width1 * 8 < mx && mx < width1 * 9 && height1 * 3 < my && my < height1 * 5) {
	//				//CheckHandle(cmgr->chara4Deck, cmgr->cardDataChara4[4]);
	//				CheckHandle(pmgr->person[3]->deck, cmgr->cardDataChara4[4]);
	//
	//			}
	//		}
	//	}



	//DrawExtendGraph(20, height1 * 1 + 20, 276, height1 * 4 + 20,pmgr->person[0]->cardList[0]->c_graph,false);

	//DrawExtendGraph(318, height1 * 1 + 20, 318 + width1 * 1, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(338 + width1 * 1, height1 * 1 + 20, 338 + width1 * 2, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(358 + width1 * 2, height1 * 1 + 20, 358 + width1 * 3, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(378 + width1 * 3, height1 * 1 + 20, 378 + width1 * 4, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(346 + width1 * 4, height1 * 1 + 20, 356 + width1 * 5, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(306 + width1 * 5, height1 * 1 + 20, 366 + width1 * 6, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);

	//DrawExtendGraph(width1 * 6 + (width1 * 1 / 2) + 21, height1 * 1 + 20, width1 * 7 + (width1 * 1 / 2) + 31, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(width1 * 7 + (width1 * 1 / 2) + 43, height1 * 1 + 20, width1 * 8 + (width1 * 1 / 2) + 43, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
	//DrawExtendGraph(width1 * 8 + (width1 * 1 / 2) + 56, height1 * 1 + 20, width1 * 9 + (width1 * 1 / 2) + 56, height1 * 3 + 20, pmgr->person[0]->cardList[0]->c_graph, false);
