#pragma once
#include "gm_unit.h"
#include "gm_board.h"

//１マスを表すクラス


class Square {
public:

	Square(int row, int col){
		this->row_ = row;
		this->col_ = col;
	}


	~Square(){}

	enum class SquareType {
		kEnpty,
		kAlly,
		kEnemy,
		kObstacle
	};


	dxe::Mesh* obj_unit_ = nullptr;


	//メンバ関数群
	void setUnit(Unit* unit) { unit_ = unit; }
	void SetSquarePos(int row, int col) { row_ = row; col_ = col; }
	void MakeObjUnit(std::string file_path);
	void SetUnitToSquare();


	//setter,getter
	SquareType getSquareType() { return square_type_; }
	void setSquareType(SquareType enumclasstype) { square_type_ = enumclasstype; }

private:

	SquareType square_type_ = SquareType::kEnpty;
	
	//int type_ = Square::kEnpty;

	Unit* unit_ = nullptr;

	//dxe::Mesh* obj_unit_ = nullptr;

	int row_ = 0;
	int col_ = 0;

	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;
	int b_w = w1 * 8 / 10;
	int b_h = h1 * 8 / 10;


	struct Square_W {
		int start = 0;
		int end = 0;
	};

	struct Square_H {
		int start = 0;
		int end = 0;
	};



	
};
