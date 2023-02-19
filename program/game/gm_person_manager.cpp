#include "gm_person_manager.h"

//ƒVƒ“ƒOƒ‹ƒgƒ“ŽÀ‘•‚Ì‚½‚ß‚Ìnullptr
PersonManager* PersonManager::instance_ = nullptr;

void PersonManager::AddPersonPointerToVector() {

	//person.push_back(person1);
	//person.push_back(person2);
	//person.push_back(person3);
	//person.push_back(person4);

	//Person* person1 = new Person(30, 30, 3, 3, 10, false, false, 0); //chara1
	//Person* person2 = new Person(10, 10, 3, 3, 9, false, false, 0); //chara2
	//Person* person3 = new Person(40, 40, 3, 3, 8, false, false, 0); //chara3
	//Person* person4 = new Person(20, 20, 3, 3, 5, false, false, 0); //chara4

	person.push_back(new Person(30, 30, 3, 3, 10, false, false, 0)); //chara1
	person.push_back(new Person(10, 10, 3, 3, 9, false, false, 0)); //chara2
	person.push_back(new Person(40, 40, 3, 3, 8, false, false, 0)); //chara3
	person.push_back(new Person(20, 20, 3, 3, 5, false, false, 0)); //chara4


}


//TODO:‚È‚º‚©for•¶‚Å‰æ‘œ‚ª“Ç‚Ýž‚Ü‚ê‚Ä‚­‚ê‚È‚¢
void PersonManager::LoadPersonGraph() {

	person[0]->GRAPH = LoadGraph("graphics/chara1_face.png"); 
	person[1]->GRAPH = LoadGraph("graphics/chara2_face.png"); 
	person[2]->GRAPH = LoadGraph("graphics/chara3_face.png"); 
	person[3]->GRAPH = LoadGraph("graphics/chara4_face.png"); 


	//for (int i = 0; i < person.size(); i++) {

	//	switch (i)	{
	//		
	//		case0:person[0]->GRAPH = LoadGraph("graphics/chara1_face.png"); break;
	//		case1:person[1]->GRAPH = LoadGraph("graphics/chara2_face.png"); break;
	//		case2:person[2]->GRAPH = LoadGraph("graphics/chara3_face.png"); break;
	//		case3:person[3]->GRAPH = LoadGraph("graphics/chara4_face.png"); break;

	//	}

	//}

}
	



