#include <time.h>
#include "gm_main.h"
#include "gm_manager.h"
#include "../game/gm_person_manager.h"
#include "../game/gm_card_manager.h"



void gameMain(float delta_time) {

	GameManager* mgr = GameManager::GetInstance();
	mgr->update(delta_time);
}

void gameEnd() {
}
