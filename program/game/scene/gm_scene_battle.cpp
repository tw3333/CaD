#include "gm_scene_battle.h"

#include <iostream>
#include <cmath>
#include <random>

#include "gm_scene_charaedit.h"
#include "../gm_person_manager.h"
#include "../gm_card_manager.h"
#include "../gm_enemy.h"
#include "DxLib.h"

#include "../gm_manager.h"
#include "gm_scene_result.h"

SceneBattle::~SceneBattle() {



	//	for (auto& unit : allUnit) { delete unit; }
	//	for (auto& person : party) { delete person; }
	//	for (auto& enemy : enemies) { delete enemy; }

	for (int i = 0; i < pmgr->person.size(); i++) { pmgr->person[i]->isFirstDeal = false; }

}


void SceneBattle::initialzie() {

	LoadBattleGraph();

	enemy_anime = true;
	chara_num = 1;
	img_turn_move = 25;

	//===初期化時点で１番目の行動unitを決める===//

	SetParty(pmgr->person, party); //pickからpersonを選出

	enemies.emplace_back(enemy1); //とりあえずの敵

	//基底クラスunitの配列に敵と味方を入れる
	for (const auto& p : party) {
		allUnit.push_back(p);
	}
	for (const auto& e : enemies) {
		allUnit.push_back(e);
	}

	//SPEEDの値で降順ソート
	std::sort(allUnit.begin(), allUnit.end(), [](Unit* a, Unit* b) {
		return a->getSPEED() > b->getSPEED();
		});

	//ReflectOrderImage(); //画像を行動順に描写

	orderCount = 0;

	if (allUnit[orderCount]->getIsEnemy() == false) {

		doPerson = static_cast<Person*>(allUnit[orderCount]);
		isDecideOrdered = true;

	}
	else if (allUnit[orderCount]->getIsEnemy() == true) {

		doEnemy = static_cast<Enemy*>(allUnit[orderCount]);
		isDecideOrdered = true;
	}

	//=========================================//


}

void SceneBattle::update(float dalta_time) {

	GameManager* mgr = GameManager::GetInstance();

	//マウス座標の取得
	GetMousePoint(&MouseX, &MouseY);


	//ボタンの処理
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

		if (10 < MouseX && MouseX < width1 * 2 - 10 && height1 * 7 + 60 < MouseY && MouseY < height1 * 8 + 25) {

			if (isDealCard == false && dealCardPhase == false) { //カードをdealする

				PlaySoundMem(smgr->dealCard_se, DX_PLAYTYPE_BACK);
				dealCardPhase = true;

			}

			if (isDealCard == true && actionPhase == true) { //Turnを終わりにする

				turnEndPhase = true;

			}

		}
	}

	//===1ターンの処理===//

	if (isDecideOrdered) {

		if (allUnit[orderCount]->getIsEnemy() == false) {

			if (dealCardPhase) {

				DealFromDeckToHand(doPerson->deck, doPerson->hand, doPerson->dealHandNum);

				isDealCard = true;
				actionPhase = true;

				dealCardPhase = false;
			}

			if (actionPhase) {

				UseCardFromHand(doPerson, doPerson->hand, MouseX, MouseY);
				for (int i = 0; i < enemies.size(); i++) {

					if (enemies[i]->HP == 0) {
						enemies[i]->setIsDead(true);
					}

				}

			}

			if (turnEndPhase) {

				actionPhase = false;
				isDealCard = false;

				isDecideOrdered = false;
				decideOrderPhase = true;

				turnEndPhase = false;
			}

		}
		else if (allUnit[orderCount]->getIsEnemy() == true) {

			doEnemy->EnemyAct(doEnemy, party);
			for (int i = 0; i < party.size(); i++) {

				if (party[i]->HP == 0) {

					party[i]->setIsDead(true);
				}

			}


			isDecideOrdered = false;
			decideOrderPhase = true;
			costReset = true;
		}

		bool all_dead = std::all_of(enemies.begin(), enemies.end(), []( Enemy* e) { return e->getIsDead(); });

		if (all_dead) {

			mgr->chengeScene(new SceneResult());

		}

		if (costReset) {

			for (int i = 0; i < party.size(); i++) {

				party[i]->COST = party[i]->COSTMAX;

			}
			costReset = false;

		}

	}

	

	if (!isDecideOrdered && decideOrderPhase) {
		
		orderCount += 1;

		if (orderCount > allUnit.size() - 1) {

			std::sort(allUnit.begin(), allUnit.end(), [](Unit* a, Unit* b) {
				return a->getSPEED() > b->getSPEED();
				});

			turnCount += 1;
			orderCount = 0;

		}

		if (allUnit[orderCount]->getIsDead() == false) {

			if (allUnit[orderCount]->getIsEnemy() == false) {

				doPerson = static_cast<Person*>(allUnit[orderCount]);
				isDecideOrdered = true;

			}
			else if (allUnit[orderCount]->getIsEnemy() == true) {

				doEnemy = static_cast<Enemy*>(allUnit[orderCount]);
				isDecideOrdered = true;
			}

		}

		decideOrderPhase = false;
	}

	//===================//

		//簡易敵アニメーション 
	timer += 0.1 * 1;
	move += 2 * sin(timer);

	//マウス座標の取得
//	GetMousePoint(&MouseX, &MouseY); //マウス座標の取得

	RaiseCard(doPerson->hand, MouseX, MouseY);

	//シーン切り替え
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		//chara_num += 1;
		select_move += 2;

	}
	else if (select_move <= 0) {
		//select_move = 0;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		//chara_num -= 1;
		select_move -= 2;
	}
	else if (select_move >= 8) {
		select_move = 8;
	}

	switch (chara_num) {
	case 1:
		chara_select = img_chara1_face;
		break;

	case 2:
		chara_select = img_chara2_face;
		break;

	case 3:
		chara_select = img_chara3_face;
		break;

	case 4:
		chara_select = img_chara4_face;
		break;

	}


	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_H)) {
	//	hp_now -= 1;
	//	your_turn = true;
	//}

	//test
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
		dealcard = true;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_U)) {
		numOfCards += 1;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) {
		numOfCards -= 1;
	}
	else if (numOfCards > 10) {
		numOfCards = 10;
	}

	t += dt;
	if (1 <= t) {
		t = 1;
	}
	d_t += 0.1;

	if (1 <= d_t) {
		d_t = 1;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_T)) {
		t = 0;
		d_t = 0;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S)) {
		t = 0;
		startTurn = true;
	}



}

void SceneBattle::render() {

	//=====描写=====//

	//背景
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, height1 * 10, img_background, true);

	//敵
	//DrawBox(width1 * 4, height1, width1 * 6, height1 * 5, GetColor(138, 140, 142), false);
	DrawExtendGraph(width1 * 4, height1 + move, width1 * 6, height1 * 5 + move, img_mon1, false);

	//DrawLine(0,height1,DXE_WINDOW_WIDTH,height1,0);

	//グリッドライン
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}

	//drawMouseUp(MouseX, MouseY);

	//行動順ぎめ
	//DrawBox(0, 0, width1 * 2, height1 * 4, red, false);

	//ターンの画像//
	//DrawGraph(0, 0, img_turn, false);

	//DrawLine(0,height1*2, width1*4, height1* 2,red);

	//手札描写
