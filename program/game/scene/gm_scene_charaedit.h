#include "../gm_manager.h"
#include "gm_scene_base.h"

#include "../gm_person_manager.h"
#include "../gm_card_manager.h"






class SceneCharaEdit : public SceneBase {
public:
	SceneCharaEdit() {}
	~SceneCharaEdit() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;


	void LoadCharaEditGraph();
	void FlameMove(bool f);

	void DrawDeckTab(bool f);

	int p1HP = 0;

	void DrawCharaStatus();
	
	PersonManager* pmgr = PersonManager::getInstance();
	CardManager* cmgr = CardManager::getInstance();
	

	
	
	
private:
	int width1 = DXE_WINDOW_WIDTH / 10;
	int height1 = DXE_WINDOW_HEIGHT / 10;

	//�L�����֘A



	//�t���[���������p
	int f_trans = 0;

	//�摜�p�n���h��
	int select_flame = 0;
	int s_chara_tile = 0;
	int chara_tile = 0;
	int deck_tile = 0;
	int equip_tile = 0;

	//�t���O�ݒ�
	bool deckTab = false;
	bool flame = false;
	bool img_frash = false;

	//�J���[�R�[�h
	int gray = GetColor(128, 128, 128);
	int dsgray = GetColor(47, 79, 79); //darkslategray

};