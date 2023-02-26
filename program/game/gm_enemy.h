#pragma once
#include <string>
#include "gm_unit.h"
#include "gm_person.h"

//TODO:�J�v�Z����

class Enemy : public Unit {
public:
	
	Enemy(std::string name, int hp, int hpmax, int attack, int speed,int graph, int egraph) 
		:NAME(name), HP(hp), HPMAX(hpmax), ATTACK(attack), SPEED(speed) ,GRAPH(graph),EGRAPH(egraph) {}

	//�X�e�[�^�X
	//�e�X�g(���J���)
	std::string NAME; //���O

	int HP; //HP
	int HPMAX; //�ő�HP
	int ATTACK; //�U����
	int SPEED; //�^�[�����ʂɎg�p����f����
	int GRAPH; //�G�̉摜
	int EGRAPH; //�G�̍U���G�t�F�N�g

	int HEAL = 10;

	int DROPEXP = 100; //�l���o���l

	bool isEnemy = true; //���ʗp
	bool isActed = false; //�s���ς݂��ǂ���
	bool isDead = false; //����ł邩�ǂ���

	//�����\��X�e�[�^�X
	bool burn = false; //�R���Ă��邩�ǂ���
	bool poison = false; //�ŏ�Ԃ��ǂ���

	//�s���p�^�[���@0: �U���̂݁@1:�U���Ɖ񕜁@2:��Ԉُ펝���@3:�񕜂̂�
	int behavior = 0;



	//Enemy�s���p�֐�
	void EnemyAct(Enemy* enemy, std::vector<Person*>& party);
	void Attack(Enemy* enemy, std::vector<Person*>& party);
	void Heal(Enemy* enemy);

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

	////�X�e�[�^�X
	////�e�X�g
	//std::string NAME; //���O

	//int HP; //HP
	//int HPMAX; //�ő�HP
	//
	//int ATTACK; //�U����
	//
	//int SPEED; //�^�[�����ʂɎg�p����f����

	////�����\��X�e�[�^�X
	//bool burn; //�R���Ă��邩�ǂ���
	//bool poison; //�ŏ�Ԃ��ǂ���

	//int GRAPH; //�G�̉摜
	//int EGRAPH; //�G�̍U���G�t�F�N�g


};
