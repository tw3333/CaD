#include "gm_person_manager.h"

//シングルトン実装のためのnullptr
PersonManager* PersonManager::instance_ = nullptr;

void PersonManager::AddPersonPointerToVector() {

	person.push_back(person1);
	person.push_back(person2);
	person.push_back(person3);
	person.push_back(person4);

}
	



