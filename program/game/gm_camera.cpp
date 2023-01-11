#include "gm_camera.h"

void GmCamera::update() 
{
	if (CTRL_TYPE_FREE_LOOK == ctrl_type_) {
		tnl::Quaternion xq = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, free_look_angle_xy_.x);
		tnl::Quaternion yq = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, free_look_angle_xy_.y);
		tnl::Quaternion wq = xq * yq;
		pos_ = target_ + tnl::Vector3::TransformCoord({ 0, 0, -target_distance_ }, wq);
	} 
	else if (CTRL_TYPE_QTN) {
		target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
	}

	/*pos_ = target_ + tnl::Vector3::TransformCoord({ 0, 0, -target_distance_ }, wq);*/
	dxe::Camera::update();
}
