#include "gm_enemy.h"

#include <vector>


//�G�̍s���̌���A�����͂��̊֐����s���ɍs����
void Enemy::EnemyAct(Enemy* enemy,std::vector<Person*> &party) {

	if (enemy == nullptr) { return; }

	//Enemy��behavior�ɉ����čs���p�^�[����ω�������
	if (enemy->behavior == 0) { //�U���̂�

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

//���ׂĂ�Person��hate�̍��v���v�Z���Arand()�֐��ŗ����𐶐����āA�ePerson��hate�����v��������Ă����A0�ȉ��ɂȂ������_�ōU������Ώۂ�����
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