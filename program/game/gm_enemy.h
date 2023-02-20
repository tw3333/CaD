#pragma once
#include <string>
#include "gm_unit.h"

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
	bool isEnemy = true; //���ʗp
	bool isActed = false; //�s���ς݂��ǂ���
	bool isDead = false; //����ł邩�ǂ���

	//�����\��X�e�[�^�X
	bool burn = false; //�R���Ă��邩�ǂ���
	bool poison = false; //�ŏ�Ԃ��ǂ���


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
