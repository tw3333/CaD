#pragma once
#include "gm_person.h"
#include <vector>

//インスタンスを共有したい

class Person;

//シングルトン設計
class PersonManager {
public:
	
	Person* person1 = new Person(30, 30, 3, 3, 10); //chara1
	Person* person2 = new Person(10, 10, 3, 3, 9); //chara2
	Person* person3 = new Person(40, 40, 3, 3, 8); //chara3
	Person* person4 = new Person(20, 20, 3, 3, 5); //chara4


	static PersonManager* getInstance() {
		if (!instance_) {
			instance_ = new PersonManager();
		}
		return instance_;
	}

private:

	static PersonManager* instance_;
	
	//コンストラクタ
	PersonManager(){
	}
	
	
};