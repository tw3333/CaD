#include "../gm_manager.h"

#include "gm_scene_play.h"
#include "gm_scene_battle.h"

#include <iostream>

//SceneBattle::~SceneBattle() {
//	
//}

void SceneBattle::initialzie() {

	
	LoadBattleGraph();

	finish = false;

	enemy_anime = true;
	chara_num = 1;
	img_turn_move = 25;

	hp_now = hp_max;
}

void SceneBattle::update(float dalta_time) {
	GameManager* mgr = GameManager::GetInstance();

	BattleStart();

	//�ȈՓG�A�j���[�V���� 
	timer += 0.1 * 1;
	move += 2 * sin(timer);

	GetMousePoint(&MouseX, &MouseY);
	drawMouseUp(MouseX, MouseY);

	//�V�[���؂�ւ�
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
	
	
	
	
	

}

void SceneBattle::render() {


	//���C�A�E�g����
	//�w�i
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, height1 * 10, img_background, true);

	//�G
	//DrawBox(width1 * 4, height1, width1 * 6, height1 * 5, GetColor(138, 140, 142), false);
	DrawExtendGraph(width1 * 4, height1 + move, width1 * 6, height1 * 5 + move, img_mon1, false);

	//DrawLine(0,height1,DXE_WINDOW_WIDTH,height1,0);

	//�O���b�h���C��
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}


	//drawMouseUp(MouseX, MouseY);

	//�s���L�����\��
	DrawBox(0, height1 * 6, width1 * 2, height1 * 7, gray, false);
	DrawExtendGraph(0, height1 * 6, width1 * 2, height1 * 7, chara_select, false);



	//�s��������
	//DrawBox(0, 0, width1 * 2, height1 * 4, red, false);

	//�^�[���̉摜
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

	//�J�[�h�`��(��D�T��)
	DrawExtendGraph(320, (height1 * 7) - CardUp_1, 576, (height1 * 10) - CardUp_1, card1, false); //1
	DrawExtendGraph(576, (height1 * 7) - CardUp_2, 832, (height1 * 10) - CardUp_2, card2, false); //2
	DrawExtendGraph(832, (height1 * 7) - CardUp_3, 1088, (height1 * 10) - CardUp_3, card3, false); //3
	DrawExtendGraph(1088, (height1 * 7) - CardUp_4, 1344, (height1 * 10) - CardUp_4, card4, false); //4
	DrawExtendGraph(1344, (height1 * 7) - CardUp_5, 1600, (height1 * 10) - CardUp_5, card4, false); //5



	//�I���t���[��
	//DrawCard(0 + select_move, 7, 2 + select_move, 10, select_flame, true);

	//�J�[�h�u����
	//DrawBox(0, height1 * 7, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, GetColor(138, 140, 142), false);

	
	DrawExtendGraph(10, (height1 * 7) + 20, 300, (height1 * 7) + 30, hp_bar_back, false);
	DrawExtendGraph(10, (height1 * 7) + 20, (hp_now / hp_max) * 300 , (height1 * 7) + 30, hp_bar, false);

	DrawStringEx(1300, 50, -1, "scene battle");
	DrawStringEx(1300, 70, -1, "%d", select_move);
	DrawStringEx(1300,90,-1,"X:%d Y:%d", MouseX, MouseY);
	DrawStringEx(10,height1*7,1,"HP:%d",hp_now);
	DrawStringEx(10,height1*7 + 40,1,"Cost:%d/%d",cost_now,cost_max);
}

void SceneBattle::DrawCard(int x, int y, int x2, int y2, int chara, bool flag)
{
	DrawExtendGraph(width1 * x, (height1 * y)  , width1 * x2, (height1 * y2)  , chara, flag);

	
}

void SceneBattle::BattleStart()
{

}

void SceneBattle::LoadBattleGraph() {
	img_background = LoadGraph("graphics/background2.png");
	img_mon1 = LoadGraph("graphics/m1.png");
	img_chara1_face = LoadGraph("graphics/chara1_face.png"); //�`����
	img_chara2_face = LoadGraph("graphics/chara2_face.png"); //�V�[�t
	img_chara3_face = LoadGraph("graphics/chara3_face.png"); //�d�R�m
	img_chara4_face = LoadGraph("graphics/chara4_face.png"); //�񕜎m
	img_enemy1_face = LoadGraph("graphics/enemy1_face.png"); //�f�u�A��

	card1 = LoadGraph("graphics/card_1.png"); //�U��
	card2 = LoadGraph("graphics/card_2.png"); //�a�����
	card3 = LoadGraph("graphics/card_3.png"); //������
	card4 = LoadGraph("graphics/card_4.png"); //���
	card5 = LoadGraph("graphics/card_5.png"); //�ە�
	card6 = LoadGraph("graphics/card_6.png"); //����
	card7 = LoadGraph("graphics/card_7.png"); //�|�W�V�����`�F���W
	card8 = LoadGraph("graphics/card_8.png"); //�t�@�C�A
	card9 = LoadGraph("graphics/card_9.png"); //�q�[��
	card10 = LoadGraph("graphics/card_10.png"); //�����\����
	card11 = LoadGraph("graphics/card_11.png"); //�w�E
	card12 = LoadGraph("graphics/card_12.png"); //��Ԉُ��
	card13 = LoadGraph("graphics/card_13.png"); //�N�C�b�N
	card14 = LoadGraph("graphics/card_14.png"); //�퓬����
	card15 = LoadGraph("graphics/card_15.png"); //����

	hp_bar = LoadGraph("graphics/hp_bar.png"); //hp�o�[
	hp_bar_back = LoadGraph("graphics/hp_bar_back.png"); //hp_bar�̌��̃o�[

	img_turn = LoadGraph("graphics/turn.png"); //turn�`�ʗp
	select_flame = LoadGraph("graphics/select_flame.png"); //�I��`�ʗp
}

void SceneBattle::drawMouseUp(int x, int y) {
	if (320 <= x && x <=  576 &&  630 <= y && y <= 900 ) {
		CardUp_1 = 45;
	}
	else {
		CardUp_1 = 0;
	}

	if ( 576<= x && x <= 832 && 630 <= y && y <= 900) {
		CardUp_2 = 45;
	} else{
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

