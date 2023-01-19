#pragma once

class Card {
public:
	
	Card() {

	}

	~Card() {}
	
	//カード情報
	int c_nunber = 0; //カードのNo
	char Name[20] = "NULL"; //カードの名前

	int c_cost = 0; //カードの使用コスト
	
	int c_damage = 0; //ダメージ
	int c_protec = 0; //防御
	int c_weak = 0; //脆弱
	int c_slow = 0; //鈍足
	int c_heal = 0; //HPを回復
	int c_hate = 0; //ヘイト

	int c_addcost = 0; //コストを加える
	
	bool cure = false; //状態異常を直す
	bool insteadDamage = false; //代わりにダメージを受けるかどうか
	bool skipTarn = false; //使用したとき即座にターンをスキップするかどうか
	bool addCard = false; //カードを加えるかどうか
	bool selectEffect = false; //効果が複数あり、そのどっちかを選択するかどうか

	
	bool tapCard = false; //使用されたかどうか
	int cardGraphic = 0; //カードのグラフィックハンドル

private:
	
};
