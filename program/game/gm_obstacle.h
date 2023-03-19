#pragma once
#include "gm_unit.h"

class Obstacle : public Unit {
public:

	Obstacle(){}
	~Obstacle(){}


	//getter,setter
	int getSquareID() { return ksquare_id_; }


private:

	const int ksquare_id_ = 3;






};
