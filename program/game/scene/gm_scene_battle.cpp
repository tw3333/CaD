#include "gm_scene_battle.h"

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <windows.h>

#include "gm_scene_charaedit.h"
#include "../gm_person_manager.h"

//
//SceneBattle::~SceneBattle() {
//	
//}

Person* getPerson(0);

void SceneBattle::initialzie() {


	LoadBattleGraph();

	finish = false;
	dealcard = false;

	enemy_anime = true;
	chara_num = 1;
	img_turn_move = 25;

	hp_now = hp_max;
	int x = 320;
	
	//PersonManager pgmr_;

}

void SceneBattle::update(float dalta_time) {
	GameManager* mgr = GameManager::GetInstance();
	
	
	
	BattleStart();

	//簡易敵アニメーション 
	timer += 0.1 * 1;
	move += 2 * sin(timer);

	GetMousePoint(&MouseX, &MouseY);
	drawCardUp(MouseX, MouseY);

	//シーン切り替え
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneCharaEdit());
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


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_H) && hp_now != 0) {
		//pmgr.person1->HP;
		your_turn = true;
	}

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

	//行動キャラ表示
	DrawBox(0, height1 * 6, width1 * 2, height1 * 7, gray, false);
	DrawExtendGraph(0, height1 * 6, width1 * 2, height1 * 7, chara_select, false);



	//行動順ぎめ
	//DrawBox(0, 0, width1 * 2, height1 * 4, red, false);

	//ターンの画像//
	//DrawGraph(0, 0, img_turn, false);
	if (startTurn) {
		DrawExtendGraph(0, 0, width1 * 2, height1 * 1, img_chara1_face, false);
		DrawExtendGraph(0, height1 * 1, width1 * 2, height1 * 2, img_enemy1_face, false);
		DrawExtendGraph(0, height1 * 2, width1 * 2, height1 * 3, img_chara1_face, false);
		DrawExtendGraph(0, height1 * 3, width1 * 2, height1 * 4, img_chara1_face, false);
	}


	//DrawLine(0,height1*2, width1*4, height1* 2,red);

	//手札描写
	DrawHands();

	DrawBox(0, height1 * 7, width1 * 2, height1 * 10, Silver, true);

	//ターン描写
	//DrawExtendGraph(width1*4,height1*3,width1*6,height1*4,img_yourturn,true);

	//EaseTurnImage(easeOutExpo(t), 0, width1 * 4);
	//EaseTurnImage(easeInExpo(t), width1*4, width1 * 10);

	

	DrawTurn();

	//選択フレーム
	//DrawCard(0 + select_move, 7, 2 + select_move, 10, select_flame, true);

	//カード置き場
	//DrawBox(0, height1 * 7, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, GetColor(138, 140, 142), false);

	//カード説明描写
	DrawBox(width1*8, height1 * 1, width1*10, height1*6, black, true);

	DrawExtendGraph(10, (height1 * 7) + 20, 300, (height1 * 7) + 30, hp_bar_back, false);
	DrawExtendGraph(10, (height1 * 7) + 20, (hp_now / hp_max) * 300, (height1 * 7) + 30, hp_bar, false);

	DrawStringEx(1300, 20, -1, "scene battle");
	DrawStringEx(1300, 40, -1, "%d", select_move);
	DrawStringEx(1300, 60, -1, "X:%d Y:%d", MouseX, MouseY);
	//DrawStringEx(10, height1 * 7, 1, "HP:%d",);
	//DrawStringEx(10, height1 * 7 + 40, 1, "Cost:%d/%d", pmgr->person2->COST, pmgr_->person2->COST);
}

void SceneBattle::DrawCard(int x, int y, int x2, int y2, int chara, bool flag)
{
	DrawExtendGraph(width1 * x, (height1 * y), width1 * x2, (height1 * y2), chara, flag);


}

void SceneBattle::BattleStart()
{

}



