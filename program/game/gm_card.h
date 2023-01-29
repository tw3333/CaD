#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Card {
public:


	//�J�[�h���
	int c_number = 0; //�J�[�h��No
	char cardJob[10] = "NULL";
	char Name[20] = "NULL"; //�J�[�h�̖��O


	int c_cost = 0; //�J�[�h�̎g�p�R�X�g

	int c_damage = 0; //�_���[�W
	int c_protec = 0; //�h��
	int c_weak = 0; //�Ǝ�
	int c_slow = 0; //�ݑ�
	int c_heal = 0; //HP����
	int c_hate = 0; //�w�C�g

	int c_addcost = 0; //�R�X�g��������
	bool c_effect = false;

	int cardGraph = 0; //�J�[�h�̃O���t�B�b�N�n���h��

	//bool cure = false; //��Ԉُ�𒼂�
	//bool insteadDamage = false; //����Ƀ_���[�W���󂯂邩�ǂ���
	//bool skipTarn = false; //�g�p�����Ƃ������Ƀ^�[�����X�L�b�v���邩�ǂ���
	//bool addCard = false; //�J�[�h�������邩�ǂ���
	//bool selectEffect = false; //���ʂ���������A���̂ǂ�������I�����邩�ǂ���
	//bool overallEffect = false; //�S�̌��ʂ��ǂ���
	//bool tapCard = false; //�g�p���ꂽ���ǂ���

	//�֐��Q
	void SetCardGraph(int i);
	static std::vector<Card> ReadCardsFromCSV(const char* filename);
	

	//�Z�b�^�[
	void SetCardNumber(int temp) { c_number = temp; }
	void SetCardCost(int temp) { c_cost = temp; }
	void SetCardDamage(int temp) { c_damage = temp; }
	void SetCardProtec(int temp) { c_protec = temp; }
	void SetCardWeak(int temp) { c_weak = temp; }
	void SetCardSlow(int temp) { c_slow = temp; }
	void SetCardHate(int temp) { c_hate = temp; }

	void SetCardAddCost(int temp) { c_addcost = temp; }
	void SetCardEffect(bool temp) { c_effect = temp; }



	//�Q�b�^�[
	int GetCardNumber() { return c_number; }
	int GetCardCost() { return c_cost; }
	int GetCardDamage() { return c_damage; }
	int GetCardProtec() { return c_protec; }
	int GetCardWeak() { return c_weak; }
	int GetCardSlow() { return c_slow; }
	int GetCardHate() { return c_hate; }

	int GetCardAddCost() { return c_addcost; }
	bool GetCardEffect() { return c_effect; }


private:

};

//memo
//�������ʂȂǂ́A���̃J�[�h�������Ă���ID�Ō��ʔ�������肷��B
//�P���ɃJ�[�hID��n���Č��ʂ𔭓�����悤�ɂ��邩�H
//���ʂ̓��삪���G�ȏꍇ�̂݁AID��n���ĕʊ֐�����
//���̑���ID�Ƃ���ɒǐ����鐔�l�̑��������ŃJ�[�h��\������H
