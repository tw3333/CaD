#include "gm_scene_test2.h"

Test2::~Test2() {

	delete camera_;
	delete img_board_;

	
}

void Test2::initialzie() {

	camera_ = new GmCamera();
	camera_->pos_ = { 0,620,-560 };
	camera_->ctrl_type_ = GmCamera::CTRL_TYPE_QTN;
	camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(55));

	img_board_ = dxe::Mesh::CreatePlaneMV({ (float)w1 * 8,(float)h1 * 8,0 });
	img_board_->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	img_board_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	img_board_->pos_ = { 0,0,0 };

	int b_w = w1 * 8 / 10;
	int b_h = h1 * 8 / 10;

	player_ = dxe::Mesh::CreatePlaneMV({ (float)74, (float)74, 0 });
	player_->setTexture(dxe::Texture::CreateFromFile("graphics/unit/ally/c1_board_img.png"));
	//player_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(50));
	player_->pos_ = { 0,44,0};
	player_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(0));
	c1_face = LoadGraph("graphics/unit/ally/c1_face.png");
	//SetLightEnable(FALSE);

	square_ = dxe::Mesh::CreatePlaneMV({ (float)b_w * 1, (float)b_h * 1, 0 });
	square_->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
	square_->pos_ = { 0,1,0 };
	square_->rot_q_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));




}

void Test2::update(float delta_time) {
	GameManager* gmgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		//player_->pos_ += tnl::Vector3::TransformCoord({ 0, -1, 0 }, camera_->rot_);
		square_->pos_.z += 36;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
/*		player_->pos_ += tnl::Vector3::TransformCoord({ 0, 1, 0 }, camera_->rot_);
		*/square_->pos_.z += -36;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		//player_->pos_ += tnl::Vector3::TransformCoord({ -1, 0, 0 }, camera_->rot_);
		square_->pos_.x += -64;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		square_->pos_.x += 64;

		//player_->pos_ += tnl::Vector3::TransformCoord({ 1, 0, 0 }, camera_->rot_);
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, 1,  0 }, camera_->rot_);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, -1, 0 }, camera_->rot_);
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_R)) {
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-1));
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_F)) {
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(1));
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_U)) {

		if (ui) { ui = false; }
		else if (!ui) { ui = true; }
	}

}

void Test2::render() {

	camera_->update();
	//DrawGridGround(camera_, 50, 20);


	img_board_->render(camera_);
	player_->render(camera_);
	square_->render(camera_);

	//DrawBox(0,0,w1*10,(h1*1) / 2,silver,true);

	//DrawBox((w1*1)/2, 0, w1 * 9 + (w1*1/2), h1 * 10, darkolivegreen, true);

	//DrawBox(0, 0, w1 * 10, (h1 * 1) / 2, silver, true);
	//DrawBox(0 + 10,h1*1/2+ 10, w1*4 , h1*1 ,silver,true);
	//DrawBox(0 + 10, h1*1 + 10, w1 * 2 +10, h1*3 +10, silver, true);

	DrawStringEx(w1 * 8, h1 * 2, -1, "s_posX%f", square_->pos_.x);
	DrawStringEx(w1 * 8, h1 * 2 + 20, -1, "s_posY%f", square_->pos_.y);
	DrawStringEx(w1 * 8, h1 * 2 + 40, -1, "s_posZ%f", square_->pos_.z);

	DrawStringEx(w1 * 8, h1 * 2 + 60, -1, "rot_%d", camera_->rot_);




	for (int i = 0; i < 10; ++i) {

		int mas_x = (w1 * 8) / 10;
		int mas_z = (h1 * 8) / 10;

		DrawLine3D(VGet(-640.0f, 0.0f, -360.0f + (mas_z * i)), VGet(640.0f, 0.0f, -360.0f + (mas_z * i)), red);
		DrawLine3D(VGet(-640.0f + (mas_x * i), 0.0f, -360.0f), VGet(-640.0f + (mas_x * i), 0.0f, 360.0f), red);

	}

	DrawLine3D({ 640.f,0.0f,-360.0f }, { 640.f,0.0f,360.0f }, red);
	



	DrawBox(0,0,w1*10,(h1*1) / 2,silver,true);

	//DrawBox((w1*1)/2, 0, w1 * 9 + (w1*1/2), h1 * 10, darkolivegreen, true);

	DrawBox(0, 0, w1 * 10, (h1 * 1) / 2, silver, true);
	DrawBox(0 + 10,h1*1/2+ 10, w1*4 , h1*1 ,silver,true);
	//DrawBox(0 + 10, h1*1 + 10, w1 * 2 +10, h1*3 +10, silver, true);
	//PersonBox();
	if (ui) {

		DrawGridGround(camera_, 50, 20);
		//アタリ線
		for (int i = 0; i < 10; ++i) {
			DrawLine(0, h1 + h1 * i, DXE_WINDOW_WIDTH, h1 + h1 * i, -1);
			DrawLine(w1 + w1 * i, 0, w1 + w1 * i, DXE_WINDOW_HEIGHT, -1);
		}
	}

}

//UI関数
void Test2::PersonBox() {


	DrawBox(0 + 10, h1 * 1 + 10, w1 * 2 + 20, h1 * 3 + 10, silver, true); //下地
	
	DrawExtendGraph(15, h1 * 1 + 15, w1 * 2 + 15, h1*2, c1_face,false); //画像

	DrawBox(15, h1 * 1 + 15, w1 * 2 + 15, h1 * 2, black,false); //画像の枠

	DrawBox(15, h1 * 2 + 15, w1 * 2 + 15,h1*2 + 25, black, false); //HPバー枠

	DrawStringEx(15, h1 * 2, 1, "HP:%d/%d", pmgr_->person[0]->HP,pmgr_->person[0]->HPMAX);


}