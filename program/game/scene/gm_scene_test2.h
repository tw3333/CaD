#pragma once
#include "gm_scene_base.h"
#include "../gm_manager.h"
#include "../gm_camera.h"

#include "../gm_person_manager.h"

#include "../gm_board.h"
#include <memory>


class Test2 : public SceneBase {
public:

	Test2() {}
	~Test2();

	GmCamera* camera_ = nullptr;
	tnl::Quaternion fox_rot_;
	//std::unique_ptr<dxe::Mesh> img_board_ = nullptr;
	dxe::Mesh* player_ = nullptr;
	dxe::Mesh* square_ = nullptr;
	//dxe::Mesh* obj_board_ = nullptr;
	
	//クラスのインスタンス
	Board* board_ = new Board();
	PersonManager* pmgr_ = PersonManager::GetInstance();

	//メンバ関数群
	void DrawBoard();
	void RenderUnit();
	void GetSquareInfoGUIByClick();
	

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	
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

	

	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;

	int mouse_point_x_ = 0;
	int mouse_point_y_ = 0;

	int c1_face = 0;

	//カラーコード
	int black = GetColor(0,0,0);
	int red = GetColor(255,0,0);
	int silver = GetColor(192,192,192);
	int darkolivegreen = GetColor(85,107,47);

};