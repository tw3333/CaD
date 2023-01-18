#include "gm_scene_charaedit.h"

void SceneCharaEdit::initialzie() {
	LoadCharaEditGraph();
}

void SceneCharaEdit::update(float delta_time) {

}

void SceneCharaEdit::render() {
	//静的グラフィック
	DrawExtendGraph(0, 0, width1 * 2, height1 * 1, chara_tile, false);
	
	
	//アタリ線
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}
}

//ここから関数

void SceneCharaEdit::LoadCharaEditGraph() {
	chara_tile = LoadGraph("graphics/s_chara_tile.png");
}