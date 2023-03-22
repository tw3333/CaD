#pragma once
#include "gm_ally.h"


class Ally;


class AllyManager {
public:

	AllyManager() {}

	~AllyManager() {

		for (auto ally : allies_) { delete ally; }
		delete instance_;

	}

	static AllyManager* GetInstance() {
		if (!instance_) { instance_ = new AllyManager(); }
		return instance_;
	}

	std::vector<Ally*> allies_;




	//ƒƒ“ƒoŠÖ”ŒQ

private:

	static AllyManager* instance_;

};
