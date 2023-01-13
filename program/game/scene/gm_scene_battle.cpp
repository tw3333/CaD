#include "../gm_manager.h"

#include "gm_scene_play.h"
#include "gm_scene_battle.h"

#include <iostream>
#include <cmath>

//SceneBattle::~SceneBattle() {
//	
//}

void SceneBattle::initialzie() {


	LoadBattleGraph();

	finish = false;
	dealcard = false;

	enemy_anime = true;
	chara_num = 1;
	img_turn_move = 25;

	hp_now = hp_max;
	int x = 320;

}

void SceneBattle::update(float dalta_time) {
	GameManager* mgr = GameManager::GetInstance();

	BattleStart();

	//簡易敵アニメーション 
	timer += 0.1 * 1;
	move += 2 * sin(timer);

	GetMousePoint(&MouseX, &MouseY);
	drawMouseUp(MouseX, MouseY);

	//シーン切り替え
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new ScenePlay());
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
		hp_now -= 1;
	}

	//test
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
		dealcard = true;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_U)) {
		numOfCards += 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) {
		numOfCards -= 1;
	}

	t += dt;
	if (1 <= t) {
		t = 1;
	}
}

void SceneBattle::render() {


	//レイアウト決め
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

	//ターンの画像
	DrawGraph(0, 0, img_turn, false);

	DrawExtendGraph(0, height1 * 2, width1 * 2, height1 * 3, img_enemy1_face, false);

	DrawExtendGraph(0 + 25, 0, width1 * 2 + 25, height1 * 1, img_chara1_face, false);
	DrawExtendGraph(0, height1 * 2, width1 * 2, height1 * 3, img_enemy1_face, false);
	DrawExtendGraph(0, height1 * 2, width1 * 2, height1 * 3, img_enemy1_face, false);

	//DrawLine(0,height1*2, width1*4, height1* 2,red);

	DrawLine(width1 * 2, 0, width1 * 2, height1 * 4, red);
	DrawLine(0, 0, width1 * 2, 0, red);
	DrawLine(0, height1 * 1, width1 * 2, height1 * 1, red);
	DrawLine(0, height1 * 2, width1 * 2, height1 * 2, red);
	DrawLine(0, height1 * 3, width1 * 2, height1 * 3, red);
	DrawLine(0, height1 * 4, width1 * 2, height1 * 4, red);

	DrawBox(0, height1 * 7, width1 * 2, height1 * 10, Silver, true);

	//手札描写
	DrawHands();

	//ターン描写
	//DrawExtendGraph(width1*4,height1*3,width1*6,height1*4,img_yourturn,true);
	EasingTurnImage(easeInExpo(t),0,width1*4);

	//選択フレーム
	//DrawCard(0 + select_move, 7, 2 + select_move, 10, select_flame, true);

	//カード置き場
	//DrawBox(0, height1 * 7, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, GetColor(138, 140, 142), false);


	DrawExtendGraph(10, (height1 * 7) + 20, 300, (height1 * 7) + 30, hp_bar_back, false);
	DrawExtendGraph(10, (height1 * 7) + 20, (hp_now / hp_max) * 300, (height1 * 7) + 30, hp_bar, false);

	DrawStringEx(1300, 50, -1, "scene battle");
	DrawStringEx(1300, 70, -1, "%d", select_move);
	DrawStringEx(1300, 90, -1, "X:%d Y:%d", MouseX, MouseY);
	DrawStringEx(10, height1 * 7, 1, "HP:%d", hp_now);
	DrawStringEx(10, height1 * 7 + 40, 1, "Cost:%d/%d", cost_now, cost_max);
}

void SceneBattle::DrawCard(int x, int y, int x2, int y2, int chara, bool flag)
{
	DrawExtendGraph(width1 * x, (height1 * y), width1 * x2, (height1 * y2), chara, flag);


}

void SceneBattle::BattleStart()
{

}

