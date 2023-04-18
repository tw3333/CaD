#include "gm_button.h"


//範囲内（四角）でマウスクリックを行ったとき、trueを返す関数
// arg1,2...指定範囲、左上の頂点座標　arg3,4...指定範囲、右下の頂点座標
bool Button::IsBoundsLeftClicked(int x1, int y1, int x2, int y2) {

	if (x1 < mouse_point_x_ && mouse_point_x_ < x2 && y1 < mouse_point_y_ && mouse_point_y_ < y2) {

		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

			return true;

		}


	}


}