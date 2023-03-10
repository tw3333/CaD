#include "../gm_manager.h"
#include "gm_scene_base.h"

#include "../gm_person.h"
#include "../gm_person_manager.h"

#include "../gm_card_manager.h"

#include "../gm_enemy.h"

#include "../gm_sound_manager.h"



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

	//バトルシーン用
	void BattleStart();
	void BattleCol();
	void BattleDraw();

	//関数群
	void DrawTurn();
	void RaiseCard(std::vector<Card*> hand, int x, int y);
	void DrawHand(std::vector<Card*> &hand);
	void EaseTurnImage(double out_t, double in_t, int x_s, int x_e);
	void EaseImageCard1(double t, int x_s, int x_e, int delay);
	void DrawHpBar(int hp_now, int hp_max); //HPバーの描写
	
	void DealFromDeckToHand(const std::vector<Card*>& deck, std::vector<Card*>& hand,int handNum);

	void DrawOrder();

	void Debug();

	void useCard(Card* &card,Person* person,std::vector<Person*> &party, std::vector<Enemy*> &enemies);

	void ChangeFlagByclickOnRange(int x, int y, int x2, int y2, bool f, int mouseX, int mouseY);

	//remake
	void SetParty(std::vector<Person*>& person, std::vector<Person*>& party);

	
	
	void UseCardFromHand(Person* party,std::vector<Card*>& hand,int x, int y);

	void SetEmemyPick();
	void ReflectOrderImage();

	std::vector<void*> GetTurnOrder(const std::vector<Person*>& party, const std::vector<Enemy*>& enemies);

	void DecideOrderUnit(std::vector<Unit*>& unit);


	//イージング関数
	double easeInExpo(double t);
	double easeOutExpo(double t);

	//PersonManager
	PersonManager* pmgr = PersonManager::GetInstance();
	//int& hp_max = pmgr->person[0]->HPMAX;
	//int& hp_now = pmgr->person[0]->HP;

	//CardManager
	CardManager* cmgr = CardManager::GetInstance();

	SoundManager* smgr = SoundManager::GetInstance();



	int test = 30;
private:
	
	//デッキ(山札)からへ手札へ
	//各キャラの手札用配列
	std::vector<Card*> chara1Hand;
	std::vector<Card*> chara2Hand; //未実装
	std::vector<Card*> chara3Hand;
	std::vector<Card*> chara4Hand;

	//単に一時的な手札
	//std::vector<Card*> hand;
	Person* doPerson = nullptr;
	Enemy* doEnemy = nullptr;
	

//	std::unique_ptr<Person> doPerson;

	//SceneBattleで戦う各キャラと敵を一時的に配列に格納して使う
	std::vector<Person*> party;
	std::vector<Enemy*> enemies;

	//SceneBattleでキャストしたPersonの持つ、deck,handを配列に戻す用
	std::vector<Card*> b_deck;
	std::vector<Card*> b_hand;


	std::vector<Unit*> allUnit;

	Enemy* enemy1 = new Enemy("敵１", 100, 100, 5, 5, 0, 0);




	bool dealHand = false;

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

	//Order関連
	int order1thImage = 0;
	int order2thImage = 0;
	int order3thImage = 0;
	int order4thImage = 0;
	int order5thImage = 0;


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

	int cost_max = 3;
	int cost_now = 0;
	int Bar_Width = 300;
	int Bar = 0;
	//	int test = 0;

	//各キャラがピックされているか
	bool pick_chara1 = false;
	bool pick_chara2 = false;
	bool pick_chara3 = false;
	bool pick_chara4 = false;

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

	//戦闘の際使うフラグ
	bool isTakeCard = false;
	bool isDealCard = false;
	bool dealCard = false; //trueでカードをdealする
	bool turnEnd = false; //trueでターンを終了
	int turnCount = 0;
	bool nextTurn = false;
	bool isDecideOrdered = false; //順番を決めたかどうか

	int dealCardNum = 5; //5枚がデフォルト

	bool isBattle = false;
	bool isturnEnd = false;

	bool isTurnStart = false;

	bool isPhaseStart = false;
	bool isPhaseEnd = false;
	bool actionPhase = false;

	int phaseCount = 0; //1ターンのフェイズの経過用

	bool decideOrder = false;

	bool dealCardPhase = false;
	bool decideOrderPhase = false;
	bool turnEndPhase = false;

	int orderCount = 0;

	bool decideNextOrder = false;

	bool isClickTurnEnd = false;

	bool costReset = false;
	//bool decideOrderPhase = false;
	//bool dealCardPhase = false;

	//ターンのファイズ管理用enum
	//enum TurnPhase {

	//	decideOrderPhase,
	//	dealCardPhase,
	//	battlePhase,
	//	endPhase,

	//};

	/*TurnPhase phase;*/


	//色設定
	unsigned int gray = GetColor(138, 140, 142);
	unsigned int red = GetColor(255, 0, 0);
	unsigned int Silver = GetColor(192,192,192);
	unsigned int black = GetColor(0,0,0);


	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;
	
};