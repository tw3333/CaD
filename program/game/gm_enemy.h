#pragma once

class Enemy {
public:
	Enemy(int hp, int hpmax, int attack, int speed) : HP(hp), HPMAX(hpmax), ATTACK(attack), SPEED(speed) {}

private:

	//ステータス
	//テスト
	int HP; //HP
	int HPMAX; //最大HP
	
	int ATTACK; //攻撃力
	
	int SPEED; //ターン順位に使用する素早さ

	//実装予定ステータス
	bool burn; //燃えているかどうか
	bool poison; //毒状態かどうか

	int enemyGraph;


};
