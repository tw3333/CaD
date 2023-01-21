#pragma once
#include "gm_person.h"



class PersonManager {
public:
	
	PersonManager();
	~PersonManager();

	Person* person1 = new Person(40, 3);
	Person* person2 = new Person(40, 3);
	Person* person3 = new Person(40, 3);
	Person* person4 = new Person(40, 3);
	
	static PersonManager pgmr;

	

private:


};