#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include <vector>
#include <string>

class Person {
public:
	Person(int hp, int hpmax, int cost,int costmax, int speed)
	 : HP(hp), HPMAX(hpmax), COST(cost),COSTMAX(costmax), SPEED(speed) {}

	//�e�X�g�X�e�[�^�X
	int HP; //HP
	int HPMAX; //�ő�HP
	int COST; //�R�X�g
	int COSTMAX; //�ő�R�X�g
	int SPEED; //�^�[�����ʂɎg�p����f����


private:

	


};


