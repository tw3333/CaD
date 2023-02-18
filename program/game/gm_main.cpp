#include <time.h>
#include "gm_main.h"
#include "gm_manager.h"
#include "../game/gm_person_manager.h"
#include "../game/gm_card_manager.h"



void gameMain(float delta_time) {
	PersonManager* pmgr = PersonManager::GetInstance();
	pmgr->AddPersonPointerToVector(); //Person�̃C���X�^���X��vector�^�̔z��Ɋi�[

	CardManager* cmgr = CardManager::GetInstance();
	cmgr->LoadCardDate(); //�S�ẴJ�[�h�f�[�^�����[�h
	cmgr->LoadCardGraph(); //�S�ẴJ�[�h�f�[�^�ɉ摜�����[�h
	cmgr->SortJobCard(); //�E�Ƃ��ƂɃJ�[�h��U�蕪��


	GameManager* mgr = GameManager::GetInstance();
	mgr->update(delta_time);
}

void gameEnd() {
}
