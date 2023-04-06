#include "gm_ally_manager.h"

AllyManager* AllyManager::instance_ = nullptr;

void AllyManager::MakeAllies() {

	allies_.emplace_back(new Ally());
	allies_.emplace_back(new Ally());
	allies_.emplace_back(new Ally());
	allies_.emplace_back(new Ally());

}

void AllyManager::LoadAlliesGraph() {

	allies_[0]->battle_img_ = ("graphics/unit/ally/c1_board_img.png");
	allies_[0]->face2_img_ = ("graphics/unit/ally/c1_face2_img.png");

	//allies_[1]->battle_img_ = LoadGraph("graphics/unit/ally/c2_board_img.png");
	//allies_[1]->face2_img_ = LoadGraph("graphics/unit/ally/c2_face2_img.png");

	//allies_[2]->battle_img_ = LoadGraph("graphics/unit/ally/c3_board_img.png");
	//allies_[3]->face2_img_ = LoadGraph("graphics/unit/ally/c3_face2_img.png");

	//allies_[4]->battle_img_ = LoadGraph("graphics/unit/ally/c4_board_img.png");
	//allies_[4]->face2_img_ = LoadGraph("graphics/unit/ally/c4_face2_img.png");


}
