#pragma once
#include "../gm_manager.h"
#include "gm_scene_base.h"

class SceneCharaEdit : public SceneBase {
public:
	SceneCharaEdit() {}
	~SceneCharaEdit() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	
	void LoadCharaEditGraph();

private:
	int width1 = DXE_WINDOW_WIDTH / 10;
	int height1 = DXE_WINDOW_HEIGHT / 10;

	//‰æ‘œ—pƒnƒ“ƒhƒ‹
	int chara_tile = 0;

};