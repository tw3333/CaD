#pragma once
#include "../gm_manager.h"
#include "gm_scene_base.h"

#include "../gm_person_manager.h"
#include "../gm_card_manager.h"
#include "../gm_sound_manager.h"

class SceneLoad : public SceneBase  {
public:

	SceneLoad(){}
//	~SceneBase();

	void initialzie() override;
	void update(float dalta_time) override;
	void render() override;

	PersonManager* pmgr = PersonManager::GetInstance();

	CardManager* cmgr = CardManager::GetInstance();
	
	SoundManager* smgr = new SoundManager();

};