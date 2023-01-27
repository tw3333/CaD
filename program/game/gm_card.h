#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Card {
public:
	

	//カード情報
	int c_nunber = 0; //カードのNo
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
	bool Effect = false;

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

private:
	
};

//memo
//複数効果などは、そのカードが持っているIDで効果判定を決定する。
//単純にカードIDを渡して効果を発動するようにするか？
//効果の動作が複雑な場合のみ、IDを渡して別関数処理
//その他はIDとそれに追随する数値の足し引きでカードを表現する？
