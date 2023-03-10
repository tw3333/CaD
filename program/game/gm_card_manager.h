#pragma once
#include "gm_card.h"
#include <vector>
#include <list>
#include "gm_person_manager.h"

class Card;
class PersonManager;

//シングルトン設計
class CardManager {
public:

	static CardManager* GetInstance() {
		if (!instance_) {
			instance_ = new CardManager();
		}
		return instance_;
	}

	//CardManager関数群
	void LoadCardDate(); //実装カードのデータを読み込む
	void LoadCardGraph(); //実装カードの画像を読み込む
	void SortJobCard(); //データからジョブごとのカードにソートする関数
	
	//TODO↓
	void LoatCardALL(); //上記の関数をまとめてやるようの関数？


	std::vector<Card*> cardData; //実装されているすべてのカードのデータ

	//各キャラごとに持っているカード一覧
	std::vector<Card*> cardDataChara1;
	std::vector<Card*> cardDataChara2; //未実装キャラ
	std::vector<Card*> cardDataChara3;
	std::vector<Card*> cardDataChara4;

	//キャラごとのデッキ
	std::vector<Card*> chara1Deck;
	std::vector<Card*> chara2Deck; //未実装キャラ
	std::vector<Card*> chara3Deck;
	std::vector<Card*> chara4Deck;

	//PersonManager
	PersonManager* pmgr = PersonManager::GetInstance();
	
	
private:

	static CardManager* instance_;

	//コンストラクタ
	CardManager() {};
	

};

//memo
//新たなカードを追加したいとき→それはもう読み込んでおいて後から配列に入れればいい
//TODO:同じカードが三枚までという表現をどうすればいいか。後から入手したカードは一枚で、
//それらが入手されるたびに、追加していくというのもどうすればいいか
//そこはまずかんがえなくていいか？→配列に入れるさいに手動で入れる→じゃあ後から入ってきたやつは？


