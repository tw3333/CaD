#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_card.h"
#include <vector>
#include <string>
#include "gm_unit.h"



//�N���X�̖��O��chara����Person��(chara����char�^�̐錾�ƊԈႦ�₷������)
//TODO:�J�v�Z����

class Person : public Unit{
public:
	
	//�R���X�g���N�^
	Person(int hp, int hpmax, int cost, int costmax, int speed, bool pick, bool edit, int graph)
	 : HP(hp), HPMAX(hpmax), COST(cost),COSTMAX(costmax), SPEED(speed),PICK(pick),EDIT(edit), GRAPH(graph) {}



	//�e�X�g�X�e�[�^�X
	int HP; //HP
	int HPMAX; //�ő�HP
	int COST; //�R�X�g
	int COSTMAX; //�ő�R�X�g
	int SPEED; //�^�[�����ʂɎg�p����f����
	bool PICK = false;
	bool EDIT = false;
	
	bool isActed = false; //�s���ς݂��ǂ���
	bool isDead = false; //����ł邩�ǂ���

	int GRAPH = 0;

	bool isEnemy = false; //�G���ǂ���

	int dealHandNum = 5;

	//SceneBattle�Ŏg�p
	std::vector<Card*> deck; //�R�D
	std::vector<Card*> hand; //��D


	//SceneDeckEdit�Ŏg�p
	std::vector<Card*> cardList; //���̃L�������������Ă���J�[�h�ꗗ





	//�����\��X�e�[�^�X
	bool isBurn = false; //�R���Ă��邩�ǂ���
	bool isPoison = false; //�ŏ�Ԃ��ǂ���
	int hate = 0; //�w�C�g

	//getter setter
	int getSPEED() const override { return SPEED; }
	void setSPEED(int speed) override { SPEED = speed; }

	bool getIsEnemy() const override { return isEnemy; }
	void setIsEnemy(bool f) override { isEnemy = f; }

	bool getIsActed() const override { return isActed; }
	void setIsActed(bool f) override { isActed = f; }

	bool getIsDead() const override { return isDead; }
	void setIsDead(bool f) override { isDead = f; }

	std::vector<Card*>& getDeck() { return deck; }
	std::vector<Card*>& getHand() { return hand; }


private:

	


};