//	DrawHand(doPerson->hand);

	DrawBox(0, height1 * 7, width1 * 2, height1 * 10, Silver, true);

	//ターン描写
	//DrawExtendGraph(width1*4,height1*3,width1*6,height1*4,img_yourturn,true);

	//EaseTurnImage(easeOutExpo(t), 0, width1 * 4);
	//EaseTurnImage(easeInExpo(t), width1*4, width1 * 10);

	DrawTurn();

	DrawOrder();

	//選択フレーム
	//DrawCard(0 + select_move, 7, 2 + select_move, 10, select_flame, true);

	//カード置き場
	//DrawBox(0, height1 * 7, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, GetColor(138, 140, 142), false);

	//カード説明描写
	DrawBox(width1 * 8, height1 * 1, width1 * 10, height1 * 6, black, true);


	DrawStringEx(1300, 20, -1, "scene battle");
	DrawStringEx(1300, 40, -1, "%d", select_move);
	DrawStringEx(1300, 60, -1, "X:%d Y:%d", MouseX, MouseY);
	//DrawStringEx(10, height1 * 7, 1, "HP:%d/%d", doPerson->HP,doPerson->HPMAX);
	//DrawStringEx(10, height1 * 7 + 40, 1, "Cost:%d/%d", doPerson->COST, doPerson->COSTMAX);

	//HPbarの描画
	//DrawHpBar(doPerson->HP, doPerson->HPMAX);

	//ボタン描画
	DrawBox(10, height1 * 7 + 60, width1 * 2 - 10, height1 * 8 + 25, black, false); //draw or turnEndのボタン
	DrawBox(10, height1 * 8 + 30, width1 * 2 - 10, height1 * 9, black, false); //skillのボタン
	DrawBox(10, height1 * 9 + 10, width1 * 1 - 5, height1 * 10 - 10, black, false); //道具のボタン
	DrawBox(width1 * 1 + 5, height1 * 9 + 10, width1 * 2 - 10, height1 * 10 - 10, black, false); //逃げるのボタン


	//debug
	DrawStringEx(width1 * 4, 0, -1, "HP:%d/%d", enemy1->HP, enemy1->HPMAX);
	
	DrawStringEx(width1 * 8, height1 * 2, -1, "%d", party[0]->SPEED);
	DrawStringEx(width1 * 8, height1 * 2 + 15, -1, "%d", party[1]->SPEED);
	DrawStringEx(width1 * 8, height1 * 2 + 30, -1, "%d", party[2]->SPEED);

	//DrawStringEx(width1 * 9, height1 * 2, -1, "%d", allUnit[0]->getIsEnemy());
	//DrawStringEx(width1 * 9, height1 * 2 + 15, -1, "%d", allUnit[1]->getIsEnemy());
	//DrawStringEx(width1 * 9, height1 * 2 + 30, -1, "%d", allUnit[2]->getIsEnemy());
	//DrawStringEx(width1 * 9, height1 * 2 + 45, -1, "%d", allUnit[3]->getIsEnemy());

	if (doPerson != nullptr) {

		DrawHpBar(doPerson->HP, doPerson->HPMAX);
		DrawHand(doPerson->hand);

		DrawStringEx(10, height1 * 7, 1, "HP:%d/%d", doPerson->HP, doPerson->HPMAX);
		DrawStringEx(10, height1 * 7 + 40, 1, "Cost:%d/%d", doPerson->COST, doPerson->COSTMAX);
		//DrawStringEx(60, height1 * 7 + 40, 1, "Deck:%d/%d", doPerson->deck.size(), doPerson->COSTMAX);


		//DrawStringEx(width1 * 9, height1 * 4 + 45, -1, "doPersonSpeed:%d", doPerson->SPEED);
		//DrawStringEx(width1 * 9 - 100, height1 * 4 + 60, -1, "allUnit[0]IsActed:%d", allUnit[0]->getIsActed());
		//DrawStringEx(width1 * 9, height1 * 4 + 75, -1, "IsDead%d", doPerson->getIsDead());
		//DrawStringEx(width1 * 9, height1 * 4 + 90, -1, "IsEnemy%d", doPerson->getIsEnemy());
		//DrawStringEx(width1 * 9, height1 * 4 + 105, -1, "TurnCount:%d", turnCount);
		//DrawStringEx(width1 * 9 - 100, height1 * 4 + 120, -1, "allUnit[1]:%d", allUnit[1]->getIsActed());
		//DrawStringEx(width1 * 9 - 100, height1 * 4 + 135, -1, "orderCount:%d", orderCount);

		//行動キャラ表示
		DrawBox(0, height1 * 6, width1 * 2, height1 * 7, gray, false);
		DrawExtendGraph(0, height1 * 6, width1 * 2, height1 * 7, doPerson->GRAPH, false);

	}


	if (!isDealCard) {

		DrawStringEx(10, height1 * 7 + 60, 1, "DrawCard");
	}
	else if (isDealCard) {
		DrawStringEx(10, height1 * 7 + 60, 1, "TurnEnd");
	}


}

//=====SceneBattle関数群=====//


void SceneBattle::DrawCard(int x, int y, int x2, int y2, int chara, bool flag)
{
	DrawExtendGraph(width1 * x, (height1 * y), width1 * x2, (height1 * y2), chara, flag);

}

void SceneBattle::BattleStart()
{

}



