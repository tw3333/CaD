#include "gm_scene_base.h"

class SceneBattle : public SceneBase {
public:
	
	SceneBattle() {}
	~SceneBattle(){}

	void initialzie() override;
	void update(float dalta_time) override;
	void render() override;

	void DrawCard(int x, int y, int x2, int y2, int chara, bool flag);

	//グラフィックロード用
	void LoadBattleGraph();

	void BattleStart();

private:
	
	int move = 0;
	float timer = 0;
	bool finish;
	int img_background;
	int img_mon1;
	int img_chara1_face;
	int img_chara2_face;
	int img_chara3_face;
	int img_chara4_face;
	int img_enemy1_face;
	int img_turn;

	int select_flame;
	
	int card1 = 0;
	int card2 = 0; 
	int card3 = 0; 
	int card4 = 0;
	int card5 = 0;
	int card6 = 0;
	int card7 = 0;
	int card8 = 0;
	int card9 = 0;
	int card10 = 0;
	int card11 = 0;
	int card12 = 0;
	int card13 = 0;
	int card14 = 0;
	int card15 = 0;


	int chara_select;
	int chara_num = 0;

	int action_count = 0; //行動上限
	int turn_count = 0;
	int order_count = 0;//行動順

	int select_move = 0;
	int img_turn_move = 0;

	bool enemy_anime;

	unsigned int gray = GetColor(138, 140, 142);
	unsigned int red = GetColor(255, 0, 0);


	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;
	
};
