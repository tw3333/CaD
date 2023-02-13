#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_card.h"
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


	
	std::vector<Card*> deck; //山札
	std::vector<Card*> hands; //手札
	std::vector<Card*> possCardList; //そのキャラが所持しているカード一覧





	//実装予定ステータス
	bool isBurn = false; //燃えているかどうか
	bool isPoison = false; //毒状態かどうか
	int hate = 0; //ヘイト


private:

	


};


