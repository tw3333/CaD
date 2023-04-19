#pragma once
#include "ui_component.h"

class Button : public UIComponent {
public:
	void Draw() = 0;

private:
	
	int size_x_ = 0;
	int size_h_ = 0;
	int pos_x_ = 0;
	int pos_y_ = 0;

};