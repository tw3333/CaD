#pragma once
#include "gm_person.h"
#include <vector>


class Person;

//�V���O���g���݌v
class PersonManager {
public:

	Person* person1 = new Person(30, 30, 3, 3, 10, false); //chara1
	Person* person2 = new Person(10, 10, 3, 3, 9, false); //chara2
	Person* person3 = new Person(40, 40, 3, 3, 8, false); //chara3
	Person* person4 = new Person(20, 20, 3, 3, 5, false); //chara4




	static PersonManager* GetInstance() {
		if (!instance_) {
			instance_ = new PersonManager();
		}
		return instance_;
	}

private:

	static PersonManager* instance_;

	//�R���X�g���N�^
	PersonManager() {
	}




};