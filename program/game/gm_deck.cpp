#include "gm_deck.h"
#include"gm_person_manager.h"

DeckClass::DeckClass() {
	person = new PersonManager();
	person->createPerson(400, 50);
}

DeckClass::~DeckClass()
{
}
