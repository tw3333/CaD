#pragma once
#include "gm_person.h"
#include "gm_enemy.h"
#include <vector>


class Person;

//シングルトン設計
class PersonManager {
public:

	//Person(chara)のインスタンス生成
	//Person* person1 = new Person(30, 30, 3, 3, 10, false, false,0); //chara1
	//Person* person2 = new Person(10, 10, 3, 3, 9, false, false,0); //chara2
	//Person* person3 = new Person(40, 40, 3, 3, 8, false, false,0); //chara3
	//Person* person4 = new Person(20, 20, 3, 3, 5, false, false,0); //chara4

	//Personを格納する配列、添え字がID代わり
	std::vector<Person*> person;

	void AddPersonPointerToVector();
	void LoadPersonGraph();


	static PersonManager* GetInstance() {
		if (!instance_) {
			instance_ = new PersonManager();
		}
		return instance_;
	}



private:

	static PersonManager* instance_;

	//コンストラクタ
	PersonManager() {
	}




};