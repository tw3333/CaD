#pragma once
#include "../dxlib_ext/dxlib_ext_camera.h"

class GmCamera : public dxe::Camera {
public :
	GmCamera() : dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {}
	~GmCamera(){}
	
	enum {
		CTRL_TYPE_FREE_LOOK
		, CTRL_TYPE_QTN
	};

	int ctrl_type_ = CTRL_TYPE_QTN;

	tnl::Quaternion rot_;

	tnl::Vector3 free_look_angle_xy_ = { tnl::ToRadian(30), 0, 0 };
	float target_distance_ = 50;

	void update();
};

