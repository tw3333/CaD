#pragma once
#include "gm_square.h"

//盤面を表すクラス



class Board {
public:

	Board() {

		for (int i = 0; i < 10; ++i) {
			for (int k = 0; k < 10; ++k) {

				squares_[i][k] =new Square(i,k);

			}
		}
	
	}

	~Board() {

		for (auto sqr : squares_) { delete sqr; }

	};

	Square* squares_[10][10];

	//メンバ関数群
	void setSquare(int row, int col, Unit* unit);
	
	void MakeObjBoard();

	//getter,setter
	dxe::Mesh* obj_board_ = nullptr;


private:

	static const int kboard_size_ = 10;

	
	//std::shared_ptr<dxe::Mesh> obj_board2_;
	std::vector<dxe::Mesh*> obj_units_;


	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;

	int board_w_ = w1 * 8;
	int board_h_ = h1 * 8;



};


