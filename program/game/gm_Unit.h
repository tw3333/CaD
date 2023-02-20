#pragma once

//PersonとEnemyの基底クラス
//SceneBattleの速さ計算時にポインタの配列を結合するために作った
//TODO:継承した方がいいかどうか要検討


class Unit {
public:
	
	
	//PesonとEnemyの共通ステータス
	int SPEED;

	bool isEnemy = false; //敵かどうか
	bool isActed = false; //行動済みかどうか
	bool isDead = false; //死んでるかどうか



	virtual ~Unit(){};

};