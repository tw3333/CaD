#include "gm_person.h"


void Person::AddExp(int exp) {

	EXP += exp;

	while(EXP >= NEEDEXP) {
		
		LEVEL += 1;
		EXP -= NEEDEXP;
		NEEDEXP = static_cast<int>(NEEDEXP * 1.2);

	}


}