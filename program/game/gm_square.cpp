#include "gm_square.h"

void Square::MakeObjUnit(std::string file_path) {

	//this->obj_unit_ = dxe::Mesh::CreatePlaneMV({ (float)74, (float)74, 0 });
	obj_unit_ = dxe::Mesh::CreatePlaneMV({ (float)64, (float)b_h * 1, 0 });
	obj_unit_->setTexture(dxe::Texture::CreateFromFile(file_path.c_str()));

	//obj_unit_->setTexture(LoadGraph("graphics/red1.bmp"));

	//player_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(50));
	obj_unit_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(20));

	float s_x = -640;
	float s_z = 360;

	float x = -640 + 64 + (128 * row_);
	float z = 360 - 36 + (-72 * col_);

	this->obj_unit_->pos_ = { x,32,z };


}

