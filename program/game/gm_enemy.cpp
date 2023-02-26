#include "gm_enemy.h"

#include <vector>


//敵の行動の決定、処理はこの関数実行時に行われる
void Enemy::EnemyAct(Enemy* enemy,std::vector<Person*> &party) {

	if (enemy == nullptr) { return; }

	//Enemyのbehaviorに応じて行動パターンを変化させる
	if (enemy->behavior == 0) { //攻撃のみ

		Attack(enemy, party);


	}
	else if (enemy->behavior == 1) {




	}




}








void Enemy::Attack(Enemy* enemy, std::vector<Person*> &party) {

	int totalHate = 0;

	for (int i = 0; i < party.size(); i++) {

		totalHate += party[i]->HATE;

	}

	int r = rand() % totalHate;

	for (int i = 0; i < party.size(); i++) {

		r -= party[i]->HATE;
		if (r < 0) {

			party[i]->HP -= enemy->ATTACK;
			break;

		}

	}


}

void Enemy::Heal(Enemy* enemy) {

	if (enemy == nullptr) { return; }

	if (enemy->isDead == false) {

		enemy->HP += enemy->HEAL;

		if (enemy->HP > enemy->HPMAX) {

			enemy->HP = enemy->HPMAX;

		}

	}



}

//すべてのPersonのhateの合計を計算し、rand()関数で乱数を生成して、各Personのhateを合計から引いていき、0以下になった時点で攻撃する対象を決定
void CooseTarget(std::vector<Person*> &party) {

	int totalHate = 0;

	for (int i = 0; i < party.size(); i++) {

		totalHate += party[i]->HATE;

	}
	
	int r = rand() % totalHate;

	for (int i = 0; i < party.size(); i++) {

		r -= party[i]->HATE;

		if (r < 0) {

			//Attack();
			break;

		}

	}


}