void SceneBattle::DrawHand(std::vector<Card*>& hand) {

	//とりあえず５枚表示
	//DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, chara1Hand[0]->c_graph, false); //1
	//DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, chara1Hand[1]->c_graph, false); //2
	//DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, chara1Hand[2]->c_graph, false); //3
	//DrawExtendGraph(1088, (height1 * 7) - CardUp_4, 1344, (height1 * 10) - CardUp_4, chara1Hand[3]->c_graph, false); //4
	//DrawExtendGraph(1344, (height1 * 7) - CardUp_5, 1600, (height1 * 10) - CardUp_5, chara1Hand[4]->c_graph, false); //5

	//
	for (int i = 0; i < hand.size(); i++) {

		if (hand.size() == 1) {
			DrawExtendGraph(512 + 320, (height1 * 7) - CardUp_1, 512 + cardW + 320, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			EaseImageCard1(easeOutExpo(t), 0, 832, 0);
		}
		else if (hand.size() == 2) {
			DrawExtendGraph(center - cardW, (height1 * 7) - CardUp_1, center, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(center, (height1 * 7) - CardUp_2, center + cardW, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			if (t < 0.5) {
				EaseImageCard1(easeOutExpo(t), 0, center - cardW, 0);
			}
			else {
				EaseImageCard1(easeOutExpo(t), 0, center, 0);
			}
		}

		else if (hand.size() == 3) {
			DrawExtendGraph(center - 128 - cardW, (height1 * 7) - CardUp_1, center - 128, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(center - 128, (height1 * 7) - CardUp_2, center + 128, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			DrawExtendGraph(center + 128, (height1 * 7) - CardUp_3, center + 128 + cardW, (height1 * 10) - CardUp_3, hand[2]->c_graph, false); //3
		}
		else if (hand.size() == 4) {
			DrawExtendGraph(center - (cardW * 2), (height1 * 7) - CardUp_1, center - cardW, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(center - cardW, (height1 * 7) - CardUp_2, center, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			DrawExtendGraph(center, (height1 * 7) - CardUp_3, center + cardW, (height1 * 10) - CardUp_3, hand[2]->c_graph, false); //3
			DrawExtendGraph(center + cardW, (height1 * 7) - CardUp_4, center + (cardW * 2), (height1 * 10) - CardUp_4, hand[3]->c_graph, false); //4
		}
		else if (hand.size() == 5) {
			DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, hand[2]->c_graph, false); //3
			DrawExtendGraph(1088, (height1 * 7) - CardUp_4, 1344, (height1 * 10) - CardUp_4, hand[3]->c_graph, false); //4
			DrawExtendGraph(1344, (height1 * 7) - CardUp_5, 1600, (height1 * 10) - CardUp_5, hand[4]->c_graph, false); //5
		}
		else if (hand.size() == 6) {
			DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(576 - cardPidl_6, (height1 * 7) - CardUp_2, 832 - cardPidl_6, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			DrawExtendGraph(832 - cardPidl_6 * 2, (height1 * 7) - CardUp_3, 1088 - cardPidl_6 * 2, (height1 * 10) - CardUp_3, hand[2]->c_graph, false); //3
			DrawExtendGraph(1088 - cardPidl_6 * 3, (height1 * 7) - CardUp_4, 1344 - cardPidl_6 * 3, (height1 * 10) - CardUp_4, hand[3]->c_graph, false); //4
			DrawExtendGraph(1344 - cardPidl_6 * 4, (height1 * 7) - CardUp_5, 1600 - cardPidl_6 * 4, (height1 * 10) - CardUp_5, hand[4]->c_graph, false); //5
			DrawExtendGraph(1600 - cardPidl_6 * 5, (height1 * 7) - CardUp_6, 1600, (height1 * 10) - CardUp_6, hand[5]->c_graph, false); //6
		}
		else if (hand.size() == 7) {
			DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(576 - cardPild_7, (height1 * 7) - CardUp_2, 832 - cardPild_7, (height1 * 10) - CardUp_2, hand[0]->c_graph, false); //2
			DrawExtendGraph(832 - cardPild_7 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_7 * 2, (height1 * 10) - CardUp_3, hand[1]->c_graph, false); //3
			DrawExtendGraph(1088 - cardPild_7 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_7 * 3, (height1 * 10) - CardUp_4, hand[2]->c_graph, false); //4
			DrawExtendGraph(1344 - cardPild_7 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_7 * 4, (height1 * 10) - CardUp_5, hand[3]->c_graph, false); //5
			DrawExtendGraph(1600 - cardPild_7 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_7 * 5, (height1 * 10) - CardUp_6, hand[5]->c_graph, false); //6
			DrawExtendGraph(1600 + (256) - cardPild_7 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_7 * 6, (height1 * 10) - CardUp_7, hand[6]->c_graph, false); //7
		}
		else if (hand.size() == 8) {
			DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(576 - cardPild_8, (height1 * 7) - CardUp_2, 832 - cardPild_8, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			DrawExtendGraph(832 - cardPild_8 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_8 * 2, (height1 * 10) - CardUp_3, hand[2]->c_graph, false); //3
			DrawExtendGraph(1088 - cardPild_8 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_8 * 3, (height1 * 10) - CardUp_4, hand[3]->c_graph, false); //4
			DrawExtendGraph(1344 - cardPild_8 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_8 * 4, (height1 * 10) - CardUp_5, hand[4]->c_graph, false); //5	

			DrawExtendGraph(1600 - cardPild_8 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_8 * 5, (height1 * 10) - CardUp_6, hand[5]->c_graph, false); //6		
			DrawExtendGraph(1600 + (256) - cardPild_8 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_8 * 6, (height1 * 10) - CardUp_7, hand[6]->c_graph, false); //7
			DrawExtendGraph(1600 + (256 * 2) - cardPild_8 * 7, (height1 * 7) - CardUp_8, 1600 + (256 * 3) - cardPild_8 * 7, (height1 * 10) - CardUp_8, hand[7]->c_graph, false); //8		
		}
		else if (hand.size() == 9) {
			DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(576 - cardPild_9, (height1 * 7) - CardUp_2, 832 - cardPild_9, (height1 * 10) - CardUp_2, hand[1]->c_graph, false); //2
			DrawExtendGraph(832 - cardPild_9 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_9 * 2, (height1 * 10) - CardUp_3, hand[2]->c_graph, false); //3
			DrawExtendGraph(1088 - cardPild_9 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_9 * 3, (height1 * 10) - CardUp_4, hand[3]->c_graph, false); //4
			DrawExtendGraph(1344 - cardPild_9 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_9 * 4, (height1 * 10) - CardUp_5, hand[4]->c_graph, false); //5

			DrawExtendGraph(1600 - cardPild_9 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_9 * 5, (height1 * 10) - CardUp_6, hand[5]->c_graph, false); //6
			DrawExtendGraph(1600 + (256) - cardPild_9 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_9 * 6, (height1 * 10) - CardUp_7, hand[6]->c_graph, false); //7
			DrawExtendGraph(1600 + (256 * 2) - cardPild_9 * 7, (height1 * 7) - CardUp_8, 1600 + (256 * 3) - cardPild_9 * 7, (height1 * 10) - CardUp_8, hand[7]->c_graph, false); //8
			DrawExtendGraph(1600 + (256 * 3) - cardPild_9 * 8, (height1 * 7) - CardUp_9, 1600 + (256 * 4) - cardPild_9 * 8, (height1 * 10) - CardUp_9, hand[8]->c_graph, false); //9

		}
		else if (hand.size() == 10) {
			DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[0]->c_graph, false); //1
			DrawExtendGraph(576 - cardPild_10, (height1 * 7) - CardUp_2, 832 - cardPild_10, (height1 * 10) - CardUp_2, hand[0]->c_graph, false); //2
			DrawExtendGraph(832 - cardPild_10 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_10 * 2, (height1 * 10) - CardUp_3, hand[1]->c_graph, false); //3
			DrawExtendGraph(1088 - cardPild_10 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_10 * 3, (height1 * 10) - CardUp_4, hand[2]->c_graph, false); //4
			DrawExtendGraph(1344 - cardPild_10 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_10 * 4, (height1 * 10) - CardUp_5, hand[3]->c_graph, false); //5

			DrawExtendGraph(1600 - cardPild_10 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_10 * 5, (height1 * 10) - CardUp_6, hand[4]->c_graph, false); //6
			DrawExtendGraph(1600 + (256) - cardPild_10 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_10 * 6, (height1 * 10) - CardUp_7, hand[5]->c_graph, false); //7
			DrawExtendGraph(1600 + (256 * 2) - cardPild_10 * 7, (height1 * 7) - CardUp_8, 1600 + (256 * 3) - cardPild_10 * 7, (height1 * 10) - CardUp_8, hand[6]->c_graph, false); //8
			DrawExtendGraph(1600 + (256 * 3) - cardPild_10 * 8, (height1 * 7) - CardUp_9, 1600 + (256 * 4) - cardPild_10 * 8, (height1 * 10) - CardUp_9, hand[7]->c_graph, false); //9
			DrawExtendGraph(1600 + (256 * 4) - cardPild_10 * 9, (height1 * 7) - CardUp_10, 1600 + (256 * 5) - cardPild_10 * 9, (height1 * 10) - CardUp_10, hand[8]->c_graph, false); //10

		}

	}

}

void SceneBattle::RaiseCard(std::vector<Card*> hand, int x, int y) {

	if (hand.size() == 1) {

		if (512 + 320 < MouseX && MouseX < 512 + cardW + 320 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

	}
	else if (hand.size() == 2) {

		if (center - cardW < MouseX && MouseX < center && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (center < MouseX && MouseX < center + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

	}
	else if (hand.size() == 3) {

		if (center - 128 - cardW < MouseX && MouseX < center - 128 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}
		if (center - 128 < MouseX && MouseX < center + 128 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}
		if (center + 128 < MouseX && MouseX < center + 128 + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}

	}
	else if (hand.size() == 4) {

		if (center - (cardW * 2) < MouseX && MouseX < center - cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}
		if (center - cardW < MouseX && MouseX < center && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}
		if (center < MouseX && MouseX < center + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}
		if (center + cardW < MouseX && MouseX < center + (cardW * 2) && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}

	}
	else if (hand.size() == 5) {

		if (320 < MouseX && MouseX < 576 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 < MouseX && MouseX < 832 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

		if (832 < MouseX && MouseX < 1088 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}

		if (1088 < MouseX && MouseX < 1344 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}

		if (1344 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}

	}
	else if (hand.size() == 6) {

		if (320 < MouseX && MouseX < 576 - cardPidl_6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 - cardPidl_6 < MouseX && MouseX < 832 - cardPidl_6 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

		if (832 - cardPidl_6 * 2 < MouseX && MouseX < 1088 - cardPidl_6 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}
		if (1088 - cardPidl_6 * 3 < MouseX && MouseX < 1344 - cardPidl_6 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}
		if (1344 - cardPidl_6 * 4 < MouseX && MouseX < 1600 - cardPidl_6 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}

		if (1600 - cardPidl_6 * 5 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_6 = 45;
		}
		else {
			CardUp_6 = 0;
		}

	}
	else if (hand.size() == 7) {

		if (320 < MouseX && MouseX < 576 - cardPild_7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 - cardPild_7 < MouseX && MouseX < 832 - cardPild_7 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

		if (832 - cardPild_7 * 2 < MouseX && MouseX < 1088 - cardPild_7 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}

		if (1088 - cardPild_7 * 3 < MouseX && MouseX < 1344 - cardPild_7 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}

		if (1344 - cardPild_7 * 4 < MouseX && MouseX < 1600 - cardPild_7 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}
		if (1600 - cardPild_7 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_7 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_6 = 45;
		}
		else {
			CardUp_6 = 0;
		}

		if (1600 + (256) - cardPild_7 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_7 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_7 = 45;
		}
		else {
			CardUp_7 = 0;
		}

	}
	else if (hand.size() == 8) {

		if (320 < MouseX && MouseX < 576 - cardPild_8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 - cardPild_8 < MouseX && MouseX < 832 - cardPild_8 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

		if (832 - cardPild_8 * 2 < MouseX && MouseX < 1088 - cardPild_8 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}

		if (1088 - cardPild_8 * 3 < MouseX && MouseX < 1344 - cardPild_8 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}

		if (1344 - cardPild_8 * 4 < MouseX && MouseX < 1600 - cardPild_8 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}
		if (1600 - cardPild_8 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_8 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_6 = 45;
		}
		else {
			CardUp_6 = 0;
		}

		if (1600 + (256) - cardPild_8 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_8 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_7 = 45;
		}
		else {
			CardUp_7 = 0;
		}

		if (1600 + (256 * 2) - cardPild_8 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_8 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_8 = 45;
		}
		else {
			CardUp_8 = 0;
		}

	}
	else if (hand.size() == 9) {

		if (320 < MouseX && MouseX < 576 - cardPild_9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 - cardPild_9 < MouseX && MouseX < 832 - cardPild_9 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

		if (832 - cardPild_9 * 2 < MouseX && MouseX < 1088 - cardPild_9 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}

		if (1088 - cardPild_9 * 3 < MouseX && MouseX < 1344 - cardPild_9 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}

		if (1344 - cardPild_9 * 4 < MouseX && MouseX < 1600 - cardPild_9 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}
		if (1600 - cardPild_9 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_9 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_6 = 45;
		}
		else {
			CardUp_6 = 0;
		}

		if (1600 + (256) - cardPild_9 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_9 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_7 = 45;
		}
		else {
			CardUp_7 = 0;
		}

		if (1600 + (256 * 2) - cardPild_9 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_9 * 8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_8 = 45;
		}
		else {
			CardUp_8 = 0;
		}

		if (1600 + (256 * 3) - cardPild_9 * 8 < MouseX && MouseX < 1600 + (256 * 4) - cardPild_9 * 9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_9 = 45;
		}
		else {
			CardUp_9 = 0;
		}

	}
	else if (hand.size() == 10) {

		if (320 < MouseX && MouseX < 576 - cardPild_10 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 - cardPild_10 < MouseX && MouseX < 832 - cardPild_10 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_2 = 45;
		}
		else {
			CardUp_2 = 0;
		}

		if (832 - cardPild_10 * 2 < MouseX && MouseX < 1088 - cardPild_10 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_3 = 45;
		}
		else {
			CardUp_3 = 0;
		}

		if (1088 - cardPild_10 * 3 < MouseX && MouseX < 1344 - cardPild_10 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_4 = 45;
		}
		else {
			CardUp_4 = 0;
		}

		if (1344 - cardPild_10 * 4 < MouseX && MouseX < 1600 - cardPild_10 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}
		if (1600 - cardPild_10 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_10 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_6 = 45;
		}
		else {
			CardUp_6 = 0;
		}

		if (1600 + (256) - cardPild_10 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_10 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_7 = 45;
		}
		else {
			CardUp_7 = 0;
		}

		if (1600 + (256 * 2) - cardPild_10 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_10 * 8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_8 = 45;
		}
		else {
			CardUp_8 = 0;
		}

		if (1600 + (256 * 3) - cardPild_10 * 8 < MouseX && MouseX < 1600 + (256 * 4) - cardPild_10 * 9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_9 = 45;
		}
		else {
			CardUp_9 = 0;
		}

		if (1600 + (256 * 4) - cardPild_10 * 9 < MouseX && MouseX < 1600 + (256 * 5) - cardPild_10 * 10 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_10 = 45;
		}
		else {
			CardUp_10 = 0;
		}
	}


}

// t: 経過時間, b: 初期値, c: 変化量, d: トータル時間

void SceneBattle::DrawTurn() {







}

double SceneBattle::easeInExpo(double t) {
	if (t == 0) { return 0; }
	return pow(2, 10 * t - 10);
}

double SceneBattle::easeOutExpo(double t) {
	if (t == 1) { return 1; }
	return 1 - pow(2, -10 * t);
}

void SceneBattle::EaseImageCard1(double t, int x_s, int x_e, int delay) {

	auto x = (1 - t) * x_s + t * x_e;
	DrawExtendGraph(x, (height1 * 7) - CardUp_1, x + cardW, (height1 * 10) - CardUp_1, card1, false); //1

}

void SceneBattle::EaseTurnImage(double out_t, double in_t, int x_s, int x_e) {

	auto x = (1 - t) * x_s + t * x_e;

	if (x <= 640) {
		t = out_t;
	}
	else if (640) {

	}
	DrawExtendGraph(x, height1 * 3, x + width1 * 2, height1 * 4, img_yourturn, true);
}

void SceneBattle::LoadBattleGraph() {
	img_background = LoadGraph("graphics/background2.png");

	img_mon1 = LoadGraph("graphics/m1.png");
	img_chara1_face = LoadGraph("graphics/chara1_face.png"); //冒険者
	img_chara2_face = LoadGraph("graphics/chara2_face.png"); //シーフ
	img_chara3_face = LoadGraph("graphics/chara3_face.png"); //重騎士
	img_chara4_face = LoadGraph("graphics/chara4_face.png"); //回復士
	img_enemy1_face = LoadGraph("graphics/enemy1_face.png"); //デブアリ

	//card1 = LoadGraph("graphics/card_1.png"); //誘導
	//card2 = LoadGraph("graphics/card_2.png"); //斬りつける
	//card3 = LoadGraph("graphics/card_3.png"); //逃げる
	//card4 = LoadGraph("graphics/card_4.png"); //守る
	//card5 = LoadGraph("graphics/card_5.png"); //鼓舞
	//card6 = LoadGraph("graphics/card_6.png"); //分析
	//card7 = LoadGraph("graphics/card_7.png"); //ポジションチェンジ
	//card8 = LoadGraph("graphics/card_8.png"); //ファイア
	//card9 = LoadGraph("graphics/card_9.png"); //ヒール
	//card10 = LoadGraph("graphics/card_10.png"); //盾を構える
	//card11 = LoadGraph("graphics/card_11.png"); //指摘
	//card12 = LoadGraph("graphics/card_12.png"); //状態異常回復
	//card13 = LoadGraph("graphics/card_13.png"); //クイック
	//card14 = LoadGraph("graphics/card_14.png"); //戦闘準備
	//card15 = LoadGraph("graphics/card_15.png"); //挑発

	hp_bar = LoadGraph("graphics/hp_bar.png"); //hpバー
	hp_bar_back = LoadGraph("graphics/hp_bar_back.png"); //hp_barの後ろのバー

	img_yourturn = LoadGraph("graphics/img_yourturn2.png"); //yourターン描写
	img_enemyturn = LoadGraph("graphics/img_enemyturn2.png"); //enemyターン描写

	img_turn = LoadGraph("graphics/turn.png"); //turn描写用
	select_flame = LoadGraph("graphics/select_flame.png"); //選択描写用
}

void SceneBattle::DrawHpBar(int hp_now, int hp_max) {

	int color = GetColor(255, 255, 255);
	int color2 = GetColor(255, 0, 0);

	DrawBox(10, (height1 * 7) + 20, 300 * hp_now / hp_max, (height1 * 7) + 30, color2, true);
	DrawBox(10, (height1 * 7) + 20, 300, (height1 * 7) + 30, color, false);

}

void SceneBattle::DealFromDeckToHand(const std::vector<Card*>& deck, std::vector<Card*>& hand, int handNum) {

	if (hand.size() == 10) { return; }

	if (deck.size() < handNum) {
		return;
	}

	std::mt19937 engine(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, deck.size() - 1);


	if (doPerson->isFirstDeal == true) { handNum = 1; }

	for (int i = 0; i < handNum; ++i) {
		int randomIndex = dist(engine);
		hand.push_back(deck[randomIndex]);
	}

	doPerson->isFirstDeal = true;

}

void SceneBattle::Debug() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		dealHand = true;
	}

}

void SceneBattle::DrawOrder() {


	//DrawExtendGraph(0, height1 * 0, width1 * 2, height1 * 1, img_mon1, false);
	//DrawExtendGraph(0, height1 * 1, width1 * 2 - 50, height1 * 2, img_chara1_face, false);
	//DrawExtendGraph(0, height1 * 2, width1 * 2 - 50, height1 * 3, img_chara1_face, false);
	//DrawExtendGraph(0, height1 * 3, width1 * 2 - 50, height1 * 4, img_chara1_face, false);

	//まずは合計４人を想定
	DrawExtendGraph(0, height1 * 0, width1 * 2, height1 * 1, order1thImage, false);
	DrawExtendGraph(0, height1 * 1, width1 * 2 - 50, height1 * 2, order2thImage, false);
	DrawExtendGraph(0, height1 * 2, width1 * 2 - 50, height1 * 3, order3thImage, false);
	DrawExtendGraph(0, height1 * 4, width1 * 2 - 50, height1 * 5, order4thImage, false);


	//for (int i = 0; i < allCharacters.size(); ++i) {
	//	DrawStringEx(0, height1 * i, 1, "%d", allCharacters[i]->SPEED);
	//}

}

void SceneBattle::SetParty(std::vector<Person*>& person, std::vector<Person*>& party) {

	for (int i = 0; i < person.size(); i++) {
		if (person[i]->PICK == true) {
			party.push_back(person[i]);
		}
	}

}

void SceneBattle::ReflectOrderImage() {

	int i, k;
	for (i = 0, k = 0; i < party.size() && k < enemies.size(); ) {
		if (party[i]->SPEED > enemies[k]->SPEED) {
			if (party[i]->GRAPH != 0) {
				if (order1thImage == 0) {
					order1thImage = party[i]->GRAPH;
				}
				else if (order2thImage == 0) {
					order2thImage = party[i]->GRAPH;
				}
				else if (order3thImage == 0) {
					order3thImage = party[i]->GRAPH;
				}
				else if (order4thImage == 0) {
					order4thImage = party[i]->GRAPH;
				}
				else if (order5thImage == 0) {
					order5thImage = party[i]->GRAPH;
				}
			}
			i++;
		}
		else {
			if (enemies[k]->GRAPH != 0) {
				if (order1thImage == 0) {
					order1thImage = enemies[k]->GRAPH;
				}
				else if (order2thImage == 0) {
					order2thImage = enemies[k]->GRAPH;
				}
				else if (order3thImage == 0) {
					order3thImage = enemies[k]->GRAPH;
				}
				else if (order4thImage == 0) {
					order4thImage = enemies[k]->GRAPH;
				}
				else if (order5thImage == 0) {
					order5thImage = enemies[k]->GRAPH;
				}
			}
			k++;
		}
	}

	for (; i < party.size(); i++) {
		if (party[i]->GRAPH != 0) {
			if (order1thImage == 0) {
				order1thImage = party[i]->GRAPH;
			}
			else if (order2thImage == 0) {
				order2thImage = party[i]->GRAPH;
			}
			else if (order3thImage == 0) {
				order3thImage = party[i]->GRAPH;
			}
			else if (order4thImage == 0) {
				order4thImage = party[i]->GRAPH;
			}
			else if (order5thImage == 0) {
				order5thImage = party[i]->GRAPH;
			}
		}
	}

	for (; k < enemies.size(); k++) {
		if (enemies[k]->GRAPH != 0) {
			if (order1thImage == 0) {
				order1thImage = enemies[k]->GRAPH;
			}
			else if (order2thImage == 0) {
				order2thImage = enemies[k]->GRAPH;
			}
			else if (order3thImage == 0) {
				order3thImage = enemies[k]->GRAPH;
			}
			else if (order4thImage == 0) {
				order4thImage = enemies[k]->GRAPH;
			}
			else if (order5thImage == 0) {
				order5thImage = enemies[k]->GRAPH;
			}
		}

	}
	//while (i < party.size() && k < enemies.size()) { //降順にソートした同士を比べる

	//	int i = 0;
	//	int k = 0;

	//	// i < party.size() || k < enemies.size() でもよい
	//	while (i < party.size() && k < enemies.size()) {
	//		if (party[i]->SPEED > enemies[k]->SPEED) {
	//			if (order1thImage == 0) {
	//				order1thImage = party[i]->GRAPH;
	//			}
	//			else if (order2thImage == 0) {
	//				order2thImage = party[i]->GRAPH;
	//			}
	//			else if (order3thImage == 0) {
	//				order3thImage = party[i]->GRAPH;
	//			}
	//			else if (order4thImage == 0) {
	//				order4thImage = party[i]->GRAPH;
	//			}
	//			else if (order5thImage == 0) {
	//				order5thImage = party[i]->GRAPH;
	//			}
	//			i++;
	//		}
	//		else {
	//			if (order1thImage == 0) {
	//				order1thImage = enemies[k]->GRAPH;
	//			}
	//			else if (order2thImage == 0) {
	//				order2thImage = enemies[k]->GRAPH;
	//			}
	//			else if (order3thImage == 0) {
	//				order3thImage = enemies[k]->GRAPH;
	//			}
	//			else if (order4thImage == 0) {
	//				order4thImage = enemies[k]->GRAPH;
	//			}
	//			else if (order5thImage == 0) {
	//				order5thImage = enemies[k]->GRAPH;
	//			}
	//			k++;
	//		}
	//	}

	//	// 余った人数の処理
	//	while (i < party.size()) {
	//		if (order1thImage == 0) {
	//			order1thImage = party[i]->GRAPH;
	//		}
	//		else if (order2thImage == 0) {
	//			order2thImage = party[i]->GRAPH;
	//		}
	//		else if (order3thImage == 0) {
	//			order3thImage = party[i]->GRAPH;
	//		}
	//		else if (order4thImage == 0) {
	//			order4thImage = party[i]->GRAPH;
	//		}
	//		else if (order5thImage == 0) {
	//			order5thImage = party[i]->GRAPH;
	//		}
	//		i++;
	//	}

	//	// 余った敵の処理
	//	while (k < enemies.size()) {

	//		if (order1thImage == 0) {
	//			order1thImage = enemies[k]->GRAPH;
	//		}
	//		else if (order2thImage == 0) {
	//			order2thImage = enemies[k]->GRAPH;
	//		}
	//		else if (order3thImage == 0) {
	//			order3thImage = enemies[k]->GRAPH;
	//		}
	//		else if (order4thImage == 0) {
	//			order4thImage = enemies[k]->GRAPH;
	//		}
	//		else if (order5thImage == 0) {
	//			order5thImage = enemies[k]->GRAPH;
	//		}
	//		k++;

	//	}
	//	
	//}


}


void SceneBattle::UseCardFromHand(Person* person, std::vector<Card*>& hand, int x, int y) {

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

		if (hand.size() == 1) {

			if (512 + 320 < MouseX && MouseX < 512 + cardW + 320 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {

				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0],person,party,enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}

			}

		}
		else if (hand.size() == 2) {

			if (center - cardW < MouseX && MouseX < center && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {

				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}

			}

			if (center < MouseX && MouseX < center + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {

				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin() + 1);
				}
			}

		}
		else if (hand.size() == 3) {

			if (center - 128 - cardW < MouseX && MouseX < center - 128 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}

			if (center - 128 < MouseX && MouseX < center + 128 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin() + 1);
				}
			}

			if (center + 128 < MouseX && MouseX < center + 128 + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin() + 2);
				}
			}


		}
		else if (hand.size() == 4) {

			if (center - (cardW * 2) < MouseX && MouseX < center - cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}

			if (center - cardW < MouseX && MouseX < center && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin() + 1);
				}
			}

			if (center < MouseX && MouseX < center + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin() + 2);
				}
			}

			if (center + cardW < MouseX && MouseX < center + (cardW * 2) && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}


		}
		else if (hand.size() == 5) {

			if (320 < x && x < 576 && height1 * 7 <= y && y <= height1 * 10) {

				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}

			}


			if (576 < x && x < 832 && height1 * 7 <= y && y <= height1 * 10) {

				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+1);
				}
			}


			if (832 < x && x < 1088 && height1 * 7 <= y && y <= height1 * 10) {

				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+2);
				}
			}


			if (1088 < MouseX && MouseX < 1344 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {

				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}


			if (1344 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {

				if (person->COST >= hand[4]->c_cost) {

					person->COST -= hand[4]->c_cost;

					useCard(hand[4], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+4);
				}
			}


		}
		else if (hand.size() == 6) {

			if (320 < MouseX && MouseX < 576 - cardPidl_6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}


			if (576 - cardPidl_6 < MouseX && MouseX < 832 - cardPidl_6 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+1);
				}
			}


			if (832 - cardPidl_6 * 2 < MouseX && MouseX < 1088 - cardPidl_6 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+2);
				}
			}

			if (1088 - cardPidl_6 * 3 < MouseX && MouseX < 1344 - cardPidl_6 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}

			if (1344 - cardPidl_6 * 4 < MouseX && MouseX < 1600 - cardPidl_6 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[4]->c_cost) {

					person->COST -= hand[4]->c_cost;

					useCard(hand[4], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+4);
				}
			}

			if (1600 - cardPidl_6 * 5 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[5]->c_cost) {

					person->COST -= hand[5]->c_cost;

					useCard(hand[5], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+5);
				}
			}

		}
		else if (hand.size() == 7) {

			if (320 < MouseX && MouseX < 576 - cardPild_7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}

			if (576 - cardPild_7 < MouseX && MouseX < 832 - cardPild_7 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}


			if (832 - cardPild_7 * 2 < MouseX && MouseX < 1088 - cardPild_7 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+2);
				}
			}

			if (1088 - cardPild_7 * 3 < MouseX && MouseX < 1344 - cardPild_7 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}


			if (1344 - cardPild_7 * 4 < MouseX && MouseX < 1600 - cardPild_7 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[4]->c_cost) {

					person->COST -= hand[4]->c_cost;

					useCard(hand[4], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+4);
				}
			}

			if (1600 - cardPild_7 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_7 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[5]->c_cost) {

					person->COST -= hand[5]->c_cost;

					useCard(hand[5], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+5);
				}
			}


			if (1600 + (256) - cardPild_7 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_7 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[6]->c_cost) {

					person->COST -= hand[6]->c_cost;

					useCard(hand[6], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+6);
				}
			}


		}
		else if (hand.size() == 8) {

			if (320 < MouseX && MouseX < 576 - cardPild_8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}

			if (576 - cardPild_8 < MouseX && MouseX < 832 - cardPild_8 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+1);
				}
			}


			if (832 - cardPild_8 * 2 < MouseX && MouseX < 1088 - cardPild_8 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+2);
				}
			}

			if (1088 - cardPild_8 * 3 < MouseX && MouseX < 1344 - cardPild_8 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}

			if (1344 - cardPild_8 * 4 < MouseX && MouseX < 1600 - cardPild_8 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[4]->c_cost) {

					person->COST -= hand[4]->c_cost;

					useCard(hand[4], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+4);
				}
			}

			if (1600 - cardPild_8 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_8 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[5]->c_cost) {

					person->COST -= hand[5]->c_cost;

					useCard(hand[5], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+5);
				}
			}


			if (1600 + (256) - cardPild_8 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_8 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[6]->c_cost) {

					person->COST -= hand[6]->c_cost;

					useCard(hand[6], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+6);
				}
			}

			if (1600 + (256 * 2) - cardPild_8 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_8 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[7]->c_cost) {

					person->COST -= hand[7]->c_cost;

					useCard(hand[7], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+7);
				}
			}


		}
		else if (hand.size() == 9) {

			if (320 < MouseX && MouseX < 576 - cardPild_9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}


			if (576 - cardPild_9 < MouseX && MouseX < 832 - cardPild_9 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+1);
				}
			}

			if (832 - cardPild_9 * 2 < MouseX && MouseX < 1088 - cardPild_9 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+2);
				}
			}

			if (1088 - cardPild_9 * 3 < MouseX && MouseX < 1344 - cardPild_9 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}


			if (1344 - cardPild_9 * 4 < MouseX && MouseX < 1600 - cardPild_9 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[4]->c_cost) {

					person->COST -= hand[4]->c_cost;

					useCard(hand[4], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+4);
				}
			}

			if (1600 - cardPild_9 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_9 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[5]->c_cost) {

					person->COST -= hand[5]->c_cost;

					useCard(hand[5], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+5);
				}
			}


			if (1600 + (256) - cardPild_9 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_9 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[6]->c_cost) {

					person->COST -= hand[6]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+6);
				}
			}


			if (1600 + (256 * 2) - cardPild_9 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_9 * 8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[7]->c_cost) {

					person->COST -= hand[7]->c_cost;

					useCard(hand[7], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+7);
				}
			}


			if (1600 + (256 * 3) - cardPild_9 * 8 < MouseX && MouseX < 1600 + (256 * 4) - cardPild_9 * 9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[8]->c_cost) {

					person->COST -= hand[8]->c_cost;

					useCard(hand[8], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+8);
				}
			}


		}
		else if (hand.size() == 10) {
			if (320 < MouseX && MouseX < 576 - cardPild_10 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[0]->c_cost) {

					person->COST -= hand[0]->c_cost;

					useCard(hand[0], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin());
				}
			}

			if (576 - cardPild_10 < MouseX && MouseX < 832 - cardPild_10 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[1]->c_cost) {

					person->COST -= hand[1]->c_cost;

					useCard(hand[1], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+1);
				}
			}


			if (832 - cardPild_10 * 2 < MouseX && MouseX < 1088 - cardPild_10 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[2]->c_cost) {

					person->COST -= hand[2]->c_cost;

					useCard(hand[2], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+2);
				}
			}

			if (1088 - cardPild_10 * 3 < MouseX && MouseX < 1344 - cardPild_10 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[3]->c_cost) {

					person->COST -= hand[3]->c_cost;

					useCard(hand[3], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+3);
				}
			}

			if (1344 - cardPild_10 * 4 < MouseX && MouseX < 1600 - cardPild_10 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[4]->c_cost) {

					person->COST -= hand[4]->c_cost;

					useCard(hand[4], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+4);
				}
			}

			if (1600 - cardPild_10 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_10 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[5]->c_cost) {

					person->COST -= hand[5]->c_cost;

					useCard(hand[5], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+5);
				}
			}


			if (1600 + (256) - cardPild_10 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_10 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[6]->c_cost) {

					person->COST -= hand[6]->c_cost;

					useCard(hand[6], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+6);
				}
			}


			if (1600 + (256 * 2) - cardPild_10 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_10 * 8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[7]->c_cost) {

					person->COST -= hand[7]->c_cost;

					useCard(hand[7], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+7);
				}
			}


			if (1600 + (256 * 3) - cardPild_10 * 8 < MouseX && MouseX < 1600 + (256 * 4) - cardPild_10 * 9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[8]->c_cost) {

					person->COST -= hand[8]->c_cost;

					useCard(hand[8], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+8);
				}
			}


			if (1600 + (256 * 4) - cardPild_10 * 9 < MouseX && MouseX < 1600 + (256 * 5) - cardPild_10 * 10 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
				if (person->COST >= hand[9]->c_cost) {

					person->COST -= hand[9]->c_cost;

					useCard(hand[9], person, party, enemies);
					PlaySoundMem(smgr->useCard_se, DX_PLAYTYPE_BACK);
					hand.erase(hand.begin()+9);
				}
			}



		}



	}


}

