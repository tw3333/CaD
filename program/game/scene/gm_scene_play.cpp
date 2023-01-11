#include "gm_scene_play.h"
#include "gm_scene_battle.h"
#include "gm_scene_selectphase.h"

ScenePlay::~ScenePlay() {
	delete camera_;
	delete ctrl_box_;
	delete floor_;
	delete dungeon_;

	for (auto box : field_boxs_) delete box;
}



void ScenePlay::initialzie() {
	//ScreenSetup
	playscreen = MakeScreen((int)DXE_WINDOW_WIDTH, (int)DXE_WINDOW_HEIGHT, TRUE);
	miniscreen = MakeScreen(width1 * 3, height1 * 3, TRUE);

	camera_ = new GmCamera();
	camera_->pos_ = { 0, 0, 50 };
	camera_->ctrl_type_ = GmCamera::CTRL_TYPE_QTN;

	//プレイヤーbox
	ctrl_box_ = dxe::Mesh::CreateBoxMV(50);
	ctrl_box_->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
	ctrl_box_->pos_ = { 0, 0, 0 };

	//flagに使う床
	floor_ = dxe::Mesh::CreatePlaneMV({ 500,500,0 });
	floor_->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	floor_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	floor_->pos_ = { 0,25,0 };

	// 使用するテクスチャを事前ロード
	Shared<dxe::Texture> texs[3];
	texs[0] = dxe::Texture::CreateFromFile("graphics/wall_box.bmp");
	texs[1] = dxe::Texture::CreateFromFile("graphics/wall_box.bmp");
	texs[2] = dxe::Texture::CreateFromFile("graphics/box.bmp");

	// ボックス３種類をあらかじめ作成
	dxe::Mesh* origin_boxs[3];
	for (int i = 0; i < 3; ++i) {
		origin_boxs[i] = dxe::Mesh::CreateBoxMV(50);
		origin_boxs[i]->setTexture(texs[i]);
	}

	// csv からフィールド情報を読み込んであらかじめ作成してある
	// ボックスをクローンして生成することで生成速度アップ
	float sx = -250;
	float sz = 250;

	dungeon_ = new SceneSelectPhase();

	SceneSelectPhase selectphase;

	std::vector<std::vector<std::string>> csv = tnl::LoadCsv("field.csv");

	for (int i = 0; i < csv.size(); ++i) {
		for (int k = 0; k < csv[i].size(); ++k) {
			int n = std::atoi(csv[i][k].c_str());
			// 0 は地面扱いとして飛ばす
			if (0 == n) continue;
			dxe::Mesh* mesh = origin_boxs[n - 1]->createClone();
			mesh->pos_ = { sx + k * 50, 0, sz - i * 50 };
			field_boxs_.emplace_back(mesh);
		}
	}

}

void ScenePlay::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	tnl::Vector3 move = { 0, 0, 0 };

	//
	// キーボード操作
	//
	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) jump_vel_ = 10.0f;
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) move += camera_->left().xz();
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) move += camera_->right().xz();
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) move += camera_->front().xz();
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) move += camera_->back().xz();*/

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, 0, 50 }, camera_->rot_);
		/*ctrl_box_->pos_ += tnl::Vector3::TransformCoord({ 0, 0, 50 }, camera_->rot_);*/

	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-90));
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(90));
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(180));
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_A))	camera_->free_look_angle_xy_.y += tnl::ToRadian(1);
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) camera_->free_look_angle_xy_.y -= tnl::ToRadian(1);
	if (tnl::Input::IsKeyDown(eKeys::KB_W))	camera_->free_look_angle_xy_.x += tnl::ToRadian(1);
	if (tnl::Input::IsKeyDown(eKeys::KB_S))	camera_->free_look_angle_xy_.x -= tnl::ToRadian(1);


	//
	// ジョイパッド操作
	//
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_1)) jump_vel_ = 10.0f;
	tnl::Vector3 lstick = tnl::Input::GetLeftStick();
	if (lstick.length() > 0.1f) {
		move += camera_->front().xz() * -lstick.y;
		move += camera_->left().xz() * -lstick.x;
	}

	tnl::Vector3 rstick = tnl::Input::GetRightStick();
	if (rstick.length() > 0.1f) {
		camera_->free_look_angle_xy_.y += tnl::ToRadian(rstick.x);
		camera_->free_look_angle_xy_.x += tnl::ToRadian(rstick.y);
	}

	//
	// 移動処理
	//
	move.normalize();
	move *= 50;
	tnl::Vector3 prev_pos = ctrl_box_->pos_;

	ctrl_box_->pos_ += move;

	//ジャンプに関する処理
	ctrl_box_->pos_.y += jump_vel_;
	if (ctrl_box_->pos_.y <= 0) {
		ctrl_box_->pos_.y = 0;
		jump_vel_ = 0;
	}
	else {
		jump_vel_ -= 0.98f;
	}


	// 
	// 衝突判定と補正
	//
	tnl::Vector3 size1 = { 50, 50, 50 };
	tnl::Vector3 size2 = { 50, 50, 50 };

	// 操作ボックスに近い順にソート
	field_boxs_.sort([&](const dxe::Mesh* l, const dxe::Mesh* r) {
		float ld = (ctrl_box_->pos_ - l->pos_).length();
		float rd = (ctrl_box_->pos_ - r->pos_).length();
		return ld < rd;
		});

	for (auto box : field_boxs_) {
		if (tnl::IsIntersectAABB(ctrl_box_->pos_, size1, box->pos_, size2)) {
			int n = tnl::GetCorrectPositionIntersectAABB(prev_pos, size1, box->pos_, size2, ctrl_box_->pos_);
			// ボックスの上に補正されたらジャンプ力リセット
			if (2 == n) jump_vel_ = 0;
		}
	}

	camera_->target_ = ctrl_box_->pos_;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneBattle());
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		mgr->chengeScene(new SceneSelectPhase());
	}

}

void ScenePlay::render()
{
	//
	//mainscreen_render
	//

	SetDrawScreen(playscreen);
	SetBackgroundColor(0, 0, 0, 255);
	ClearDrawScreen();

	camera_->update();

	ctrl_box_->render(camera_);
	floor_->render(camera_);

	for (auto box : field_boxs_) box->render(camera_);


	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, -1);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, -1);
	}

	//
	//miniscreen_render(minimap)
	//

	SetDrawScreen(miniscreen);
	SetBackgroundColor(70, 130, 180, 255);
	ClearDrawScreen();

	//あたり線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, m_h + m_h * i, m_window_width, m_h + m_h * i, -1);
		DrawLine(m_w + m_w * i, 0, m_w + m_w * i, m_window_height, -1);
	}


	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, playscreen, true);
	DrawGraph(0, 0, miniscreen, true);
}
