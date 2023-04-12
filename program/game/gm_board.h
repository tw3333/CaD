#pragma once
#include "gm_square.h"

//盤面を表すクラス


class Board {
public:

	Board(int screen_w, int screen_h) {

		board_w_ = (screen_w / 10) * 8;
		board_h_ = (screen_h / 10) * 8;
	
	}

	~Board() {

		for (auto sqr : squares_) { delete sqr; }

	};

	Square* squares_[10][10];

	//メンバ関数群
	void setSquare(int row, int col, Unit* unit);
	void MakeSquaresInstance();
	
	void MakeObjBoard();

	//getter,setter
	dxe::Mesh* obj_board_ = nullptr;
	int getBoardW() { return board_w_; }
	int getBoardH() { return board_h_; }


private:

	static const int kboard_size_ = 10;

	
	//std::shared_ptr<dxe::Mesh> obj_board2_;
	std::vector<dxe::Mesh*> obj_units_;


	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;

	//Object作成時の盤面のサイズw*h
	int board_w_ = 0;
	int board_h_ = 0;



};


