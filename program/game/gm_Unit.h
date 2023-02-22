#pragma once
#include <vector>
#include "gm_card.h"



//Person��Enemy�̊��N���X
//SceneBattle�̑����v�Z���Ƀ|�C���^�̔z����������邽�߂ɍ����
//TODO:�p�����������������ǂ����v����

class Card;

class Unit {
public:
	
	virtual int getSPEED() const { return SPEED; }
	virtual void setSPEED(int SPEED) { SPEED = SPEED; }
	
	virtual bool getIsEnemy() const { return isEnemy; }
	virtual void setIsEnemy(bool f) { isEnemy = f; }

	virtual bool getIsActed() const { return isActed; }
	virtual void setIsActed(bool f) { isActed = f; }

	virtual bool getIsDead() const { return isEnemy; }
	virtual void setIsDead(bool f) { isDead = f; }

	virtual std::vector<Card*> getDeck() const { return deck; }
	virtual std::vector<Card*> getHand() const { return hand; }


	virtual ~Unit(){};

protected:
	
	//Peson��Enemy�̋��ʃX�e�[�^�X
	int SPEED = 0;

	std::vector<Card*> deck; //�R�D
	std::vector<Card*> hand; //��D

	bool isEnemy = false; //�G���ǂ���
	bool isActed = false; //�s���ς݂��ǂ���
	bool isDead = false; //����ł邩�ǂ���


};