#pragma once

class Chara {
public:
	Chara() {}
	~Chara(){}


private:
	struct chara {

		int hp = 0;
		int cost = 0;
		int speed = 0;
		int hate = 0;

		bool burn = false;
		bool poison = false;



		int hands = 0; //��D

		int card_deck[15]; //�f�b�L
		int img_chara = 0; // �摜�n���h��
	};


};
