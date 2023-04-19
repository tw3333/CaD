#pragma once
//#include "gm_ui.h"
#include "../library/tnl_input.h"

class Button {
public:

	//void update();
	Button() {}
	~Button() {}

	enum class Type {
		Dungeon,
		Chara,
		shop,
		storate
	};


	
	void UpdateMousePoint(int x, int y) { mouse_point_x_ = x; mouse_point_y_ = y; }
	bool IsBoundsLeftClicked(int x1, int y1, int x2, int y2);
	bool IsLeftClicked();

private:

	int mouse_point_x_;
	int mouse_point_y_;

	//ボタンを配置するpos,左上頂点座標からw,hの大きさに展開
	int pos_x_ = 0;
	int pos_y_ = 0;

	int size_w_ = 0;
	int size_h_ = 0;





};
