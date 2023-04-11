#pragma once
#include "gm_unit.h"

//１マスを表すクラス


class Square {
public:

	Square(int row, int col){
		row_ = row; 
		col_ = col;
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
	VECTOR getXZBeginScreenPos() { return xz_begin_screen_pos_; }
	VECTOR getXZEndScreenPos() { return xz_end_screen_pos_; }

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

	//float pos_x_ = (b_w1 * row_) + (b_w1 / 2);



	float s_x_begin_ = -(b_w / 2) + (b_w1*row_); 
	float s_x_end_ = s_x_begin_ + (b_w1);
	float s_z_begin_ = (b_h / 2) - (b_h1*col_);
	float s_z_end_ = s_z_begin_ - (b_h1);


	////float型の{x,y,z}を格納
	////boardの大きさから、各Squareのwidth,heightの始点と終点を計算
	//VECTOR x_begin_ = { (float)s_x_begin_, 0.0f, 0.0f };
	//VECTOR x_end_ = { (float)s_x_end_, 0.0f, 0.0f };
	//VECTOR z_begin_ = VGet(0.0f, 0.0f, (float)s_z_begin_);
	//VECTOR z_end_ = VGet(0.0f, 0.0f, (float)s_z_end_);

	VECTOR xz_begin_ = {s_x_begin_, 0.0f, s_z_begin_ };
	VECTOR xz_end_ ={ s_x_end_, 0.0f, s_z_end_ };

	VECTOR xz_begin_screen_pos_ = ConvWorldPosToScreenPos(xz_begin_);
	VECTOR xz_end_screen_pos_ = ConvWorldPosToScreenPos(xz_end_);


    //構造体でまとめたかった案
	//struct Square_W {
	//	VECTOR begin = VGet((float)(-b_w1 * 4) + (b_w1*row_), 0, 0);
	//	VECTOR end = { 0,0,0 };
	//};
	//struct Square_H {
	//	VECTOR begin = { 0,0,0 };
	//	VECTOR end = { 0,0,0 };
	//};

};
