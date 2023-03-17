#pragma once
#include <string>
#include "gm_unit.h"


class Ally : public Unit {
public:

	Ally(){}
	~Ally();

	
	//gette,setter


private:
	
	//
	int id_ = 0;
	//std::string name_ = '\0';
	int face_graph_ = 0;
	 

	//ステータス
	int level_ = 0;
	int hp_ = 0;
	int hp_max_ = 0;
	int cost_ = 0;
	int cost_max_ = 0;
	int speed_ = 0;
	int hate_ = 0;
	int exp_ = 0;
	int need_exp_ = 0;
	int protec_ = 0;

	bool pick_ = false;
	bool edit_ = false;

	bool is_first_deal_ = false;
	bool is_acted_ = false;
	bool is_dead_ = false;
	
	int deal_hand_num_ = 5;

	int graph_ = 0;





};