#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"
#include "gm_scene_selectphase.h"

void SceneResult::initialzie() {

	for (int i = 0; i < pmgr->person.size(); i++) {

		if (pmgr->person[i]->PICK == true) {

			party.emplace_back(pmgr->person[i]);

		}

	}

	//for (int i = 0; party.size(); i++) {

	//	beforExp[i] = party[i]->EXP;
	//	beforExpMax[i] = party[i]->NEEDEXP;
	//}

	

}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	expAnimCount += 1;

	//for (int i = 0; i < party.size(); i++) {

	//	expAnimCountMax = party[i]


	//}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneTitle());
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_U)) {
		mgr->chengeScene(new SceneSelectPhase());
	}

	//ÉAÉ^Éäê¸
	for (int i = 0; i < 10; ++i) {
		DrawLine(0, height1 + height1 * i, DXE_WINDOW_WIDTH, height1 + height1 * i, 0);
		DrawLine(width1 + width1 * i, 0, width1 + width1 * i, DXE_WINDOW_HEIGHT, 0);
	}


}

void SceneResult::render()
{
	DrawStringEx(50, 50, -1, "scene result");

	//DrawBox(0,0,1600,900,0,true);

	for (int i = 0; i < party.size(); i++) {

		DrawExtendGraph(width1 * 1, height1 * (1 + i * 3), width1 * 3, height1 * (2 + i * 3), party[i]->GRAPH, false); //
		
		//hp 
		DrawStringEx(width1 * 3 + 10, height1 * (1 + i * 3), -1, "HP:%d/%d", party[i]->HP, party[i]->HPMAX);

		if (party[i]->HP / party[i]->HPMAX != 0) {

			DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 15, (width1 * 5 - 10) * (party[i]->HP / party[i]->HPMAX), height1 * (1 + i * 3) + 25, red, true);

		}
		//DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 15, (width1 * 5 - 10) * (party[i]->HP / party[i]->HPMAX), height1 * (1 + i * 3) + 25, red, true);
		DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 15, width1 * 5 - 10, height1 * (1 + i * 3) + 25, white, false);

		//DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 15, (width1 * 5 - 10) * (party[i]->HP / party[i]->HPMAX), height1 * (1 + i * 3) + 25, red, true);


		//exp
		DrawStringEx(width1 * 3 + 10, height1 * (1 + i * 3) + 30, -1, "EXP:%d/%d", party[i]->EXP, party[i]->NEEDEXP);
		
		if (party[i]->EXP / party[i]->NEEDEXP != 0) {
			DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 45, width1 * 5 - 10 * (party[i]->EXP / party[i]->NEEDEXP), height1 * (1 + i * 3) + 55, red, true);

//			DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 45, (width1 * 5 - 10) * (party[i]->EXP / party[i]->NEEDEXP), height1 * (1 + i * 3) + 55, red, true);
		}
		//DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 45, (width1 * 5 - 10) * (party[i]->EXP / party[i]->NEEDEXP), height1 * (1 + i * 3) + 55, red, true);
		DrawBox(width1 * 3 + 10, height1 * (1 + i * 3) + 45, width1 * 5 - 10, height1 * (1 + i * 3) + 55, white, false);

	}


	//for (int i = 0; i < party.size(); i++) {

	//	//DrawBox(width1*2 + 10, height1*1,-1,false);

	//}
}
