#include "gm_scene_deckedit.h"
#include "gm_scene_selectphase.h"
#include <iostream>
#include <vector>

void SceneDeckEdit::initialzie() {
	LoadDeckEditGraph();

	//tab管理用フラグ
	tab = true;
	draw_tab = true;
	chara1_tab = false;
	chara2_tab = false;
	chara3_tab = false;
	chara4_tab = false;

}

void SceneDeckEdit::update(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		mgr->chengeScene(new SceneSelectPhase());
	}

	//tab操作用関数群
	opTab(tab);
	opChara01_Tab(chara1_tab);
	opChara02_Tab(chara2_tab);
	opChara03_Tab(chara3_tab);
	opChara04_Tab(chara4_tab);

}

void SceneDeckEdit::render() {

	DrawBox(0, 0, width1 * 10, height1 * 10, white, true);

	Tab(draw_tab);

	Chara01_Tab(chara1_tab);
	Chara02_Tab(chara2_tab);
	Chara03_Tab(chara3_tab);
	Chara04_Tab(chara4_tab);

	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}
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

void SceneDeckEdit::opChara01_Tab(bool flag) {
	if (flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			deck_fmove_x += 1;
		}
		else if (deck_fmove_x > 3) {
			deck_fmove_x = 3;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			deck_fmove_x -= 1;
		}
		else if (deck_fmove_x < 0) {
			deck_fmove_x = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			deck_fmove_y -= 2;
		}
		else if (deck_fmove_y < 0) {
			deck_fmove_y = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			deck_fmove_y += 2;
		}
		else if (deck_fmove_y > 6) {
			deck_fmove_y = 6;
		}


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {

			if (deck_fmove_x == 0 && deck_fmove_y == 0) {
				CheckHandle(c1deck, c1_d1);
			}
			else if (deck_fmove_x == 1 && deck_fmove_y == 0) {
				CheckHandle(c1deck, c1_d2);
			}
			else if (deck_fmove_x == 2 && deck_fmove_y == 0) {
				CheckHandle(c1deck, c1_d3);
			}
			else if (deck_fmove_x == 3 && deck_fmove_y == 0) {
				CheckHandle(c1deck, c1_d4);
			}
			else if (deck_fmove_x == 0 && deck_fmove_y == 2) {
				CheckHandle(c1deck, c1_d5);
			}

			c1deck_count += 1;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {

			for (int i = 0; i < 10; ++i) {
				c1deck[i] = 0;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
			chara1_tab = false;
			tab = true;
		}

	}


}

void SceneDeckEdit::opChara02_Tab(bool flag) {
	if (flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			deck_fmove_x += 1;
		}
		else if (deck_fmove_x > 3) {
			deck_fmove_x = 3;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			deck_fmove_x -= 1;
		}
		else if (deck_fmove_x < 0) {
			deck_fmove_x = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			deck_fmove_y -= 2;
		}
		else if (deck_fmove_y < 0) {
			deck_fmove_y = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			deck_fmove_y += 2;
		}
		else if (deck_fmove_y > 6) {
			deck_fmove_y = 6;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
			
			if (deck_fmove_x == 0 && deck_fmove_y == 0) {
				CheckHandle(c2deck, c2_d1);
			}
			else if (deck_fmove_x == 1 && deck_fmove_y == 0) {
				CheckHandle(c2deck, c2_d1);
			}
			else if (deck_fmove_x == 2 && deck_fmove_y == 0) {
				CheckHandle(c2deck, c2_d1);
			}
			else if (deck_fmove_x == 3 && deck_fmove_y == 0) {
				CheckHandle(c2deck, c2_d1);
			}
			else if (deck_fmove_x == 0 && deck_fmove_y == 2) {
				CheckHandle(c2deck, c2_d1);
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {

			for (int i = 0; i < 10; ++i) {
				c2deck[i] = 0;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
			chara2_tab = false;
			tab = true;
		}
	}
}

void SceneDeckEdit::opChara03_Tab(bool flag) {
	if (flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			deck_fmove_x += 1;
		}
		else if (deck_fmove_x > 3) {
			deck_fmove_x = 3;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			deck_fmove_x -= 1;
		}
		else if (deck_fmove_x < 0) {
			deck_fmove_x = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			deck_fmove_y -= 2;
		}
		else if (deck_fmove_y < 0) {
			deck_fmove_y = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			deck_fmove_y += 2;
		}
		else if (deck_fmove_y > 6) {
			deck_fmove_y = 6;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {

			if (deck_fmove_x == 0 && deck_fmove_y == 0) {
				CheckHandle(c3deck, c3_d1);
			}
			else if (deck_fmove_x == 1 && deck_fmove_y == 0) {
				CheckHandle(c3deck, c3_d2);
			}
			else if (deck_fmove_x == 2 && deck_fmove_y == 0) {
				CheckHandle(c3deck, c3_d3);
			}
			else if (deck_fmove_x == 3 && deck_fmove_y == 0) {
				CheckHandle(c3deck, c3_d4);
			}
			else if (deck_fmove_x == 0 && deck_fmove_y == 2) {
				CheckHandle(c3deck, c3_d5);
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {

			for (int i = 0; i < 10; ++i) {
				c3deck[i] = 0;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
			chara3_tab = false;
			tab = true;
		}
	}
}

void SceneDeckEdit::opChara04_Tab(bool flag) {
	if (flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			deck_fmove_x += 1;
		}
		else if (deck_fmove_x > 3) {
			deck_fmove_x = 3;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			deck_fmove_x -= 1;
		}
		else if (deck_fmove_x < 0) {
			deck_fmove_x = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			deck_fmove_y -= 2;
		}
		else if (deck_fmove_y < 0) {
			deck_fmove_y = 0;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			deck_fmove_y += 2;
		}
		else if (deck_fmove_y > 6) {
			deck_fmove_y = 6;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {

			if (deck_fmove_x == 0 && deck_fmove_y == 0) {
				CheckHandle(c4deck, c4_d1);
			}
			else if (deck_fmove_x == 1 && deck_fmove_y == 0) {
				CheckHandle(c4deck, c4_d2);
			}
			else if (deck_fmove_x == 2 && deck_fmove_y == 0) {
				CheckHandle(c4deck, c4_d3);
			}
			else if (deck_fmove_x == 3 && deck_fmove_y == 0) {
				CheckHandle(c4deck, c4_d4);
			}
			else if (deck_fmove_x == 0 && deck_fmove_y == 2) {
				CheckHandle(c4deck, c4_d5);
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {

			for (int i = 0; i < 10; ++i) {
				c4deck[i] = 0;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
			chara4_tab = false;
			tab = true;
		}
	}
}


//charaのtab描写用
void SceneDeckEdit::Chara01_Tab(bool flag) {

	if (flag) {
		DrawGraph(width1 * 2, height1 / 2, t_deckedit, false);
		DrawGraph(width1 * 6, height1 / 2, t_deck, false);

		DrawBox(width1 * 2, height1 * 1, width1 * 10, height1 * 10, gray, true);
		DrawBox(width1 * 2, height1 * 1, width1 * 6, height1 * 10, dimgray, true);



		DrawExtendGraph(width1 * 2, height1 * 1, width1 * 3, height1 * 3, c1_d1, false);
		DrawExtendGraph(width1 * 3, height1 * 1, width1 * 4, height1 * 3, c1_d2, false);
		DrawExtendGraph(width1 * 4, height1 * 1, width1 * 5, height1 * 3, c1_d3, false);
		DrawExtendGraph(width1 * 5, height1 * 1, width1 * 6, height1 * 3, c1_d4, false);
		DrawExtendGraph(width1 * 2, height1 * 3, width1 * 3, height1 * 5, c1_d5, false);



		DrawExtendGraph(width1 * 6, height1 * 1, width1 * 7, height1 * 3, c1deck[0], false);
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, c1deck[1], false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, c1deck[2], false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, c1deck[3], false);

		DrawExtendGraph(width1 * 6, height1 * 3, width1 * 7, height1 * 5, c1deck[4], false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, c1deck[5], false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, c1deck[6], false);
		DrawExtendGraph(width1 * 9, height1 * 3, width1 * 10, height1 * 5, c1deck[7], false);

		DrawExtendGraph(width1 * 6, height1 * 5, width1 * 7, height1 * 7, c1deck[8], false);
		DrawExtendGraph(width1 * 7, height1 * 5, width1 * 8, height1 * 7, c1deck[9], false);



		DrawGraph(width1 * (2 + deck_fmove_x), height1 * (1 + deck_fmove_y), deck_flame, true);

	}

}

void SceneDeckEdit::Chara02_Tab(bool flag) {

	if (flag) {
		DrawGraph(width1 * 2, height1 / 2, t_deckedit, false);
		DrawGraph(width1 * 6, height1 / 2, t_deck, false);

		DrawBox(width1 * 2, height1 * 1, width1 * 10, height1 * 10, gray, true);
		DrawBox(width1 * 2, height1 * 1, width1 * 6, height1 * 10, dimgray, true);

		DrawExtendGraph(width1 * 2, height1 * 1, width1 * 3, height1 * 3, c2_d1, false);
		DrawExtendGraph(width1 * 3, height1 * 1, width1 * 4, height1 * 3, c2_d1, false);
		DrawExtendGraph(width1 * 4, height1 * 1, width1 * 5, height1 * 3, c2_d1, false);
		DrawExtendGraph(width1 * 5, height1 * 1, width1 * 6, height1 * 3, c2_d1, false);
		DrawExtendGraph(width1 * 2, height1 * 3, width1 * 3, height1 * 5, c2_d1, false);

		DrawExtendGraph(width1 * 6, height1 * 1, width1 * 7, height1 * 3, c2deck[0], false);
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, c2deck[1], false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, c2deck[2], false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, c2deck[3], false);

		DrawExtendGraph(width1 * 6, height1 * 3, width1 * 7, height1 * 5, c2deck[4], false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, c2deck[5], false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, c2deck[6], false);
		DrawExtendGraph(width1 * 9, height1 * 3, width1 * 10, height1 * 5, c2deck[7], false);

		DrawExtendGraph(width1 * 6, height1 * 5, width1 * 7, height1 * 7, c2deck[8], false);
		DrawExtendGraph(width1 * 7, height1 * 5, width1 * 8, height1 * 7, c2deck[9], false);


		DrawGraph(width1 * (2 + deck_fmove_x), height1 * (1 + deck_fmove_y), deck_flame, true);



	}

}

void SceneDeckEdit::Chara03_Tab(bool flag) {

	if (flag) {
		DrawGraph(width1 * 2, height1 / 2, t_deckedit, false);
		DrawGraph(width1 * 6, height1 / 2, t_deck, false);

		DrawBox(width1 * 2, height1 * 1, width1 * 10, height1 * 10, gray, true);
		DrawBox(width1 * 2, height1 * 1, width1 * 6, height1 * 10, dimgray, true);

		DrawExtendGraph(width1 * 2, height1 * 1, width1 * 3, height1 * 3, c3_d1, false);
		DrawExtendGraph(width1 * 3, height1 * 1, width1 * 4, height1 * 3, c3_d2, false);
		DrawExtendGraph(width1 * 4, height1 * 1, width1 * 5, height1 * 3, c3_d3, false);
		DrawExtendGraph(width1 * 5, height1 * 1, width1 * 6, height1 * 3, c3_d4, false);
		DrawExtendGraph(width1 * 2, height1 * 3, width1 * 3, height1 * 5, c3_d5, false);

		DrawExtendGraph(width1 * 6, height1 * 1, width1 * 7, height1 * 3, c3deck[0], false);
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, c3deck[1], false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, c3deck[2], false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, c3deck[3], false);

		DrawExtendGraph(width1 * 6, height1 * 3, width1 * 7, height1 * 5, c3deck[4], false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, c3deck[5], false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, c3deck[6], false);
		DrawExtendGraph(width1 * 9, height1 * 3, width1 * 10, height1 * 5, c3deck[7], false);

		DrawExtendGraph(width1 * 6, height1 * 5, width1 * 7, height1 * 7, c3deck[8], false);
		DrawExtendGraph(width1 * 7, height1 * 5, width1 * 8, height1 * 7, c3deck[9], false);


		DrawGraph(width1 * (2 + deck_fmove_x), height1 * (1 + deck_fmove_y), deck_flame, true);

		

	}

}

void SceneDeckEdit::Chara04_Tab(bool flag) {

	if (flag) {
		DrawGraph(width1 * 2, height1 / 2, t_deckedit, false);
		DrawGraph(width1 * 6, height1 / 2, t_deck, false);

		DrawBox(width1 * 2, height1 * 1, width1 * 10, height1 * 10, gray, true);
		DrawBox(width1 * 2, height1 * 1, width1 * 6, height1 * 10, dimgray, true);

		DrawExtendGraph(width1 * 2, height1 * 1, width1 * 3, height1 * 3, c4_d1, false);
		DrawExtendGraph(width1 * 3, height1 * 1, width1 * 4, height1 * 3, c4_d2, false);
		DrawExtendGraph(width1 * 4, height1 * 1, width1 * 5, height1 * 3, c4_d3, false);
		DrawExtendGraph(width1 * 5, height1 * 1, width1 * 6, height1 * 3, c4_d4, false);
		DrawExtendGraph(width1 * 2, height1 * 3, width1 * 3, height1 * 5, c4_d5, false);

		DrawExtendGraph(width1 * 6, height1 * 1, width1 * 7, height1 * 3, c4deck[0], false);
		DrawExtendGraph(width1 * 7, height1 * 1, width1 * 8, height1 * 3, c4deck[1], false);
		DrawExtendGraph(width1 * 8, height1 * 1, width1 * 9, height1 * 3, c4deck[2], false);
		DrawExtendGraph(width1 * 9, height1 * 1, width1 * 10, height1 * 3, c4deck[3], false);

		DrawExtendGraph(width1 * 6, height1 * 3, width1 * 7, height1 * 5, c4deck[4], false);
		DrawExtendGraph(width1 * 7, height1 * 3, width1 * 8, height1 * 5, c4deck[5], false);
		DrawExtendGraph(width1 * 8, height1 * 3, width1 * 9, height1 * 5, c4deck[6], false);
		DrawExtendGraph(width1 * 9, height1 * 3, width1 * 10, height1 * 5, c4deck[7], false);

		DrawExtendGraph(width1 * 6, height1 * 5, width1 * 7, height1 * 7, c4deck[8], false);
		DrawExtendGraph(width1 * 7, height1 * 5, width1 * 8, height1 * 7, c4deck[9], false);


		DrawGraph(width1 * (2 + deck_fmove_x), height1 * (1 + deck_fmove_y), deck_flame, true);



	}

}

//選択されたカードのかぶりを監視する関数
void SceneDeckEdit::CheckHandle(std::array<int, 10>& ary, int new_handle) {
	
	if (std::count(ary.begin(),ary.end(),new_handle) < 3) {
		for (size_t i = 0; i < ary.size(); ++i) {
			if (ary[i]) {
				continue;
			}
			ary[i] = new_handle;
			return;
		}
	}
}

//グラフィック描写用
void SceneDeckEdit::LoadDeckEditGraph() {
	chara01_face = LoadGraph("graphics/chara1_face.png");
	chara02_face = LoadGraph("graphics/chara2_face.png");
	chara03_face = LoadGraph("graphics/chara3_face.png");
	chara04_face = LoadGraph("graphics/chara4_face.png");


	tab_flame = LoadGraph("graphics/x2_y1_flame_R.png");
	deck_flame = LoadGraph("graphics/deck_flame.png");

	t_chara = LoadGraph("graphics/edit_chara.png");
	t_deckedit = LoadGraph("graphics/edit_deckedit.png");
	t_deck = LoadGraph("graphics/edit_deck.png");

	c1_d1 = LoadGraph("graphics/card_1.png");
	c1_d2 = LoadGraph("graphics/card_2.png");
	c1_d3 = LoadGraph("graphics/card_3.png");
	c1_d4 = LoadGraph("graphics/card_6.png");
	c1_d5 = LoadGraph("graphics/card_7.png");

	c2_d1 = LoadGraph("graphics/card_2.png");
	c2_d2 = LoadGraph("graphics/card_2.png");
	c2_d3 = LoadGraph("graphics/card_2.png");
	c2_d4 = LoadGraph("graphics/card_2.png");
	c2_d5 = LoadGraph("graphics/card_2.png");

	c3_d1 = LoadGraph("graphics/card_4.png");
	c3_d2 = LoadGraph("graphics/card_10.png");
	c3_d3 = LoadGraph("graphics/card_15.png");
	c3_d4 = LoadGraph("graphics/card_11.png");
	c3_d5 = LoadGraph("graphics/card_14.png");

	c4_d1 = LoadGraph("graphics/card_8.png");
	c4_d2 = LoadGraph("graphics/card_9.png");
	c4_d3 = LoadGraph("graphics/card_12.png");
	c4_d4 = LoadGraph("graphics/card_13.png");
	c4_d5 = LoadGraph("graphics/card_5.png");

}