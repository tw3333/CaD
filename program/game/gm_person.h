#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_card.h"
#include <vector>
#include <string>
#include "gm_unit.h"



//クラスの名前をcharaからPersonへ(charaだとchar型の宣言と間違えやすいため)

class Person : public Unit{
public:
	
	Person(int hp, int hpmax, int cost, int costmax, int speed, bool pick, bool edit, int graph)
	 : HP(hp), HPMAX(hpmax), COST(cost),COSTMAX(costmax), SPEED(speed),PICK(pick),EDIT(edit), GRAPH(graph) {}

	//テストステータス
	int HP; //HP
	int HPMAX; //最大HP
	int COST; //コスト
	int COSTMAX; //最大コスト
	int SPEED; //ターン順位に使用する素早さ
	bool PICK = false;
	bool EDIT = false;



	int GRAPH = 0;

	bool isEnemy = false; //判別用

	
	std::vector<Card*> deck; //山札
	std::vector<Card*> hands; //手札
	std::vector<Card*> possCardList; //そのキャラが所持しているカード一覧





	//実装予定ステータス
	bool isBurn = false; //燃えているかどうか
	bool isPoison = false; //毒状態かどうか
	int hate = 0; //ヘイト


private:

	


};


