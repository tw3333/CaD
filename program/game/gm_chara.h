#pragma once
#include <vector>
#include "../dxlib_ext/dxlib_ext.h"

class Chara {
public:
	Chara() {
		chara01_h = LoadGraph("graphics/chara1_face.png");
		chara02_h = LoadGraph("graphics/chara2_face.png");
		chara03_h = LoadGraph("graphics/chara3_face.png");
		chara04_h = LoadGraph("graphics/chara4_face.png");

		chara chara_[4] = {
			{"chara1","���E���_�[",50,3,30,10,false,false,5,chara01_h},
			{"chara2","�V�[�t"    ,40,3,35,10,false,false,5,chara02_h},
			{"chara3","�d�R�m"    ,60,3,20,10,false,false,5,chara03_h},
			{"chara4","�񕜎m"    ,40,3,25,15,false,false,5,chara04_h},
		};
	}

	~Chara(){}

	struct chara {

		char Name[100]; //���O
		char J_Name[100]; //�E��
		int hp = 0;
		int cost = 0;
		int speed = 0;
		int hate = 0;

		bool burn = false;
		bool poison = false;

		int hands = 0; //��D
		//int card_deck[15]; //�f�b�L
		int img_chara = 0; // �摜�n���h��
	};

	

private:
	
	//�O���t�B�b�N�p�n���h��
	int chara01_h = 0;
	int chara02_h = 0;
	int chara03_h = 0;
	int chara04_h = 0;


};
