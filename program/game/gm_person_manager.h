#pragma once
#include "gm_person.h"
#include <vector>



class PersonManager {
public:
	
	Person* createPerson(int HP, int COST) {
		Person* newPerson = new Person(HP, COST);
		personList.push_back(newPerson);
		return newPerson;
	}

	Person* getPerson(int index) {
		return personList[index];
	}

	void deletePerson(int index){
		delete personList[index];
		personList.erase(personList.begin() + index);
	}

	void getPersonAll();

private:
	
	std::vector<Person*> personList;
	
};