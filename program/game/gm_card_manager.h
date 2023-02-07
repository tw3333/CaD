#pragma once
#include "gm_card.h"
#include <vector>
#include <list>

class Card;

//�V���O���g���݌v
class CardManager {
public:

	static CardManager* getInstance() {
		if (!instance_) {
			instance_ = new CardManager();
		}
		return instance_;
	}

	void LoadCardDate();
	void LoadCardGraph();


	std::vector<Card*> cardDate; //��������Ă��邷�ׂẴJ�[�h�̃f�[�^

	
private:

	static CardManager* instance_;

	//�R���X�g���N�^
	CardManager() {};
	~CardManager();

};

//memo
//�V���ȃJ�[�h��ǉ��������Ƃ�������͂����ǂݍ���ł����Čォ��z��ɓ����΂���
//TODO:�����J�[�h���O���܂łƂ����\�����ǂ�����΂������B�ォ����肵���J�[�h�͈ꖇ�ŁA
//����炪���肳��邽�тɁA�ǉ����Ă����Ƃ����̂��ǂ�����΂�����
//�����͂܂����񂪂��Ȃ��Ă������H���z��ɓ���邳���Ɏ蓮�œ���遨���Ⴀ�ォ������Ă�����́H