void SceneBattle::useCard(Card*& card, Person* person, std::vector<Person*>& party, std::vector<Enemy*>& enemies) {

	if (card->c_effect) {


	}
	else if (card->c_effect == false) {

		if(card->c_damage > 0) {
			
			enemies[0]->HP -= card->c_damage;
			
		}
		else if (card->c_hate > 0) {

			person->HATE += card->c_hate;

		}
		else if (card->c_protec > 0) {

			person->PROTEC += card->c_protec;

		}
		else if (card->c_slow > 0) {

			enemies[0]->SPEED -= card->c_slow;

		}
		else if (card->c_weak > 0) {

		}



	}




}

void SceneBattle::DecideOrderUnit(std::vector<Unit*>& allUnit) {

	//if (f) {

	for (auto& unit : allUnit) {
		if (unit->getIsDead() == false && unit->getIsActed() == false) {

			if (unit->getIsEnemy() == false) { // 味方の場合

				doPerson = static_cast<Person*>(unit);
				doPerson->setIsActed(true);
				break;

			}
			else if (unit->getIsEnemy() == true) { // 敵の場合

				doEnemy = static_cast<Enemy*>(unit);
				doEnemy->setIsActed(true);
				break;

			}
		}
	}

	//	f = false;
	//}


}

void SceneBattle::ChangeFlagByclickOnRange(int x, int y, int x2, int y2, bool f, int mouseX, int mouseY) {

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

		if (x < mouseX && mouseX < x2 && y < mouseY && mouseY < y2) {

			if (f) { f = false; }
			else if (!f) { f = true; }

		}

	}



}


