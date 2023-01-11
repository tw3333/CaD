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
}

void SceneBattle::update(float dalta_time) {
	GameManager* mgr = GameManager::GetInstance();

	BattleStart();

	//�ȈՓG�A�j���[�V���� 
	timer += 0.1 * 1;
	move += 2 * sin(timer);

	

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

}

void SceneBattle::render() {


	//���C�A�E�g����
	//�w�i
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, height1 * 7, img_background, true);

	//�G
	//DrawBox(width1 * 4, height1, width1 * 6, height1 * 5, GetColor(138, 140, 142), false);
	DrawExtendGraph(width1 * 4, height1 + move, width1 * 6, height1 * 5 + move, img_mon1, false);

	//DrawLine(0,height1,DXE_WINDOW_WIDTH,height1,0);

	//�O���b�h���C��
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}




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



	//�s���I��
	DrawBox(0, height1 * 7, width1 * 2, height1 * 10, gray, false); //1
	//DrawExtendGraph(0, height1 * 7, width1 * 2, height1 * 10, img_card1, false);

	DrawCard(0, 7, 2, 10, card1, false);

	DrawBox(width1 * 2, height1 * 7, width1 * 4, height1 * 10, gray, false); //2
	DrawExtendGraph(width1 * 2, height1 * 7, width1 * 4, height1 * 10, card1, false); //2

	DrawBox(width1 * 4, height1 * 7, width1 * 6, height1 * 10, gray, false); //3
	DrawExtendGraph(width1 * 4, height1 * 7, width1 * 6, height1 * 10, card2, false); //3

	DrawBox(width1 * 6, height1 * 7, width1 * 8, height1 * 10, gray, false); //4
	DrawExtendGraph(width1 * 6, height1 * 7, width1 * 8, height1 * 10, card3, false); //4

	DrawBox(width1 * 8, height1 * 7, width1 * 10, height1 * 10, gray, false); //5
	DrawExtendGraph(width1 * 8, height1 * 7, width1 * 10, height1 * 10, card4, false); //5

	//�I���t���[��
	DrawCard(0 + select_move, 7, 2 + select_move, 10, select_flame, true);

	//�J�[�h�u����
	DrawBox(0, height1 * 7, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, GetColor(138, 140, 142), false);

	DrawStringEx(900, 50, -1, "scene battle");
	DrawStringEx(900, 70, -1, "%d", select_move);
}

void SceneBattle::DrawCard(int x, int y, int x2, int y2, int chara, bool flag)
{
	DrawExtendGraph(width1 * x, height1 * y, width1 * x2, height1 * y2, chara, flag);
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


	img_turn = LoadGraph("graphics/turn.png"); //turn�`�ʗp
	select_flame = LoadGraph("graphics/select_flame.png"); //�I��`�ʗp
}