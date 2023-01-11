#include "gm_scene_base.h"
#include "../gm_manager.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>


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

	void CheckHandle(std::array<int, 10>& ary, int new_handle);

private:

	std::array<int, 10> c1deck{};
	std::array<int, 10> c2deck{};
	std::array<int, 10> c3deck{};
	std::array<int, 10> c4deck{};


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


	int c1_d1 = 0;
	int c1_d2 = 0;
	int c1_d3 = 0;
	int c1_d4 = 0;
	int c1_d5 = 0;

	int c1_c1 = 0;
	int c1_c2 = 0;
	int c1_c3 = 0;
	int c1_c4 = 0;
	int c1_c5 = 0;
	int c1_c6 = 0;
	int c1_c7 = 0;
	int c1_c8 = 0;
	int c1_c9 = 0;
	int c1_c10 = 0;



	int c2_d1 = 0;
	int c2_d2 = 0;
	int c2_d3 = 0;
	int c2_d4 = 0;
	int c2_d5 = 0;

	int c3_d1 = 0;
	int c3_d2 = 0;
	int c3_d3 = 0;
	int c3_d4 = 0;
	int c3_d5 = 0;

	int c4_d1 = 0;
	int c4_d2 = 0;
	int c4_d3 = 0;
	int c4_d4 = 0;
	int c4_d5 = 0;

	//std::vector<int> c1deck;
	//std::vector<int> c2deck;
	//std::vector<int> c3deck;
	//std::vector<int> c4deck;

	int tab_flame_move = 0;

	int white = GetColor(255,255,255);
	int gray = GetColor(128,128,128);
	int dimgray = GetColor(100,100,100);

	int c1deck_count = 0;



};
