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
			{"chara1","ラウンダー",50,3,30,10,false,false,5,chara01_h},
			{"chara2","シーフ"    ,40,3,35,10,false,false,5,chara02_h},
			{"chara3","重騎士"    ,60,3,20,10,false,false,5,chara03_h},
			{"chara4","回復士"    ,40,3,25,15,false,false,5,chara04_h},
		};
	}

	~Chara(){}

	struct chara {

		char Name[100]; //名前
		char J_Name[100]; //職業
		int hp = 0;
		int cost = 0;
		int speed = 0;
		int hate = 0;

		bool burn = false;
		bool poison = false;

		int hands = 0; //手札
		//int card_deck[15]; //デッキ
		int img_chara = 0; // 画像ハンドル
	};

	

private:
	
	//グラフィック用ハンドル
	int chara01_h = 0;
	int chara02_h = 0;
	int chara03_h = 0;
	int chara04_h = 0;


};
