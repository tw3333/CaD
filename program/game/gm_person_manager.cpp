#include "gm_person_manager.h"

//ƒVƒ“ƒOƒ‹ƒgƒ“ŽÀ‘•‚Ì‚½‚ß‚Ìnullptr
PersonManager* PersonManager::instance_ = nullptr;

void PersonManager::AddPersonPointerToVector() {

	//person.push_back(person1);
	//person.push_back(person2);
	//person.push_back(person3);
	//person.push_back(person4);

	person.push_back(new Person(10, 10, 3, 3, 9, false, false, 0));
}

void PersonManager::LoadPersonGraph() {

	person[0]->GRAPH = LoadGraph("graphics/chara1_face.png"); 





	//for (int i = 0; i < person.size(); i++) {

	//	switch (i)	{
	//		
	//		case0:person[0]->GRAPH = LoadGraph("graphics/chara1_face.png"); break;
	//		case1:person[1]->GRAPH = LoadGraph("graphics/chara2_face.png"); break;
	//		case2:person[2]->GRAPH = LoadGraph("graphics/chara3_face.png"); break;
	//		case3:person[3]->GRAPH = LoadGraph("graphics/chara4_face.png"); break;
	//		case4:person[4]->GRAPH = LoadGraph("graphics/chara1_face.png"); break;

	//	}

	//}

}
	



