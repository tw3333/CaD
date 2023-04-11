#include "gm_square.h"

void Square::MakeObjUnit(std::string file_path) {

	//this->obj_unit_ = dxe::Mesh::CreatePlaneMV({ (float)74, (float)74, 0 });
	obj_unit_ = dxe::Mesh::CreatePlaneMV({ (float)64, (float)b_h1 ,0});
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

void Square::MakeObjSquare() {

	obj_square_ = dxe::Mesh::CreatePlaneMV({ (float)b_w1,(float)b_h1,0 });
	obj_square_->setTexture(dxe::Texture::CreateFromFile("graphics/blue2.bmp"));
	obj_square_->rot_q_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	float s_x = -(b_w / 2);
	float s_z = (b_h / 2);

	float x = s_x + (b_w1 / 2) + (b_w1 * row_);
	float z = s_z - (b_h1 / 2) + (-b_h1 * col_);

	obj_square_->pos_ = { x,1,z };


}

