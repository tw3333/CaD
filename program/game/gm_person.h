#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include <vector>
#include <string>

class Person {
public:
	
	Person(int hp, int cost) : HP(hp), COST(cost) {}


	~Person(){}
	
	
	//公開で書いてみる
	int HP;
	int COST;

	//想定しているステータス
	char NAME[20]; //名前
	int SPEED; //ターン順位に使用する素早さ
	int LEVEL; //レベル
	int EXP; //経験値
	int DECK_MAX; //山札にもてるカードの最大数


	
private:

	

};

