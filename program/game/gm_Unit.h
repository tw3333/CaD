#pragma once

//Person��Enemy�̊��N���X
//SceneBattle�̑����v�Z���Ƀ|�C���^�̔z����������邽�߂ɍ����
//TODO:�p�����������������ǂ����v����


class Unit {
public:
	
	
	//Peson��Enemy�̋��ʃX�e�[�^�X
	int SPEED;

	bool isEnemy = false; //�G���ǂ���
	bool isActed = false; //�s���ς݂��ǂ���
	bool isDead = false; //����ł邩�ǂ���



	virtual ~Unit(){};

};