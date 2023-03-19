#pragma once
#include "gm_square.h"

//�Ֆʂ�\���N���X

class Square;

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

	//�����o�֐��Q
	void setSquare(int row, int col, Unit* unit);



	//getter,setter




private:

	static const int kboard_size_ = 10;

	



};


