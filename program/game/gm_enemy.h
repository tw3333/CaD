#pragma once

class Enemy {
public:
	Enemy(int hp, int hpmax, int attack, int speed) : HP(hp), HPMAX(hpmax), ATTACK(attack), SPEED(speed) {}

private:

	//�X�e�[�^�X
	//�e�X�g
	int HP; //HP
	int HPMAX; //�ő�HP
	
	int ATTACK; //�U����
	
	int SPEED; //�^�[�����ʂɎg�p����f����

	//�����\��X�e�[�^�X
	bool burn; //�R���Ă��邩�ǂ���
	bool poison; //�ŏ�Ԃ��ǂ���

	int enemyGraph;


};