//memo
//小規模な要素の追加はemplace_backを使用するとよい？（要検索）

		//switch (i)
		//{
		//case 0:
		//	DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, hand[i]->c_graph, false); //1
		//	break;
		//case 1:
		//	DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, hand[i]->c_graph, false); //2
		//	break;
		//case 2:
		//	DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, hand[i]->c_graph, false); //3
		//	break;
		//case 3:
		//	DrawExtendGraph(1088, (height1 * 7) - CardUp_4, 1344, (height1 * 10) - CardUp_4, hand[i]->c_graph, false); //4
		//	break;
		//case 4:
		//	DrawExtendGraph(1344, (height1 * 7) - CardUp_5, 1600, (height1 * 10) - CardUp_5, hand[i]->c_graph, false); //5
		//	break;
		//default:
		//	break;
		//}

	////TODO:マジックナンバーを画面比率から変数でとる
	//if (320 < MouseX && MouseX < 576 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//	CardUp_1 = 45;
	//}
	//else {
	//	CardUp_1 = 0;
	//}

	//if (576 < MouseX && MouseX < 832 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//	CardUp_2 = 45;
	//}
	//else {
	//	CardUp_2 = 0;
	//}

	//if (832 < MouseX && MouseX < 1088 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//	CardUp_3 = 45;
	//}
	//else {
	//	CardUp_3 = 0;
	//}

	//if (1088 < MouseX && MouseX < 1344 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//	CardUp_4 = 45;
	//}
	//else {
	//	CardUp_4 = 0;
	//}

	//if (1344 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//	CardUp_5 = 45;
	//}
	//else {
	//	CardUp_5 = 0;
	//}


