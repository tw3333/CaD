#pragma once
#include "gm_card.h"
#include <vector>
#include <list>
#include "gm_person_manager.h"

class Card;
class PersonManager;

//�V���O���g���݌v
class CardManager {
public:

	static CardManager* GetInstance() {
		if (!instance_) {
			instance_ = new CardManager();
		}
		return instance_;
	}

	//CardManager�֐��Q
	void LoadCardDate(); //�����J�[�h�̃f�[�^��ǂݍ���
	void LoadCardGraph(); //�����J�[�h�̉摜��ǂݍ���
	void SortJobCard(); //�f�[�^����W���u���Ƃ̃J�[�h�Ƀ\�[�g����֐�
	
	//TODO��
	void LoatCardALL(); //��L�̊֐����܂Ƃ߂Ă��悤�̊֐��H


	std::vector<Card*> cardData; //��������Ă��邷�ׂẴJ�[�h�̃f�[�^

	//�e�L�������ƂɎ����Ă���J�[�h�ꗗ
	std::vector<Card*> cardDataChara1;
	std::vector<Card*> cardDataChara2; //�������L����
	std::vector<Card*> cardDataChara3;
	std::vector<Card*> cardDataChara4;

	//�L�������Ƃ̃f�b�L
	std::vector<Card*> chara1Deck;
	std::vector<Card*> chara2Deck; //�������L����
	std::vector<Card*> chara3Deck;
	std::vector<Card*> chara4Deck;

	//PersonManager
	PersonManager* pmgr = PersonManager::GetInstance();
	
	
private:

	static CardManager* instance_;

	//�R���X�g���N�^
	CardManager() {};
	

};

//memo
//�V���ȃJ�[�h��ǉ��������Ƃ�������͂����ǂݍ���ł����Čォ��z��ɓ����΂���
//TODO:�����J�[�h���O���܂łƂ����\�����ǂ�����΂������B�ォ����肵���J�[�h�͈ꖇ�ŁA
//����炪���肳��邽�тɁA�ǉ����Ă����Ƃ����̂��ǂ�����΂�����
//�����͂܂����񂪂��Ȃ��Ă������H���z��ɓ���邳���Ɏ蓮�œ���遨���Ⴀ�ォ������Ă�����́H


