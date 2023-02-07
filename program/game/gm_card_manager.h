#pragma once
#include "gm_card.h"
#include <vector>
#include <list>

class Card;

//シングルトン設計
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


	std::vector<Card*> cardDate; //実装されているすべてのカードのデータ

	//各キャラごとに持っているカード一覧
	std::vector<Card*> cardListChara1;
	std::vector<Card*> cardListChara2;
	std::vector<Card*> cardListChara3;
	std::vector<Card*> cardListChara4;


	
private:

	static CardManager* instance_;

	//コンストラクタ
	CardManager() {};
	~CardManager();

};

//memo
//新たなカードを追加したいとき→それはもう読み込んでおいて後から配列に入れればいい
//TODO:同じカードが三枚までという表現をどうすればいいか。後から入手したカードは一枚で、
//それらが入手されるたびに、追加していくというのもどうすればいいか
//そこはまずかんがえなくていいか？→配列に入れるさいに手動で入れる→じゃあ後から入ってきたやつは？


