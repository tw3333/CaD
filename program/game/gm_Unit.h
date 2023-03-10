#pragma once
#include <vector>
#include "gm_card.h"



//PersonとEnemyの基底クラス
//SceneBattleの速さ計算時にポインタの配列を結合するために作った
//TODO:継承した方がいいかどうか要検討

class Card;

class Unit {
public:
	
	virtual int getSPEED() const { return SPEED; }
	virtual void setSPEED(int SPEED) { SPEED = SPEED; }
	
	virtual bool getIsEnemy() const { return isEnemy; }
	virtual void setIsEnemy(bool f) { isEnemy = f; }

	virtual bool getIsActed() const { return isActed; }
	virtual void setIsActed(bool f) { isActed = f; }

	virtual bool getIsDead() const { return isEnemy; }
	virtual void setIsDead(bool f) { isDead = f; }

	virtual std::vector<Card*> getDeck() const { return deck; }
	virtual std::vector<Card*> getHand() const { return hand; }


	virtual ~Unit(){};

protected:
	
	//PesonとEnemyの共通ステータス
	int SPEED = 0;

	std::vector<Card*> deck; //山札
	std::vector<Card*> hand; //手札

	bool isEnemy = false; //敵かどうか
	bool isActed = false; //行動済みかどうか
	bool isDead = false; //死んでるかどうか


};