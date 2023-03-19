#pragma once
#include "gm_unit.h"

//１マスを表すクラス


class Square {
public:

	Square(int row, int col){
		this->row_ = row;
		this->col_ = col;
	}


	~Square(){}

	enum SquareType {
		kEnpty,
		kAlly,
		kEnemy,
		kObstacle
	};


	//setter,getter
	int getSquareType() { return type_; }
	void setSquareType(int type_id) { type_ = SquareType::kEnpty; }

	void setUnit(Unit* unit) { unit_ = unit; }




private:

	
	int type_ = SquareType::kEnpty;

	Unit* unit_ = nullptr;


	int row_ = 0;
	int col_ = 0;


	





};