void SceneBattle::LoadBattleGraph() {
	img_background = LoadGraph("graphics/background2.png");
	img_mon1 = LoadGraph("graphics/m1.png");
	img_chara1_face = LoadGraph("graphics/chara1_face.png"); //冒険者
	img_chara2_face = LoadGraph("graphics/chara2_face.png"); //シーフ
	img_chara3_face = LoadGraph("graphics/chara3_face.png"); //重騎士
	img_chara4_face = LoadGraph("graphics/chara4_face.png"); //回復士
	img_enemy1_face = LoadGraph("graphics/enemy1_face.png"); //デブアリ

	card1 = LoadGraph("graphics/card_chara1_flame.png"); //誘導
	card2 = LoadGraph("graphics/card_chara1_flame.png"); //斬りつける
	card3 = LoadGraph("graphics/card_chara1_flame.png"); //逃げる
	card4 = LoadGraph("graphics/card_chara1_flame.png"); //守る
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

void SceneBattle::DrawHands() {
	if (numOfCards == 1) {
		DrawExtendGraph(640 - 128 + 320, (height1 * 7) - CardUp_1, 640 + 128 + 320, (height1 * 10) - CardUp_1, card1, false); //1

	}
	else if (numOfCards == 2) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, card2, false); //2
	}
	else if (numOfCards == 3) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, card3, false); //3
	}
	else if (numOfCards == 4) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088, (height1 * 7) - CardUp_4, 1344, (height1 * 10) - CardUp_4, card4, false); //4
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
		DrawExtendGraph(1600 - cardPidl_6 * 5, (height1 * 7) - CardUp_5, 1600, (height1 * 10) - CardUp_5, card4, false); //6
	}
	else if (numOfCards == 7) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_7, (height1 * 7) - CardUp_2, 832 - cardPild_7, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_7 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_7 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_7 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_7 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_7 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_7 * 4, (height1 * 10) - CardUp_5, card4, false); //5
		DrawExtendGraph(1600 - cardPild_7 * 5, (height1 * 7) - CardUp_5, 1600 + (256) - cardPild_7 * 5, (height1 * 10) - CardUp_5, card4, false); //6
		DrawExtendGraph(1600 + (256) - cardPild_7 * 6, (height1 * 7) - CardUp_5, 1600 + (256*2) - cardPild_7* 6, (height1 * 10) - CardUp_5, card4, false); //7
	}
	else if (numOfCards == 8) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_8, (height1 * 7) - CardUp_2, 832 - cardPild_8, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_8 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_8 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_8 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_8 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_8 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_8 * 4, (height1 * 10) - CardUp_5, card4, false); //5	

		DrawExtendGraph(1600 - cardPild_8 * 5, (height1 * 7) - CardUp_5, 1600 + (256) - cardPild_8 * 5, (height1 * 10) - CardUp_5, card4, false); //6		
		DrawExtendGraph(1600 + (256) - cardPild_8 * 6, (height1 * 7) - CardUp_5, 1600 + (256 * 2) - cardPild_8 * 6, (height1 * 10) - CardUp_5, card4, false); //7
		DrawExtendGraph(1600 + (256 * 2) - cardPild_8 * 7, (height1 * 7) - CardUp_5, 1600 + (256 * 3) - cardPild_8 * 7, (height1 * 10) - CardUp_5, card4, false); //8		
	}
	else if (numOfCards == 9) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_9, (height1 * 7) - CardUp_2, 832 - cardPild_9, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_9 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_9 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_9 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_9 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_9 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_9 * 4, (height1 * 10) - CardUp_5, card4, false); //5

		DrawExtendGraph(1600 - cardPild_9 * 5, (height1 * 7) - CardUp_5, 1600 + (256) - cardPild_9 * 5, (height1 * 10) - CardUp_5, card4, false); //6
		DrawExtendGraph(1600 + (256) - cardPild_9 * 6, (height1 * 7) - CardUp_5, 1600 + (256 * 2) - cardPild_9 * 6, (height1 * 10) - CardUp_5, card4, false); //7
		DrawExtendGraph(1600 + (256 * 2) - cardPild_9 * 7, (height1 * 7) - CardUp_5, 1600 + (256 * 3) - cardPild_9 * 7, (height1 * 10) - CardUp_5, card4, false); //8
		DrawExtendGraph(1600 + (256 * 3) - cardPild_9 * 8, (height1 * 7) - CardUp_5, 1600 + (256 * 4) - cardPild_9 * 8, (height1 * 10) - CardUp_5, card4, false); //9

	}
	else if (numOfCards == 10) {
		DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
		DrawExtendGraph(576 - cardPild_10, (height1 * 7) - CardUp_2, 832 - cardPild_10, (height1 * 10) - CardUp_2, card2, false); //2
		DrawExtendGraph(832 - cardPild_10 * 2, (height1 * 7) - CardUp_3, 1088 - cardPild_10 * 2, (height1 * 10) - CardUp_3, card3, false); //3
		DrawExtendGraph(1088 - cardPild_10 * 3, (height1 * 7) - CardUp_4, 1344 - cardPild_10 * 3, (height1 * 10) - CardUp_4, card4, false); //4
		DrawExtendGraph(1344 - cardPild_10 * 4, (height1 * 7) - CardUp_5, 1600 - cardPild_10 * 4, (height1 * 10) - CardUp_5, card4, false); //5

		DrawExtendGraph(1600 - cardPild_10 * 5, (height1 * 7) - CardUp_5, 1600 + (256) - cardPild_10 * 5, (height1 * 10) - CardUp_5, card4, false); //6
		DrawExtendGraph(1600 + (256) - cardPild_10 * 6, (height1 * 7) - CardUp_5, 1600 + (256 * 2) - cardPild_10 * 6, (height1 * 10) - CardUp_5, card4, false); //7
		DrawExtendGraph(1600 + (256 * 2) - cardPild_10 * 7, (height1 * 7) - CardUp_5, 1600 + (256 * 3) - cardPild_10 * 7, (height1 * 10) - CardUp_5, card4, false); //8
		DrawExtendGraph(1600 + (256 * 3) - cardPild_10 * 8, (height1 * 7) - CardUp_5, 1600 + (256 * 4) - cardPild_10 * 8, (height1 * 10) - CardUp_5, card4, false); //9
		DrawExtendGraph(1600 + (256 * 4) - cardPild_10 * 9, (height1 * 7) - CardUp_5, 1600 + (256 * 5) - cardPild_10 * 9, (height1 * 10) - CardUp_5, card4, false); //10

	}
}

