#include <time.h>
#include "gm_main.h"
#include "gm_manager.h"
#include "../game/gm_person_manager.h"
#include "../game/gm_card_manager.h"



void gameMain(float delta_time) {
	PersonManager* pmgr = PersonManager::GetInstance();
	pmgr->AddPersonPointerToVector(); //Personのインスタンスをvector型の配列に格納

	CardManager* cmgr = CardManager::GetInstance();
	cmgr->LoadCardDate(); //全てのカードデータをロード
	cmgr->LoadCardGraph(); //全てのカードデータに画像をロード
	cmgr->SortJobCard(); //職業ごとにカードを振り分け


	GameManager* mgr = GameManager::GetInstance();
	mgr->update(delta_time);
}

void gameEnd() {
}
