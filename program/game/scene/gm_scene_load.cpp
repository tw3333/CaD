
#include "gm_scene_load.h"
#include "gm_scene_selectphase.h"

void SceneLoad::initialzie() {
	//Sound�f�[�^�̃��[�h
	smgr->LoadSoundSe();

	//Person�f�[�^�̃��[�h
	pmgr->AddPersonPointerToVector();
	pmgr->LoadPersonGraph();

	//Card�f�[�^�̃��[�h
	cmgr->LoadCardDate();
	cmgr->LoadCardGraph();
	cmgr->SortJobCard();

}

void SceneLoad::update(float delta_time) {
	GameManager* gmgr = GameManager::GetInstance();


	for (int i = 0; i < pmgr->person.size(); i++) {

		if (pmgr->person[i] != nullptr) {

			for (int k = 0; k < pmgr->person[i]->cardList.size(); k++) {

				if (pmgr->person[i]->cardList[k] != nullptr) {

					gmgr->chengeScene(new SceneSelectPhase);



				}



			}

		}



	}






}

void SceneLoad::render() {







}


