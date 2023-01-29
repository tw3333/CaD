#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Card {
public:


	//カード情報
	int c_number = 0; //カードのNo
	char cardJob[10] = "NULL";
	char Name[20] = "NULL"; //カードの名前


	int c_cost = 0; //カードの使用コスト

	int c_damage = 0; //ダメージ
	int c_protec = 0; //防御
	int c_weak = 0; //脆弱
	int c_slow = 0; //鈍足
	int c_heal = 0; //HPを回復
	int c_hate = 0; //ヘイト

	int c_addcost = 0; //コストを加える
	bool c_effect = false;

	int cardGraph = 0; //カードのグラフィックハンドル

	//bool cure = false; //状態異常を直す
	//bool insteadDamage = false; //代わりにダメージを受けるかどうか
	//bool skipTarn = false; //使用したとき即座にターンをスキップするかどうか
	//bool addCard = false; //カードを加えるかどうか
	//bool selectEffect = false; //効果が複数あり、そのどっちかを選択するかどうか
	//bool overallEffect = false; //全体効果かどうか
	//bool tapCard = false; //使用されたかどうか

	//関数群
	void SetCardGraph(int i);
	static std::vector<Card> ReadCardsFromCSV(const char* filename);
	

	//セッター
	void SetCardNumber(int temp) { c_number = temp; }
	void SetCardCost(int temp) { c_cost = temp; }
	void SetCardDamage(int temp) { c_damage = temp; }
	void SetCardProtec(int temp) { c_protec = temp; }
	void SetCardWeak(int temp) { c_weak = temp; }
	void SetCardSlow(int temp) { c_slow = temp; }
	void SetCardHate(int temp) { c_hate = temp; }

	void SetCardAddCost(int temp) { c_addcost = temp; }
	void SetCardEffect(bool temp) { c_effect = temp; }



	//ゲッター
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
//複数効果などは、そのカードが持っているIDで効果判定を決定する。
//単純にカードIDを渡して効果を発動するようにするか？
//効果の動作が複雑な場合のみ、IDを渡して別関数処理
//その他はIDとそれに追随する数値の足し引きでカードを表現する？
