#include "gm_board.h"

void Board::setSquare(int row, int col,Unit* unit) {
	
	squares_[row][col]->setUnit(unit);


}

void Board::MakeSquaresInstance() {

	for (int i = 0; i < 10; ++i) {
		for (int k = 0; k < 10; ++k) {

			squares_[i][k] =new Square(i,k);

		}
	}

}


void Board::MakeObjBoard() {

	obj_board_ = dxe::Mesh::CreatePlane({ (float)board_w_,(float)board_h_,0 });
	obj_board_->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	obj_board_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	obj_board_->pos_ = { 0,0,0 };

}






