#include "../gm_manager.h"
#include "gm_scene_base.h"
#include "../gm_person_manager.h"




class SceneBattle : public SceneBase {
public:
	
	SceneBattle(){}
	~SceneBattle();


	void initialzie() override;
	void update(float dalta_time) override;
	void render() override;

	void DrawCard(int x, int y, int x2, int y2, int chara, bool flag);

	//グラフィックロード用
	void LoadBattleGraph();

	void BattleStart();

	//関数群
	void DrawTurn();
	void drawCardUp(int x, int y);
	void DrawHands();
	void EaseTurnImage(double out_t, double in_t, int x_s, int x_e);
	void EaseImageCard1(double t, int x_s, int x_e, int delay);

	
	//イージング関数
	double easeInExpo(double t);
	double easeOutExpo(double t);

	//PersonManager
	


	//GameManager mgr;
	//int p1HP = mgr.pmgr_->person1->HP;
	
private:
	

	int MouseX = 0;
	int MouseY = 0;
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

	//マウスポインタに合わせてカードを上げる用
	int CardUp_1 = 0;
	int CardUp_2 = 0;
	int CardUp_3 = 0;
	int CardUp_4 = 0;
	int CardUp_5 = 0;
	int CardUp_6 = 0;
	int CardUp_7 = 0;
	int CardUp_8 = 0;
	int CardUp_9 = 0;
	int CardUp_10 = 0;

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

	int hp_bar = 0;
	int hp_bar_back = 0;
	int img_yourturn = 0;
	int img_enemyturn = 0;

	int chara_select;
	int chara_num = 0;

	int action_count = 0; //行動上限
	int turn_count = 0;
	int order_count = 0;//行動順

	int select_move = 0;
	int img_turn_move = 0;

	bool enemy_anime;
	bool dealcard;
	int numOfCards = 0;

	int cardPidl_6 = 51.2;
	float cardPild_7 = 85.3;
	float cardPild_8 = 109.7;
	int cardPild_9 = 128;
	float cardPild_10 = 142.2;

	float hp_max = 40.0;
	float hp_now = 0.0;
	int cost_max = 3;
	int cost_now = 0;
	int Bar_Width = 300;
	int Bar = 0;
	int test = 0;

	//ターン関連
	bool startTurn = false;
	bool your_turn = false;
	bool enemy_turn = false;
	bool easeOut = false;
	bool easeIn = false;

	//イージング用
	float t = 0;
	float dt = 0.1;
	float x0 = -200;
	float x1 = 200;
	float delay = 0;
	float d_t = 0;

	//バトルシーンのカード用
	int cardW = 256;
	int cardH = 270;
	int center = 960; // カード置き場の中心


	//色設定
	unsigned int gray = GetColor(138, 140, 142);
	unsigned int red = GetColor(255, 0, 0);
	unsigned int Silver = GetColor(192,192,192);
	unsigned int black = GetColor(0,0,0);


	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;
	
};