#include "gm_button.h"


//�͈͓��i�l�p�j�Ń}�E�X�N���b�N���s�����Ƃ��Atrue��Ԃ��֐�
// arg1,2...�w��͈́A����̒��_���W�@arg3,4...�w��͈́A�E���̒��_���W
bool Button::IsBoundsLeftClicked(int x1, int y1, int x2, int y2) {

	if (x1 < mouse_point_x_ && mouse_point_x_ < x2 && y1 < mouse_point_y_ && mouse_point_y_ < y2) {

		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {

			return true;

		}


	}


}