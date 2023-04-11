#include "gm_scene_test2.h"

Test2::~Test2() {

	delete camera_;
	//delete img_board_;

	
}

void Test2::initialzie() {

	//SetUseLighting(false);
	SetMouseDispFlag(true);
	//SetCameraNearFar(100.0f,101.0f);
	camera_ = new GmCamera();
	camera_->pos_ = { 0,680,-605 };
	camera_->ctrl_type_ = GmCamera::CTRL_TYPE_QTN;
	camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(54));

	//SetCameraNearFar(100.0f, 15000.0f);
	
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
	board_->squares_[0][0]->MakeObjSquare();
	board_->squares_[3][6]->MakeObjSquare();


//	board_->squares_[0][0]->setSquareType(Square::kAlly);
////	board_->squares_[0][0]->MakeObjUnit();
//	
//
//	board_->squares_[9][0]->setSquareType(Square::kAlly);
//	board_->squares_[9][0]->MakeObjUnit();

	amgr_->MakeAllies();
	amgr_->LoadAlliesGraph();

	c1_face = LoadGraph(amgr_->allies_[0]->battle_img_.c_str());
	face_ = LoadGraph("graphics/unit/ally/c1_face2_img.png");

	amgr_->allies_[0]->setAllyPos(2,4);
	board_->squares_[2][4]->setUnit(amgr_->allies_[0]);
	board_->squares_[2][4]->setSquareType(Square::SquareType::kAlly);
	board_->squares_[2][4]->MakeObjUnit(amgr_->allies_[0]->battle_img_);

	amgr_->allies_[1]->setAllyPos(2, 3);
	board_->squares_[2][3]->setUnit(amgr_->allies_[1]);
	board_->squares_[2][3]->setSquareType(Square::SquareType::kAlly);
	board_->squares_[2][3]->MakeObjUnit(amgr_->allies_[0]->battle_img_);


	square_ = dxe::Mesh::CreatePlaneMV({ (float)b_w * 1, (float)b_h * 1, 0 });
	square_->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
	square_->pos_ = { -64,0,-36 };
	square_->rot_q_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	turn_triangle_ = dxe::Mesh::CreateTriangleEquilateralMV((float)50);
	turn_triangle_->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
	turn_triangle_->pos_ = {-64,110,5 };
	turn_triangle_->rot_q_ = tnl::Quaternion::RotationAxis({ 0,0,1 }, tnl::ToRadian(180));




}

void Test2::update(float delta_time) {
	
	GameManager* gmgr = GameManager::GetInstance();

	GetMousePoint(&mouse_point_x_, &mouse_point_y_);

	//マウスポインタがある画面上の座標に該当する3D空間上のNear面の座標を取得
	//start_pos_ = ConvScreenPosToWorldPos(VGet(mouse_point_x_,mouse_point_y_,0.0f));
	//マウスポインタがある画面上の座標に該当する3D空間上のFar面の座標を取得
	end_pos_ = ConvScreenPosToWorldPos(VGet(mouse_point_x_, mouse_point_y_, 1.0f));



	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		//player_->pos_ += tnl::Vector3::TransformCoord({ 0, -1, 0 }, camera_->rot_);
		square_->pos_.z += 72;
		turn_triangle_->pos_.z += 72;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		/*player_->pos_ += tnl::Vector3::TransformCoord({ 0, 1, 0 }, camera_->rot_);*/
		square_->pos_.z += -72;
		turn_triangle_->pos_.z += -72;

	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		//player_->pos_ += tnl::Vector3::TransformCoord({ -1, 0, 0 }, camera_->rot_);
		square_->pos_.x += -128;
		turn_triangle_->pos_.x += -128;

	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		square_->pos_.x += 128;
		turn_triangle_->pos_.x += 128;


		//player_->pos_ += tnl::Vector3::TransformCoord({ 1, 0, 0 }, camera_->rot_);
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, 1,  0 }, camera_->rot_);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, -1, 0 }, camera_->rot_);
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, 0,  1 }, camera_->rot_);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		camera_->pos_ += tnl::Vector3::TransformCoord({ 0, 0, -1 }, camera_->rot_);
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_R)) {
		
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(1));
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_F)) {
		camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-1));
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_U)) {

		if (ui) { ui = false; }
		else if (!ui) { ui = true; }
	}

	turn_triangle_->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(3));
	//camera_->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(cnt));
	
	tnl::Vector3 msv = tnl::Input::GetMousePosition();
	
	tnl::Vector3 ray = tnl::Vector3::CreateScreenRay(
		msv.x
		, msv.y
		, camera_->screen_w_
		, camera_->screen_h_
		, camera_->view_
		, camera_->proj_);

	tnl::Vector3 hit;

	if (tnl::IsIntersectLinePlane(camera_->pos_, camera_->pos_ + (ray * 10000.0f), { 10, 10, 10 }, { 0, 1, 0 }, &hit)) {
		square_->pos_ = hit;
	}


}

