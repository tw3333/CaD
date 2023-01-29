#pragma once
#include "gm_card.h"

class Card;

//シングルトン設計
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

	//コンストラクタ
	CardManager() {

	}

};