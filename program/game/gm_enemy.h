#pragma once
#include <string>
#include "gm_unit.h"

//TODO:カプセル化

class Enemy : public Unit {
public:
	
	Enemy(std::string name, int hp, int hpmax, int attack, int speed,int graph, int egraph) 
		:NAME(name), HP(hp), HPMAX(hpmax), ATTACK(attack), SPEED(speed) ,GRAPH(graph),EGRAPH(egraph) {}

	//ステータス
	//テスト(公開状態)
	std::string NAME; //名前

	int HP; //HP
	int HPMAX; //最大HP
	int ATTACK; //攻撃力
	int SPEED; //ターン順位に使用する素早さ
	int GRAPH; //敵の画像
	int EGRAPH; //敵の攻撃エフェクト
	bool isEnemy = true; //判別用
	bool isActed = false; //行動済みかどうか
	bool isDead = false; //死んでるかどうか

	//実装予定ステータス
	bool burn = false; //燃えているかどうか
	bool poison = false; //毒状態かどうか
	

	//getter setter
	int getSPEED() const override { return SPEED; }
	void setSPEED(int speed) override { SPEED = speed; }

	bool getIsEnemy() const override { return isEnemy; }
	void setIsEnemy(bool f) override { isEnemy = f; }

	bool getIsActed() const override { return isActed; }
	void setIsActed(bool f) override { isActed = f; }

	bool getIsDead() const override { return isDead; }
	void setIsDead(bool f) override { isDead = f; }

private:

	////ステータス
	////テスト
	//std::string NAME; //名前

	//int HP; //HP
	//int HPMAX; //最大HP
	//
	//int ATTACK; //攻撃力
	//
	//int SPEED; //ターン順位に使用する素早さ

	////実装予定ステータス
	//bool burn; //燃えているかどうか
	//bool poison; //毒状態かどうか

	//int GRAPH; //敵の画像
	//int EGRAPH; //敵の攻撃エフェクト


};