void Test2::render() {

	camera_->update();

	board_->obj_board_->render(camera_);
	board_->squares_[0][0]->obj_square_->render(camera_);
	board_->squares_[3][6]->obj_square_->render(camera_);

	RenderUnit();

	square_->render(camera_);
	
	turn_triangle_->render(camera_);

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
	//DrawStringEx(w1 * 1, h1 * 2 + 140, -1, "x.begin%f",board_->squares_[0][0]->getXZBeginScreenPos().x);
	DrawStringEx(w1 * 9, h1 * 2 + 160, -1, "x:%d", board_->squares_[0][0]->pos_x_);
	
	DrawStringEx(w1 * 9, h1 * 2 + 180, -1, "cpos.x:%f", camera_->pos_.x);
	DrawStringEx(w1 * 9, h1 * 2 + 200, -1, "cpos.y:%f", camera_->pos_.y);
	DrawStringEx(w1 * 9, h1 * 2 + 220, -1, "cpos.z:%f", camera_->pos_.z);
	DrawStringEx(w1 * 9, h1 * 2 + 240, -1, "cnt:%d", cnt);



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



	//DrawBox(0,0,w1*10,(h1*1) / 2,silver,true);

	//DrawBox((w1*1)/2, 0, w1 * 9 + (w1*1/2), h1 * 10, darkolivegreen, true);

	//DrawBox(0, 0, w1 * 10, (h1 * 1) / 2, silver, true);
	//DrawBox(0 + 10,h1*1/2+ 10, w1*4 , h1*1 ,silver,true);
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
	RenderHand();
	//AllyInfoUI();

	DrawExtendGraph(10,h1*1,10 + w1*2,h1*2,face_,false);

	DrawLine(0,(h1*7)+(h1*1)/2,w1*1, (h1 * 7) + (h1 * 1) / 2,-1);
	DrawLine(w1*1/2,h1*7, w1 * 1 / 2,h1*8,-1);

	DrawLine(w1*9, (h1 * 7) + (h1 * 1) / 2, w1 * 10, (h1 * 7) + (h1 * 1) / 2, -1);
	DrawLine(w1 * 9 + (w1*1 / 2), h1 * 7, w1 * 9 + (w1 * 1 / 2), h1 * 8, -1);


}

//UI関数群
void Test2::PersonBox() {


	DrawBox(0 + 10, h1 * 1 + 10, w1 * 2 + 20, h1 * 3 + 10, silver, true); //下地
	
	DrawExtendGraph(15, h1 * 1 + 15, w1 * 2 + 15, h1*2, c1_face,false); //画像

	DrawBox(15, h1 * 1 + 15, w1 * 2 + 15, h1 * 2, black,false); //画像の枠

	DrawBox(15, h1 * 2 + 15, w1 * 2 + 15,h1*2 + 25, black, false); //HPバー枠

	DrawStringEx(15, h1 * 2, 1, "HP:%d/%d", pmgr_->person[0]->HP,pmgr_->person[0]->HPMAX);


}

void Test2::AllyInfoUI() {

	DrawBox(10, 10, w1 * 2, h1 * 2, silver, true); //下地
	DrawBox(15,15,(w1*2)-5,(h1*1)-5,black,false); //顔画像


	//DrawExtendGraph();




}

void Test2::GetSquareInfoGUIByClick() {

	VECTOR square_x_begin;
	VECTOR square_x_end;

	VECTOR square_z_begin;
	VECTOR square_z_end;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {

			if (board_->squares_[i][j]->getXZBeginScreenPos().x < mouse_point_x_ &&
				mouse_point_x_ < board_->squares_[i][j]->getXZEndScreenPos().x &&
				board_->squares_[i][j]->getXZBeginScreenPos().z < mouse_point_y_ && 
				mouse_point_y_ < board_->squares_[i][j]->getXZEndScreenPos().y)
			{


				DrawStringEx(w1 * 9, h1 * 2 + 260, -1, "square[%d][%d]", board_->squares_[i][j]->getSquareRow(),board_->squares_[i][j]->getSquareCol() );
				

			}

		}

	}


	//if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
	//	if (b_w0 < mouse_point_x_ && mouse_point_x_ < b_w0 + w1 && b_h0 < mouse_point_y_ && mouse_point_y_ < b_w0 - h1) {

	//		if (ui) { ui = false; }
	//		else if (!ui) { ui = true; }

	//	}
	//}




}




//描写関連
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