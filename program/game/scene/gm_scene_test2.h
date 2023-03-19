#pragma once
#include "gm_scene_base.h"
#include "../gm_manager.h"
#include "../gm_camera.h"

#include "../gm_person_manager.h"

#include "../gm_board.h"


class Test2 : public SceneBase {
public:

	Test2() {}
	~Test2();


	GmCamera* camera_ = nullptr;
	
	dxe::Mesh* img_board_ = nullptr;
	dxe::Mesh* player_ = nullptr;
	dxe::Mesh* square_ = nullptr;



	tnl::Quaternion fox_rot_;
	
	Board* board_ = new Board();


	//メンバ関数群
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	PersonManager* pmgr_ = PersonManager::GetInstance();



	//debug
	bool ui = true;

	//UI関数
	void PersonBox();

private:

	int kboard_size_ = 10;
	const int knum_cells_ = kboard_size_ * kboard_size_;

	enum CellType {
	
		Empty,
		Person,
		Enemy,
		EFFRCT,

	};

	struct Cell {
		CellType type;
		int effect;
	};

	Cell board_[10][10];

	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;

	int c1_face;

	//カラーコード
	int black = GetColor(0,0,0);
	int red = GetColor(255,0,0);
	int silver = GetColor(192,192,192);
	int darkolivegreen = GetColor(85,107,47);


};