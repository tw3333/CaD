#pragma once
#include "gm_ui.h"
#include "../library/tnl_input.h"

class Button : public UI {
public:

	//void update();
	
	void UpdateMousePoint(int x, int y) { mouse_point_x_ = x; mouse_point_y_ = y; }
	bool IsBoundsLeftClicked(int x1, int y1, int x2, int y2);

private:

	int mouse_point_x_ = 0;
	int mouse_point_y_ = 0;



};
