#include "gm_board.h"

void Board::setSquare(int row, int col,Unit* unit) {
	
	squares_[row][col]->setUnit(unit);


}


void Board::MakeObjBoard() {

	obj_board_ = dxe::Mesh::CreatePlaneMV({ (float)w1 * 8,(float)h1 * 8,0 });
	//obj_board_->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	obj_board_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	obj_board_->pos_ = { 0,0,0 };

}






