#pragma once
#include <string>

class Enemy {
public:
	Enemy(std::string name, int hp, int hpmax, int attack, int speed,int graph, int egraph) 
		:NAME(name), HP(hp), HPMAX(hpmax), ATTACK(attack), SPEED(speed) ,GRAPH(graph),EGRAPH(egraph) {}

private:

	//�X�e�[�^�X
	//�e�X�g
	std::string NAME; //���O

	int HP; //HP
	int HPMAX; //�ő�HP
	
	int ATTACK; //�U����
	
	int SPEED; //�^�[�����ʂɎg�p����f����

	//�����\��X�e�[�^�X
	bool burn; //�R���Ă��邩�ǂ���
	bool poison; //�ŏ�Ԃ��ǂ���

	int GRAPH; //�G�̉摜
	int EGRAPH; //�G�̍U���G�t�F�N�g


};
