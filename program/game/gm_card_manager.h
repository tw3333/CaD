#pragma once
#include "gm_card.h"

class Card;

//�V���O���g���݌v
class CardManager {
public:





	static CardManager* getInstance() {
		if (!instance_) {
			instance_ = new CardManager;
		}
		return instance_;
	}

private:

	static CardManager* instance_;

	//�R���X�g���N�^
	CardManager() {

	}

};