#pragma once
#include <string>
#include "gm_entity.h"

class Enemy : public Entity {
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



	//実装予定ステータス
	bool burn = false; //燃えているかどうか
	bool poison = false; //毒状態かどうか


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
