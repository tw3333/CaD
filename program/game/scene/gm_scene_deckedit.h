#include "gm_scene_base.h"
#include "../gm_manager.h"
#include "../gm_card_manager.h"
#include <iostream>
#include <vector>

#include <array>

#include "../gm_person_manager.h"

class SceneDeckEdit : public SceneBase {
public:

	SceneDeckEdit() {
	}
	~SceneDeckEdit() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	
	void LoadDeckEditGraph();
	
	void Tab(bool flag);
	
	void Chara01_Tab(bool flag);
	void Chara02_Tab(bool flag);
	void Chara03_Tab(bool flag);
	void Chara04_Tab(bool flag);

	void opChara01_Tab(bool flag);
	void opChara02_Tab(bool flag);
	void opChara03_Tab(bool flag);
	void opChara04_Tab(bool flag);

	void opTab(bool flag);

	//カード描写
	void DrawCardZone(); //カードがどんなのかを描写
	void DrawDeckZone(); //デッキ内容を描写
	void DrawListZone(); //持っているカードのリストを描写

	//カードとマウスの判定
	void ListMouseCheck(int mx, int my);


	void CheckHandle(std::vector<Card*> &deck, Card* card );

	//GameManager
	GameManager* gmgr = GameManager::GetInstance();

	//PersonManager
	PersonManager* pmgr = PersonManager::GetInstance();

	//CardManager用
	CardManager* cmgr = CardManager::GetInstance();
	
private:

	//マウス用
	int MouseX = 0; //x
	int MouseY = 0; //y
	bool PushCheck = 0;



	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;

	int t_chara = 0;
	int t_deckedit = 0;
	int t_deck = 0;

	int tab_flame = 0;
	int chara01_face = 0;
	int chara02_face = 0;
	int chara03_face = 0;
	int chara04_face = 0;

	int deck_flame = 0;

	int deck_fmove_x = 0;
	int deck_fmove_y = 0;

	bool tab;
	bool draw_tab;

	bool chara1_tab;
	bool chara2_tab;
	bool chara3_tab;
	bool chara4_tab;


	int tab_flame_move = 0;
	int c1deck_count = 0;


	//カラーコード
	int white = GetColor(255,255,255);
	int gray = GetColor(128,128,128);
	int dimgray = GetColor(100,100,100);
	int dsgray = GetColor(47, 79, 79); //darkslategray

	bool d_select_chara1 = false;
	bool d_select_chara2 = false;
	bool d_select_chara3 = false;
	bool d_select_chara4 = false;

	
};
