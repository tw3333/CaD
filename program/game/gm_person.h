#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include <vector>
#include <string>

class Person {
public:
	
	Person(int hp, int cost) : HP(hp), COST(cost) {}


	~Person(){}
	
	
	//���J�ŏ����Ă݂�
	int HP;
	int COST;

	//�z�肵�Ă���X�e�[�^�X
	char NAME[20]; //���O
	int SPEED; //�^�[�����ʂɎg�p����f����
	int LEVEL; //���x��
	int EXP; //�o���l
	int DECK_MAX; //�R�D�ɂ��Ă�J�[�h�̍ő吔


	
private:

	

};

