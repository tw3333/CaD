#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include <vector>
#include <string>

class Person {
public:
	Person(int hp, int hpmax, int cost,int costmax, int speed)
	 : HP(hp), HPMAX(hpmax), COST(cost),COSTMAX(costmax), SPEED(speed) {}

	//テストステータス
	int HP; //HP
	int HPMAX; //最大HP
	int COST; //コスト
	int COSTMAX; //最大コスト
	int SPEED; //ターン順位に使用する素早さ


private:

	


};


