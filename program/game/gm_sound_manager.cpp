#include "gm_sound_manager.h"
#include "DxLib.h"


SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::LoadSoundSe() {

	useCard_se = LoadSoundMem("sound/usecard_se.mp3");
	dealCard_se = LoadSoundMem("sound/dealcard_se.mp3");


}