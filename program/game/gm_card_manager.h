#pragma once
#include "gm_card.h"
#include <vector>

class Card;

//シングルトン設計
class CardManager {
public:

	//std::vector<Card> CardDate;

	std::vector<Card> CardDate = Card::ReadCardsFromCSV("date/card.csv");
	
	static CardManager* getInstance() {
		if (!instance_) {
			instance_ = new CardManager;
		}
		return instance_;
	}

	void LoadCardDate(Card CD[]);
	

private:

	static CardManager* instance_;

	//コンストラクタ
	CardManager() {

	}

};

//memo
//新たなカードを追加したいとき→それはもう読み込んでおいて後から配列に入れればいい
//TODO:同じカードが三枚までという表現をどうすればいいか。後から入手したカードは一枚で、
//それらが入手されるたびに、追加していくというのもどうすればいいか
//そこはまずかんがえなくていいか？→配列に入れるさいに手動で入れる→じゃあ後から入ってきたやつは？


