#include "gm_square.h"

void Square::MakeObjUnit() {

	//this->obj_unit_ = dxe::Mesh::CreatePlaneMV({ (float)74, (float)74, 0 });
	this->obj_unit_ = dxe::Mesh::CreatePlaneMV({ (float)b_w * 1, (float)b_h * 1, 0 });
	obj_unit_->setTexture(dxe::Texture::CreateFromFile("graphics/unit/ally/c1_board_img.png"));
	//player_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(50));
	this->obj_unit_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));

	int s_x = -640;
	int s_z = 360;

	float x = -640 + 64 + (128 * row_);
	float z = 360 - 36 + (-72 * col_);

	this->obj_unit_->pos_ = { x,1,z };


}

