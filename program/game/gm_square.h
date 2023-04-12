#pragma once
#include "gm_unit.h"


//１マスを表すクラス


class Square {
public:

	Square(int row, int col){
		row_ = row; 
		col_ = col;

		x_begin_ = -(b_w / 2) + (b_w1 * row_);
		x_end_ = x_begin_ + (b_w1 * 1);
		z_begin_ = (b_h / 2) - (b_h1 * col_);
		z_end_ = z_begin_ - (b_w1 * 1);

		xz_begin_pos_ = { (float)x_begin_,0.0f,(float)z_begin_ };
		xz_end_pos_ = { (float)x_end_,0.0f,(float)z_end_ };

	}


	~Square(){}

	enum class SquareType {
		kEnpty,
		kAlly,
		kEnemy,
		kObstacle
	};


	dxe::Mesh* obj_unit_ = nullptr;
	dxe::Mesh* obj_square_ = nullptr;


	//メンバ関数群
	void setUnit(Unit* unit) { unit_ = unit; }
	void SetSquarePos(int row, int col) { row_ = row; col_ = col; }
	void MakeObjUnit(std::string file_path);
	void MakeObjSquare();
	void SetUnitToSquare();



	//setter,getter
	int getSquareRow() { return row_; }
	int getSquareCol() { return col_; }
	SquareType getSquareType() { return square_type_; }
	void setSquareType(SquareType enumclasstype) { square_type_ = enumclasstype; }
	tnl::Vector3 getXZBeginPos() { return xz_begin_pos_; }
	tnl::Vector3 getXZEndPos() { return xz_end_pos_; }

	const int pos_x_ = -(640) + (160);

private:

	SquareType square_type_ = SquareType::kEnpty;
	
	//int type_ = Square::kEnpty;

	Unit* unit_ = nullptr;

	//dxe::Mesh* obj_unit_ = nullptr;

	int row_ = 0;
	int col_ = 0;

	
	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;
	int b_w = w1 * 8;
	int b_h = h1 * 8;
	int b_w1 = b_w / 10;
	int b_h1 = b_h / 10;


	int x_begin_ = -(b_w / 2) + (b_w1 * row_);
	int x_end_ = x_begin_ + (b_w1*1);
	int z_begin_ = (b_h / 2) - (b_h1 * col_);
	int z_end_ = z_begin_ - (b_w1*1);

	tnl::Vector3 xz_begin_pos_ = {(float)x_begin_,0.0f,(float)z_begin_};
	tnl::Vector3 xz_end_pos_ = {(float)x_end_,0.0f,(float)z_end_};



	//float s_x_begin_ = -(b_w / 2) + (b_w1*row_); 
	//float s_x_end_ = s_x_begin_ + (b_w1);
	//float s_z_begin_ = (b_h / 2) - (b_h1*col_);
	//float s_z_end_ = s_z_begin_ - (b_h1);
	


};