void SceneBattle::DrawHands() {
	if (numOfCards == 1) {
		//DrawExtendGraph(512 + 320, (height1 * 7) - CardUp_1, 512 + cardW + 320, (height1 * 10) - CardUp_1, card1, false); //1
		EaseImageCard1(easeOutExpo(t),0, 832, 0);
	}
	else if (numOfCards == 2) {
	    //DrawExtendGraph(center - cardW, (height1 * 7) - CardUp_1,center, (height1 * 10) - CardUp_1, card1, false); //1
		//DrawExtendGraph(center, (height1 * 7) - CardUp_2, center + cardW, (height1 * 10) - CardUp_2, card2, false); //2
		if (t < 0.5) {
			EaseImageCard1(easeOutExpo(t), 0, center - cardW, 0);
		}
		else {
			EaseImageCard1(easeOutExpo(t), 0, center, 0);
		}
	

	}
	else if (numOfCards == 3) {
		DrawExtendGraph(center - 128 - cardW, (height1 * 7) - CardUp_1, center - 128, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(center - 128, (height1 * 7) - CardUp_2, center + 128, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(center + 128, (height1 * 7) - CardUp_3, center + 128 + cardW , (height1 * 10) - CardUp_3, card3, false); //3
	}
	else if (numOfCards == 4) {
		DrawExtendGraph(center - (cardW * 2), (height1 * 7) - CardUp_1, center - cardW, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(center - cardW, (height1 * 7) - CardUp_2, center, (height1 * 10) - CardUp_2, card1, false); //2
		DrawExtendGraph(center, (height1 * 7) - CardUp_3, center + cardW, (height1 * 10) - CardUp_3, card2, false); //3
		DrawExtendGraph(center + cardW, (height1 * 7) - CardUp_4, center + (cardW * 2), (height1 * 10) - CardUp_4, card4, false); //4
	}
	else if (numOfCards == 5) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088, (height1 * 7) - CardUp_4, 1344, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344, (height1 * 7) - CardUp_5, 1600, (height1 * 10) - CardUp_5, card4, false); //5
	}
	else if (numOfCards == 6) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPidl_6, (height1 * 7) - CardUp_2, 832 - cardPidl_6, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPidl_6 * 2, (height1 * 7) - CardUp_3, 1088 - cardPidl_6 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPidl_6 * 3, (height1 * 7) - CardUp_4, 1344 - cardPidl_6 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPidl_6 * 4, (height1 * 7) - CardUp_5, 1600 - cardPidl_6 * 4, (height1 * 10) - CardUp_5, card4, false); //5
		DrawExtendGraph(1600 - cardPidl_6 * 5, (height1 * 7) - CardUp_6, 1600, (height1 * 10) - CardUp_6, card4, false); //6
	}
	else if (numOfCards == 7) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_7, (height1 * 7) - CardUp_2, 832 - cardPild_7, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_7 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_7 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_7 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_7 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_7 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_7 * 4, (height1 * 10) - CardUp_5, card4, false); //5
		DrawExtendGraph(1600 - cardPild_7 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_7 * 5, (height1 * 10) - CardUp_6, card4, false); //6
		DrawExtendGraph(1600 + (256) - cardPild_7 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_7 * 6, (height1 * 10) - CardUp_7, card4, false); //7
	}
	else if (numOfCards == 8) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_8, (height1 * 7) - CardUp_2, 832 - cardPild_8, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_8 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_8 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_8 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_8 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_8 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_8 * 4, (height1 * 10) - CardUp_5, card4, false); //5	

		DrawExtendGraph(1600 - cardPild_8 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_8 * 5, (height1 * 10) - CardUp_6, card4, false); //6		
		DrawExtendGraph(1600 + (256) - cardPild_8 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_8 * 6, (height1 * 10) - CardUp_7, card4, false); //7
		DrawExtendGraph(1600 + (256 * 2) - cardPild_8 * 7, (height1 * 7) - CardUp_8, 1600 + (256 * 3) - cardPild_8 * 7, (height1 * 10) - CardUp_8, card4, false); //8		
	}
	else if (numOfCards == 9) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_9, (height1 * 7) - CardUp_2, 832 - cardPild_9, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_9 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_9 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_9 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_9 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_9 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_9 * 4, (height1 * 10) - CardUp_5, card4, false); //5

		DrawExtendGraph(1600 - cardPild_9 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_9 * 5, (height1 * 10) - CardUp_6, card4, false); //6
		DrawExtendGraph(1600 + (256) - cardPild_9 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_9 * 6, (height1 * 10) - CardUp_7, card4, false); //7
		DrawExtendGraph(1600 + (256 * 2) - cardPild_9 * 7, (height1 * 7) - CardUp_8, 1600 + (256 * 3) - cardPild_9 * 7, (height1 * 10) - CardUp_8, card4, false); //8
		DrawExtendGraph(1600 + (256 * 3) - cardPild_9 * 8, (height1 * 7) - CardUp_9, 1600 + (256 * 4) - cardPild_9 * 8, (height1 * 10) - CardUp_9, card4, false); //9

	}
	else if (numOfCards == 10) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_10, (height1 * 7) - CardUp_2, 832 - cardPild_10, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_10 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_10 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_10 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_10 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_10 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_10 * 4, (height1 * 10) - CardUp_5, card4, false); //5

		DrawExtendGraph(1600 - cardPild_10 * 5, (height1 * 7) - CardUp_6, 1600 + (256) - cardPild_10 * 5, (height1 * 10) - CardUp_6, card4, false); //6
		DrawExtendGraph(1600 + (256) - cardPild_10 * 6, (height1 * 7) - CardUp_7, 1600 + (256 * 2) - cardPild_10 * 6, (height1 * 10) - CardUp_7, card4, false); //7
		DrawExtendGraph(1600 + (256 * 2) - cardPild_10 * 7, (height1 * 7) - CardUp_8, 1600 + (256 * 3) - cardPild_10 * 7, (height1 * 10) - CardUp_8, card4, false); //8
		DrawExtendGraph(1600 + (256 * 3) - cardPild_10 * 8, (height1 * 7) - CardUp_9, 1600 + (256 * 4) - cardPild_10 * 8, (height1 * 10) - CardUp_9, card4, false); //9
		DrawExtendGraph(1600 + (256 * 4) - cardPild_10 * 9, (height1 * 7) - CardUp_10, 1600 + (256 * 5) - cardPild_10 * 9, (height1 * 10) - CardUp_10, card4, false); //10

	}
}

