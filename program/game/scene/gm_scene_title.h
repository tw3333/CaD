#include "../gm_manager.h"

#include "gm_scene_base.h"
#include "gm_scene_battle.h"



class SceneTitle : public SceneBase {
public:
	SceneTitle() {}
	~SceneTitle() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

private:
	
	int move = 0;
	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;

	int title_img = 0;

};
