#pragma once

class Card {
public:
	
	Card() {

	}

	~Card() {}
	
	//�J�[�h���
	int c_nunber = 0; //�J�[�h��No
	char Name[20] = "NULL"; //�J�[�h�̖��O

	int c_cost = 0; //�J�[�h�̎g�p�R�X�g
	
	int c_damage = 0; //�_���[�W
	int c_protec = 0; //�h��
	int c_weak = 0; //�Ǝ�
	int c_slow = 0; //�ݑ�
	int c_heal = 0; //HP����
	int c_hate = 0; //�w�C�g

	int c_addcost = 0; //�R�X�g��������
	
	bool cure = false; //��Ԉُ�𒼂�
	bool insteadDamage = false; //����Ƀ_���[�W���󂯂邩�ǂ���
	bool skipTarn = false; //�g�p�����Ƃ������Ƀ^�[�����X�L�b�v���邩�ǂ���
	bool addCard = false; //�J�[�h�������邩�ǂ���
	bool selectEffect = false; //���ʂ���������A���̂ǂ�������I�����邩�ǂ���

	
	bool tapCard = false; //�g�p���ꂽ���ǂ���
	int cardGraphic = 0; //�J�[�h�̃O���t�B�b�N�n���h��

private:
	
};
