#pragma once
#include <string>
#include "gm_unit.h"


class Ally : public Unit {
public:

	Ally(){}
	~Ally(){};

	
	//gette,setter
	int getSquareID() { return ksquare_id_; }
	


private:
	
	const int ksquare_id_ = 1;
	
	int ally_id_ = 0;
	std::string name_;

	//ステータス
	//確定ステータス
	int level_ = 0;
	int hp_ = 0;
	int hp_max_ = 0;
	int cost_ = 0;
	int cost_max_ = 0;
	int speed_ = 0;

	//（採用）不確定ステータス
	int hate_ = 0;
	int exp_ = 0;
	int need_exp_ = 0;
	int protec_ = 0;

	//状態フラグ
	bool pick_ = false;
	bool edit_ = false;
	bool is_first_deal_ = false;
	bool is_acted_ = false;
	bool is_dead_ = false;
	
	int deal_hand_num_ = 5;

	//画像ハンドル
	int face_img_ = 0;
	int face2_img_ = 0;
	int battle_img_ = 0;
	int stand_img_ = 0;



};