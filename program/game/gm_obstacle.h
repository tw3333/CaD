#pragma once
#include "gm_unit.h"
#include "gm_square.h"

class Obstacle : public Unit {
public:

	Obstacle(){}
	~Obstacle(){}


	//getter,setter
	int getSquareID() { return ksquare_id_; }


private:

	const int ksquare_id_ = 3;

	Square::SquareType square_type_ = Square::SquareType::kObstacle;





};
