#include "gm_ally_manager.h"

AllyManager* AllyManager::instance_ = nullptr;

void AllyManager::MakeAllies() {

	allies_.emplace_back(new Ally(1,3));
	allies_.emplace_back(new Ally(2,3));
	allies_.emplace_back(new Ally(3,3));
	allies_.emplace_back(new Ally(4,3));

}

void AllyManager::LoadAlliesGraph() {

	allies_[0]->battle_img_ = ("graphics/unit/ally/c1_board_img.png");
	allies_[0]->face2_img_ = ("graphics/unit/ally/c1_face2_img.png");

	allies_[0]->face_img_path_ = ("graphics/unit/ally/c1_face_img.png");
	allies_[0]->face2_img_path_ = ("graphics/unit/ally/c1_face2_img.png");
	allies_[0]->board_img_path_ = ("graphics/unit/ally/c1_board_img.png");
	allies_[0]->face_img_handle_ = LoadGraph(allies_[0]->face_img_path_.c_str());
	allies_[0]->face2_img_handle_ = LoadGraph(allies_[0]->face2_img_path_.c_str());

	allies_[1]->face_img_path_ = ("graphics/unit/ally/c2_face_img.png");
	allies_[1]->face2_img_path_ = ("graphics/unit/ally/c2_face2_img.png");
	allies_[1]->board_img_path_ = ("graphics/unit/ally/c2_board_img.png");
	allies_[1]->face_img_handle_ = LoadGraph(allies_[1]->face_img_path_.c_str());
	allies_[1]->face2_img_handle_ = LoadGraph(allies_[1]->face2_img_path_.c_str());

	allies_[2]->face_img_path_ = ("graphics/unit/ally/c3_face_img.png");
	allies_[2]->face2_img_path_ = ("graphics/unit/ally/c3_face2_img.png");
	allies_[2]->board_img_path_ = ("graphics/unit/ally/c3_board_img.png");
	allies_[2]->face_img_handle_ = LoadGraph(allies_[2]->face_img_path_.c_str());
	allies_[2]->face2_img_handle_ = LoadGraph(allies_[2]->face2_img_path_.c_str());

	allies_[3]->face_img_path_ = ("graphics/unit/ally/c4_face_img.png");
	allies_[3]->face2_img_path_ = ("graphics/unit/ally/c4_face2_img.png");
	allies_[3]->board_img_path_ = ("graphics/unit/ally/c4_board_img.png");
	allies_[3]->face_img_handle_ = LoadGraph(allies_[3]->face_img_path_.c_str());
	allies_[3]->face2_img_handle_ = LoadGraph(allies_[3]->face2_img_path_.c_str());




}
