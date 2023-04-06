#include "gm_scene_test2.h"

Test2::~Test2() {

	delete camera_;
	//delete img_board_;

	
}

void Test2::initialzie() {

	//SetUseLighting(false);

	camera_ = new GmCamera();
	camera_->pos_ = { 0,620,-560 };
	camera_->ctrl_type_ = GmCamera::CTRL_TYPE_QTN;
	camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(55));


	
	//img_board_ = dxe::Mesh::CreatePlaneMV({ (float)w1 * 8,(float)h1 * 8,0 });
	//img_board_->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	//img_board_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	//img_board_->pos_ = { 0,0,0 };

	int b_w = w1 * 8 / 10;
	int b_h = h1 * 8 / 10;

	//player_ = dxe::Mesh::CreatePlaneMV({ (float)74, (float)74, 0 });
	//player_->setTexture(dxe::Texture::CreateFromFile("graphics/unit/ally/c1_board_img.png"));
	////player_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(50));
	//player_->pos_ = { 0,44,0};
	//player_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(0));
	
	//c1_face = LoadGraph(amgr_->allies_[0]->battle_img_.c_str());
	//SetLightEnable(FALSE);

	board_->MakeObjBoard();

//	board_->squares_[0][0]->setSquareType(Square::kAlly);
////	board_->squares_[0][0]->MakeObjUnit();
//	
//
//	board_->squares_[9][0]->setSquareType(Square::kAlly);
//	board_->squares_[9][0]->MakeObjUnit();

	amgr_->MakeAllies();
	amgr_->LoadAlliesGraph();

	c1_face = LoadGraph(amgr_->allies_[0]->battle_img_.c_str());

	amgr_->allies_[0]->setAllyPos(2,4);
	board_->squares_[2][4]->setUnit(amgr_->allies_[0]);
	board_->squares_[2][4]->setSquareType(Square::SquareType::kAlly);
	board_->squares_[2][4]->MakeObjUnit(amgr_->allies_[0]->battle_img_);

	amgr_->allies_[1]->setAllyPos(2, 3);
	board_->squares_[2][3]->setUnit(amgr_->allies_[1]);
	board_->squares_[2][3]->setSquareType(Square::SquareType::kAlly);
	board_->squares_[2][3]->MakeObjUnit(amgr_->allies_[0]->battle_img_);


	square_ = dxe::Mesh::CreatePlaneMV({ (float)b_w * 1, (float)b_h * 1, 0 });
	square_->setTexture(dxe::Texture::CreateFromFile(amgr_->allies_[0]->battle_img_.c_str()));
	square_->pos_ = { -64,1,-36 };
	square_->rot_q_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));


}

void Test2::update(float delta_time) {
	
	GameManager* gmgr = GameManager::GetInstance();

	GetMousePoint(&mouse_point_x_, &mouse_point_y_);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		//player_->pos_ += tnl::Vector3::TransformCoord({ 0, -1, 0 }, camera_->rot_);
		square_->pos_.z += 72;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		/*player_->pos_ += tnl::Vector3::TransformCoord({ 0, 1, 0 }, camera_->rot_);*/
		square_->pos_.z += -72;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		//player_->pos_ += tnl::Vector3::TransformCoord({ -1, 0, 0 }, camera_->rot_);
		square_->pos_.x += -128;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		square_->pos_.x += 128;

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
	board_->obj_board_->render(camera_);

	//board_->squares_[0][0]->obj_unit_->render(camera_);
	RenderUnit();


	RenderHand();
	

	square_->render(camera_);

	//DrawBillboard3D(VGet(0,1,0),0.0f,0.0f, 64, 0,c1_face,true);
	//DrawBox(0,0,w1*10,(h1*1) / 2,silver,true);

	//DrawBox((w1*1)/2, 0, w1 * 9 + (w1*1/2), h1 * 10, darkolivegreen, true);

	//DrawBox(0, 0, w1 * 10, (h1 * 1) / 2, silver, true);
	//DrawBox(0 + 10,h1*1/2+ 10, w1*4 , h1*1 ,silver,true);
	//DrawBox(0 + 10, h1*1 + 10, w1 * 2 +10, h1*3 +10, silver, true);

	DrawStringEx(w1 * 9, h1 * 2, -1, "s_posX%f", square_->pos_.x);
	DrawStringEx(w1 * 9, h1 * 2 + 20, -1, "s_posY%f", square_->pos_.y);
	DrawStringEx(w1 * 9, h1 * 2 + 40, -1, "s_posZ%f", square_->pos_.z);

	DrawStringEx(w1 * 9, h1 * 2 + 60, -1, "rot_%d", camera_->rot_);

	DrawStringEx(w1 * 9, h1 * 2 + 80, -1, "mouseX:%d", mouse_point_x_);
	DrawStringEx(w1 * 9, h1 * 2 + 100, -1, "mouseY:%d", mouse_point_y_);
	DrawStringEx(w1 * 9, h1 * 2 + 120, -1, "path:%s\n", amgr_->allies_[0]->battle_img_.c_str());


	GetSquareInfoGUIByClick();

	for (int i = 0; i < 10; ++i) {

		int mas_x = (w1 * 8) / 10;
		int mas_z = (h1 * 8) / 10;

		DrawLine3D(VGet(-640.0f, 0.0f, -360.0f + (mas_z * i)), VGet(640.0f, 0.0f, -360.0f + (mas_z * i)), red);
		DrawLine3D(VGet(-640.0f + (mas_x * i), 0.0f, -360.0f), VGet(-640.0f + (mas_x * i), 0.0f, 360.0f), red);

	}



	//DrawLine3D({ 640.f,0.0f,-360.0f }, { 640.f,0.0f,360.0f }, red);

	DrawLine3D({-640.0f,1000,1000.0f},{-640.0f,0.0f,360.0f},red);
	DrawLine3D({ 640.0f,1000,1000.0f }, { 640.0f,0.0f,360.0f }, red);



	DrawBox(0,0,w1*10,(h1*1) / 2,silver,true);

	//DrawBox((w1*1)/2, 0, w1 * 9 + (w1*1/2), h1 * 10, darkolivegreen, true);

	DrawBox(0, 0, w1 * 10, (h1 * 1) / 2, silver, true);
	DrawBox(0 + 10,h1*1/2+ 10, w1*4 , h1*1 ,silver,true);
	//DrawBox(0 + 10, h1*1 + 10, w1 * 2 +10, h1*3 +10, silver, true);
	//PersonBox();
	if (ui) {

		DrawGridGround(camera_, 50, 20);
		//ƒAƒ^ƒŠü
		for (int i = 0; i < 10; ++i) {
			DrawLine(0, h1 + h1 * i, DXE_WINDOW_WIDTH, h1 + h1 * i, -1);
			DrawLine(w1 + w1 * i, 0, w1 + w1 * i, DXE_WINDOW_HEIGHT, -1);
		}
	}

}

