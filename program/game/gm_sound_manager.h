#pragma once


//�V���O���g���݌v

class SoundManager {
public:
	SoundManager(){}
	~SoundManager(){}

	void LoadSoundSe();
	
	static SoundManager* GetInstance() {
		if (!instance_) {
			instance_ = new SoundManager();
		}

		return instance_;

	}

	int useCard_se;
	int dealCard_se;

private:

	static SoundManager* instance_;



};