//if (numOfCards == 1) {
//	if (512 + 320 < MouseX && MouseX < 512 + cardW + 320 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//}
//
//if (numOfCards == 2) {
//
//	if (center - cardW < MouseX && MouseX < center && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//
//	if (center < MouseX && MouseX < center + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//}
//
//if (numOfCards == 3) {
//	if (center - 128 - cardW < MouseX && MouseX < center - 128 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//	if (center - 128 < MouseX && MouseX < center + 128 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//	if (center + 128 < MouseX && MouseX < center + 128 + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//}
//
//if (numOfCards == 4) {
//	if (center - (cardW * 2) < MouseX && MouseX < center - cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//	if (center - cardW < MouseX && MouseX < center && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//	if (center < MouseX && MouseX < center + cardW && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//	if (center + cardW < MouseX && MouseX < center + (cardW * 2) && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
//		CardUp_4 = 45;
//	}
//	else {
//		CardUp_4 = 0;
//	}
//}
//
//if (numOfCards == 5) {
//
//	if (320 < MouseX && MouseX < 576 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//
//	if (576 < MouseX && MouseX < 832 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//
//	if (832 < MouseX && MouseX < 1088 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//
//	if (1088 < MouseX && MouseX < 1344 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_4 = 45;
//	}
//	else {
//		CardUp_4 = 0;
//	}
//
//	if (1344 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_5 = 45;
//	}
//	else {
//		CardUp_5 = 0;
//	}
//
//}
//
//if (numOfCards == 6) {
//	if (320 < MouseX && MouseX < 576 - cardPidl_6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//
//	if (576 - cardPidl_6 < MouseX && MouseX < 832 - cardPidl_6 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//
//	if (832 - cardPidl_6 * 2 < MouseX && MouseX < 1088 - cardPidl_6 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//	if (1088 - cardPidl_6 * 3 < MouseX && MouseX < 1344 - cardPidl_6 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_4 = 45;
//	}
//	else {
//		CardUp_4 = 0;
//	}
//	if (1344 - cardPidl_6 * 4 < MouseX && MouseX < 1600 - cardPidl_6 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_5 = 45;
//	}
//	else {
//		CardUp_5 = 0;
//	}
//
//	if (1600 - cardPidl_6 * 5 < MouseX && MouseX < 1600 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_6 = 45;
//	}
//	else {
//		CardUp_6 = 0;
//	}
//
//}
//
//if (numOfCards == 7) {
//
//	if (320 < MouseX && MouseX < 576 - cardPild_7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//
//	if (576 - cardPild_7 < MouseX && MouseX < 832 - cardPild_7 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//
//	if (832 - cardPild_7 * 2 < MouseX && MouseX < 1088 - cardPild_7 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//
//	if (1088 - cardPild_7 * 3 < MouseX && MouseX < 1344 - cardPild_7 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_4 = 45;
//	}
//	else {
//		CardUp_4 = 0;
//	}
//
//	if (1344 - cardPild_7 * 4 < MouseX && MouseX < 1600 - cardPild_7 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_5 = 45;
//	}
//	else {
//		CardUp_5 = 0;
//	}
//	if (1600 - cardPild_7 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_7 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_6 = 45;
//	}
//	else {
//		CardUp_6 = 0;
//	}
//
//	if (1600 + (256) - cardPild_7 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_7 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_7 = 45;
//	}
//	else {
//		CardUp_7 = 0;
//	}
//
//}
//
//if (numOfCards == 8) {
//
//	if (320 < MouseX && MouseX < 576 - cardPild_8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//
//	if (576 - cardPild_8 < MouseX && MouseX < 832 - cardPild_8 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//
//	if (832 - cardPild_8 * 2 < MouseX && MouseX < 1088 - cardPild_8 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//
//	if (1088 - cardPild_8 * 3 < MouseX && MouseX < 1344 - cardPild_8 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_4 = 45;
//	}
//	else {
//		CardUp_4 = 0;
//	}
//
//	if (1344 - cardPild_8 * 4 < MouseX && MouseX < 1600 - cardPild_8 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_5 = 45;
//	}
//	else {
//		CardUp_5 = 0;
//	}
//	if (1600 - cardPild_8 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_8 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_6 = 45;
//	}
//	else {
//		CardUp_6 = 0;
//	}
//
//	if (1600 + (256) - cardPild_8 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_8 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_7 = 45;
//	}
//	else {
//		CardUp_7 = 0;
//	}
//
//	if (1600 + (256 * 2) - cardPild_8 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_8 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_8 = 45;
//	}
//	else {
//		CardUp_8 = 0;
//	}
//
//}
//
//if (numOfCards == 9) {
//
//	if (320 < MouseX && MouseX < 576 - cardPild_9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_1 = 45;
//	}
//	else {
//		CardUp_1 = 0;
//	}
//
//	if (576 - cardPild_9 < MouseX && MouseX < 832 - cardPild_9 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_2 = 45;
//	}
//	else {
//		CardUp_2 = 0;
//	}
//
//	if (832 - cardPild_9 * 2 < MouseX && MouseX < 1088 - cardPild_9 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_3 = 45;
//	}
//	else {
//		CardUp_3 = 0;
//	}
//
//	if (1088 - cardPild_9 * 3 < MouseX && MouseX < 1344 - cardPild_9 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_4 = 45;
//	}
//	else {
//		CardUp_4 = 0;
//	}
//
//	if (1344 - cardPild_9 * 4 < MouseX && MouseX < 1600 - cardPild_9 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_5 = 45;
//	}
//	else {
//		CardUp_5 = 0;
//	}
//	if (1600 - cardPild_9 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_9 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_6 = 45;
//	}
//	else {
//		CardUp_6 = 0;
//	}
//
//	if (1600 + (256) - cardPild_9 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_9 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_7 = 45;
//	}
//	else {
//		CardUp_7 = 0;
//	}
//
//	if (1600 + (256 * 2) - cardPild_9 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_9 * 8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_8 = 45;
//	}
//	else {
//		CardUp_8 = 0;
//	}
//
//	if (1600 + (256 * 3) - cardPild_9 * 8 < MouseX && MouseX < 1600 + (256 * 4) - cardPild_9 * 9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
//		CardUp_9 = 45;
//	}
//	else {
//		CardUp_9 = 0;
//	}
//
//}

	//if (numOfCards == 10) {

	//	if (320 < MouseX && MouseX < 576 - cardPild_10 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_1 = 45;
	//	}
	//	else {
	//		CardUp_1 = 0;
	//	}

	//	if (576 - cardPild_10 < MouseX && MouseX < 832 - cardPild_10 * 2 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_2 = 45;
	//	}
	//	else {
	//		CardUp_2 = 0;
	//	}

	//	if (832 - cardPild_10 * 2 < MouseX && MouseX < 1088 - cardPild_10 * 3 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_3 = 45;
	//	}
	//	else {
	//		CardUp_3 = 0;
	//	}

	//	if (1088 - cardPild_10 * 3 < MouseX && MouseX < 1344 - cardPild_10 * 4 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_4 = 45;
	//	}
	//	else {
	//		CardUp_4 = 0;
	//	}

	//	if (1344 - cardPild_10 * 4 < MouseX && MouseX < 1600 - cardPild_10 * 5 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_5 = 45;
	//	}
	//	else {
	//		CardUp_5 = 0;
	//	}
	//	if (1600 - cardPild_10 * 5 < MouseX && MouseX < 1600 + (256) - cardPild_10 * 6 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_6 = 45;
	//	}
	//	else {
	//		CardUp_6 = 0;
	//	}

	//	if (1600 + (256) - cardPild_10 * 6 < MouseX && MouseX < 1600 + (256 * 2) - cardPild_10 * 7 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_7 = 45;
	//	}
	//	else {
	//		CardUp_7 = 0;
	//	}

	//	if (1600 + (256 * 2) - cardPild_10 * 7 < MouseX && MouseX < 1600 + (256 * 3) - cardPild_10 * 8 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_8 = 45;
	//	}
	//	else {
	//		CardUp_8 = 0;
	//	}

	//	if (1600 + (256 * 3) - cardPild_10 * 8 < MouseX && MouseX < 1600 + (256 * 4) - cardPild_10 * 9 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_9 = 45;
	//	}
	//	else {
	//		CardUp_9 = 0;
	//	}

	//	if (1600 + (256 * 4) - cardPild_10 * 9 < MouseX && MouseX < 1600 + (256 * 5) - cardPild_10 * 10 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
	//		CardUp_10 = 45;
	//	}
	//	else {
	//		CardUp_10 = 0;
	//	}

	//}