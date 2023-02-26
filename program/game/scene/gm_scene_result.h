#include "gm_scene_base.h"
#include "../gm_manager.h"

#include "../gm_person_manager.h"

class SceneResult : public SceneBase {
public:
	SceneResult() {}
	~SceneResult() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	PersonManager* pmgr = PersonManager::GetInstance();

	std::vector<Person*> party;

private:

	int expAnimCount = 0;
	int expAnimCountMax = 0;


	int beforExp[3];
	int beforExpMax[3];

	int width1 = DXE_WINDOW_WIDTH / 10;
	int height1 = DXE_WINDOW_HEIGHT / 10;

	//カラーコード
	int red = GetColor(255,0,0);
	int white = GetColor(255,255,255);

};
