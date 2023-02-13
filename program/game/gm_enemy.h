#pragma once
#include <string>

class Enemy {
public:
	Enemy(std::string name, int hp, int hpmax, int attack, int speed,int graph, int egraph) 
		:NAME(name), HP(hp), HPMAX(hpmax), ATTACK(attack), SPEED(speed) ,GRAPH(graph),EGRAPH(egraph) {}

private:

	//ステータス
	//テスト
	std::string NAME; //名前

	int HP; //HP
	int HPMAX; //最大HP
	
	int ATTACK; //攻撃力
	
	int SPEED; //ターン順位に使用する素早さ

	//実装予定ステータス
	bool burn; //燃えているかどうか
	bool poison; //毒状態かどうか

	int GRAPH; //敵の画像
	int EGRAPH; //敵の攻撃エフェクト


};
