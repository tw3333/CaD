#pragma once
#include <string>
#include "gm_unit.h"


class Ally : public Unit {
public:

	Ally(int id,int cost){
		
		ally_id_ = id;
		cost_max_ = cost;

	
	}
	~Ally(){};

	
	//gette,setter
	int getAllyID() { return ally_id_; }

	int getSquareID() { return ksquare_id_; }
	void setAllyPos(int row, int col) { row_ = row; col_ = col; }

	int getRow() { return row_; }
	int getCol() { return col_; }
	void setIsPicked(bool is_picked) { is_picked_ = is_picked; }
	bool getIsPicked() { return is_picked_; }



	//�摜handle
	int face_img_handle_ = 0;
	int face2_img_handle_ = 0;
	int board_img_handle_ = 0;

	//�摜�t�@�C��path
	std::string face_img_path_;
	std::string face2_img_path_;
	std::string board_img_path_;

	std::string face2_img_;
	std::string battle_img_;
private:
	
	const int ksquare_id_ = 1;

	int row_ = 0;
	int col_ = 0;
	int pick_order_ = 0;


	int ally_id_ = 0;
	std::string name_;

	//�X�e�[�^�X
	//�m��X�e�[�^�X
	int level_ = 0;
	int hp_ = 0;
	int hp_max_ = 0;
	int cost_ = 0;
	int cost_max_ = 0;
	int speed_ = 0;

	//�i�̗p�j�s�m��X�e�[�^�X
	int hate_ = 0;
	int exp_ = 0;
	int need_exp_ = 0;
	int protec_ = 0;



	//��ԃt���O
	bool is_picked_ = false;
	bool edit_ = false;
	bool is_first_deal_ = false;
	bool is_acted_ = false;
	bool is_dead_ = false;
	
	int deal_hand_num_ = 5;

};