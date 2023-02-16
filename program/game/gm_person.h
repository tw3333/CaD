#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_card.h"
#include <vector>
#include <string>

class Person {
public:
	
	Person(int hp, int hpmax, int cost, int costmax, int speed, bool pick, bool edit)
	 : HP(hp), HPMAX(hpmax), COST(cost),COSTMAX(costmax), SPEED(speed),PICK(pick),EDIT(edit) {}

	//�e�X�g�X�e�[�^�X
	int HP; //HP
	int HPMAX; //�ő�HP
	int COST; //�R�X�g
	int COSTMAX; //�ő�R�X�g
	int SPEED; //�^�[�����ʂɎg�p����f����
	bool PICK = false;
	bool EDIT = false;

	
	std::vector<Card*> deck; //�R�D
	std::vector<Card*> hands; //��D
	std::vector<Card*> possCardList; //���̃L�������������Ă���J�[�h�ꗗ





	//�����\��X�e�[�^�X
	bool isBurn = false; //�R���Ă��邩�ǂ���
	bool isPoison = false; //�ŏ�Ԃ��ǂ���
	int hate = 0; //�w�C�g


private:

	


};


