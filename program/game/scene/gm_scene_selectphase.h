#include "../gm_manager.h"
#include "gm_scene_base.h"

#include "../gm_person_manager.h"
#include "../gm_card_manager.h"


class SceneSelectPhase : public SceneBase {
public:
	SceneSelectPhase() {}
	~SceneSelectPhase(){}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	void DrawTab(int x, int y, int x2, int y2, int load);

	void LoadSelectPhaseGraph();
	void LoadDungeonCsv();

	void DrawPartyTab();

	void opTab(bool flag);
	void opTabDungeon(bool flag);
	void opTabParty(bool flag);

	void PickCheck(int pick1, int pick2, int pick3, int pick_chara);

	//remake
	//各画面の描写用関数
	void DrawDungeonWindow(bool f);
	void DrawCharaWindow(bool f);
	void DrawLibraryWindow(bool f);
	void DrawShopWindow(bool f);
	void DrawGuildWindow(bool f);

	//各画面の操作（クリックなど）の関数
	void OpDungeonWindow(bool f);
	void OpCharaWindow(bool f,int mx, int my);
	void OpLibraryWindow(bool f);
	void OpShopWindow(bool f);
	void OpGuildWindow(bool f);

	void SelectMouseWindow(int mx, int my);

	std::vector<std::vector<std::string>> dungeon;

	//PersonManager
	PersonManager* pmgr = PersonManager::GetInstance();

	//CardManager
	CardManager* cmgr = CardManager::getInstance();


private:

	int background;
	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;

	
	int select_tab = 0;
	int select_chara = 0;
	int select_dungeon = 0;
	int select_party = 0;
	int select_flame = 0;

	int dungeon_1 = 0;
	int dungeon_2 = 0;
	int dungeon_3 = 0;
	int dungeon_4 = 0;
	int dungeon_5 = 0;
	int dungeon_6 = 0;
	int dungeon_select_flame = 0;

	int flame_move = 0;
	int dun_flame_move = 0;
	int p_flame_move = 0;

	int member_img = 0;
	int x2y1_flame_B = 0;
	int x2y1_flame_1 = 0;
	int x2y1_flame_2 = 0;
	int x2y1_flame_3 = 0;

	int x2y1_flame_R = 0;

	int chara01 = 0;
	int chara02 = 0;
	int chara03 = 0;
	int chara04 = 0;

	

	int pick = 0;
	int pick_chara1 = 0;
	int pick_chara2 = 0;
	int pick_chara3 = 0;



	
	bool select_dungeon_tab;
	bool select_dungeon_tab2;

	bool select_chara_tab;
	bool select_party_tab;

	bool tab;
	bool tab2;

	bool tab_dungeon;
	bool tab_party;


	int d_csv = 0;

	//画像ハンドル用
	int s_guild_tile = 0;

	//カラーコード
	int gray = GetColor(211,211,211);
	int gray2 = GetColor(128, 128, 128);
	int dimGray = GetColor(105,105,105);
	int darkGray = GetColor(169,169,169);


	int black = GetColor(50,50,50);
	int white = GetColor(255,255,255);
	int darkGreen = GetColor(0, 100, 0);
	

	//remake
	//どのWindowが選択されているかのフラグ
	bool dungeonWindow = false;
	bool charaWindow = false;
	bool libraryWindow = false;
	bool shopWindow = false;
	bool guildWindow = false;


	int MouseX = 0;
	int MouseY = 0;

	bool tab1_cw = false;


};