//GUIŠÖ”ŒQ
void Test2::PersonBox() {


	DrawBox(0 + 10, h1 * 1 + 10, w1 * 2 + 20, h1 * 3 + 10, silver, true); //‰º’n
	
	DrawExtendGraph(15, h1 * 1 + 15, w1 * 2 + 15, h1*2, c1_face,false); //‰æ‘œ

	DrawBox(15, h1 * 1 + 15, w1 * 2 + 15, h1 * 2, black,false); //‰æ‘œ‚Ì˜g

	DrawBox(15, h1 * 2 + 15, w1 * 2 + 15,h1*2 + 25, black, false); //HPƒo[˜g

	DrawStringEx(15, h1 * 2, 1, "HP:%d/%d", pmgr_->person[0]->HP,pmgr_->person[0]->HPMAX);


}

void Test2::GetSquareInfoGUIByClick() {

	int b_w0 = -640;
	int b_h0 = 360;

	int w1 = 128;
	int h1 = 72;

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (b_w0 < mouse_point_x_ && mouse_point_x_ < b_w0 + w1 && b_h0 < mouse_point_y_ && mouse_point_y_ < b_w0 - h1) {

			if (ui) { ui = false; }
			else if (!ui) { ui = true; }

		}
	}




}




//•`ŽÊŠÖ˜A
void Test2::DrawBoard() {

	/*img_board_ = dxe::Mesh::CreatePlaneMV({ (float)w1 * 8,(float)h1 * 8,0 });
	img_board_->setTexture(dxe::Texture::CreateFromFile("graphics/512.bmp"));
	img_board_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	img_board_->pos_ = { 0,0,0 };

	img_board_->render(camera_);
*/


}

void Test2::RenderUnit() {

	for (int i = 0; i < 10; ++i) {
		for (int k = 0; k < 10; ++k) {

			if (board_->squares_[i][k]->getSquareType() == Square::SquareType::kEnpty) {
				//board_->squares_[i][k]->obj_unit_->render(camera_);

			}
			else if (board_->squares_[i][k]->getSquareType() == Square::SquareType::kAlly) {

				board_->squares_[i][k]->obj_unit_->render(camera_);



			}


		}


	}

}

void Test2::RenderCard(int x, int y) {

	float h_1 = DXE_WINDOW_HEIGHT / 10;
	float w_1 = DXE_WINDOW_WIDTH / 10;

	float card_w = w_1;
	float card_h = (h_1 * 2) + (h_1 / 2);

	DrawBox(x, y, x + card_w, y + card_h,silver, true);




}

void Test2::RenderHand() {

	float h_1 = DXE_WINDOW_HEIGHT / 10;
	float w_1 = DXE_WINDOW_WIDTH / 10;

	float card_w_ = w_1;
	float card_h_ = (h_1 * 2) + (h_1 / 2);

	RenderCard(w_1*4,h_1*7);


}