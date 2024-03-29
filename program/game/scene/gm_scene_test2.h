#pragma once
#include "gm_scene_base.h"
#include "../gm_manager.h"
#include "../gm_camera.h"

#include "../gm_person_manager.h"
#include "../gm_ally_manager.h"

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
	dxe::Mesh* select_square_ = nullptr;
	//dxe::Mesh* obj_board_ = nullptr;
	dxe::Mesh* turn_triangle_ = nullptr;
	
	//クラスのインスタンス
	Board* board_ = new Board(DXE_WINDOW_WIDTH,DXE_WINDOW_HEIGHT);
	PersonManager* pmgr_ = PersonManager::GetInstance();
	AllyManager* amgr_ = AllyManager::GetInstance();

	//メンバ関数群
	void DrawBoard();
	void RenderUnit();
	void GetSquareInfoGUIByClick();
	void Dedug();


	void RenderCard(int x, int y);
	void RenderHand();


	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	
	//debug
	bool ui = true;

	//UI関数
	void PersonBox();
	void AllyInfoUI();

private:

	int kboard_size_ = 10;
	const int knum_cells_ = kboard_size_ * kboard_size_;

	int w1 = DXE_WINDOW_WIDTH / 10;
	int h1 = DXE_WINDOW_HEIGHT / 10;

	int mouse_point_x_ = 0;
	int mouse_point_y_ = 0;
	int mouse_pos_x_ = 0;
	int mouse_pos_y_ = 0;
	tnl::Vector3 msv_ = {0,0,0};
	tnl::Vector3 ray_ = {0,0,0};
	tnl::Vector3 hit_ = {0,0,0};

	VECTOR start_pos_ = { 0,0,0 };
	VECTOR end_pos_ = {0,0,0};

	int c1_face = 0;
	int face_ = 0;

	int cnt = 55;

	//カラーコード
	int black = GetColor(0,0,0);
	int red = GetColor(255,0,0);
	int silver = GetColor(192,192,192);
	int darkolivegreen = GetColor(85,107,47);
	
	int dxlib_blend_mode_ = DX_BLENDMODE_ALPHA;
};