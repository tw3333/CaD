#pragma once
#include <vector>
#include "gm_unit.h"

//!!!シングルトンではない

class TurnManager {
public:

	TurnManager(std::vector<Unit*> allUnit){};
	~TurnManager(){}

	void DecideOrderUnit(
	);



private:


};