void SceneBattle::drawCardUp(int x, int y) {

	if (numOfCards == 1) {
		if (512 + 320 < MouseX && MouseX < 512 + cardW + 320 && (height1 * 7) < MouseY && MouseY < (height1 * 10)) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}
	}

	if (numOfCards == 2) {
		
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

	if (numOfCards == 3) {
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

	if (numOfCards == 4) {
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

	if (numOfCards == 5) {

		if (320 < MouseX && MouseX < 576 && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_1 = 45;
		}
		else {
			CardUp_1 = 0;
		}

		if (576 < MouseX && MouseX < 832  && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
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

		if (1344  < MouseX && MouseX < 1600  && height1 * 7 <= MouseY && MouseY <= height1 * 10) {
			CardUp_5 = 45;
		}
		else {
			CardUp_5 = 0;
		}

	}

	if (numOfCards == 6) {
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

	if (numOfCards == 7) {

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

	if (numOfCards == 8) {

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

	if (numOfCards == 9) {

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

	if (numOfCards == 10) {

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

	card1 = LoadGraph("graphics/card_1.png"); //誘導
	card2 = LoadGraph("graphics/card_2.png"); //斬りつける
	card3 = LoadGraph("graphics/card_3.png"); //逃げる
	card4 = LoadGraph("graphics/card_4.png"); //守る
	card5 = LoadGraph("graphics/card_5.png"); //鼓舞
	card6 = LoadGraph("graphics/card_6.png"); //分析
	card7 = LoadGraph("graphics/card_7.png"); //ポジションチェンジ
	card8 = LoadGraph("graphics/card_8.png"); //ファイア
	card9 = LoadGraph("graphics/card_9.png"); //ヒール
	card10 = LoadGraph("graphics/card_10.png"); //盾を構える
	card11 = LoadGraph("graphics/card_11.png"); //指摘
	card12 = LoadGraph("graphics/card_12.png"); //状態異常回復
	card13 = LoadGraph("graphics/card_13.png"); //クイック
	card14 = LoadGraph("graphics/card_14.png"); //戦闘準備
	card15 = LoadGraph("graphics/card_15.png"); //挑発

	hp_bar = LoadGraph("graphics/hp_bar.png"); //hpバー
	hp_bar_back = LoadGraph("graphics/hp_bar_back.png"); //hp_barの後ろのバー

	img_yourturn = LoadGraph("graphics/img_yourturn2.png"); //yourターン描写
	img_enemyturn = LoadGraph("graphics/img_enemyturn2.png"); //enemyターン描写

	img_turn = LoadGraph("graphics/turn.png"); //turn描写用
	select_flame = LoadGraph("graphics/select_flame.png"); //選択描写用
}