void SceneBattle::drawMouseUp(int x, int y) {
	if (320 <= x && x <= 576 && 630 <= y && y <= 900) {
		CardUp_1 = 45;
	}
	else {
		CardUp_1 = 0;
	}

	if (576 <= x && x <= 832 && 630 <= y && y <= 900) {
		CardUp_2 = 45;
	}
	else {
		CardUp_2 = 0;
	}

	if (832 <= x && x <= 1088 && 630 <= y && y <= 900) {
		CardUp_3 = 45;
	}
	else {
		CardUp_3 = 0;
	}

	if (1088 <= x && x <= 1344 && 630 <= y && y <= 900) {
		CardUp_4 = 45;
	}
	else {
		CardUp_4 = 0;
	}

	if (1344 <= x && x <= 1600 && 630 <= y && y <= 900) {
		CardUp_5 = 45;
	}
	else {
		CardUp_5 = 0;
	}

}

double SceneBattle::easeInExpo(double x) {
	if (x == 0) { return 0; }
	return pow(2, 10 * x -10);
}

void SceneBattle::EasingTurnImage(double t, int x_s, int x_e) {
	auto x = (1 - t) * x_s + t * x_e;
	DrawExtendGraph(x, height1 * 3, x + width1*2, height1 * 4, img_yourturn, true);
}