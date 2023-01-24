#pragma once
#include "gm_card.h"
#include <vector>

class Card;
class PersonManager;

class DeckClass {
	DeckClass(){}
	~DeckClass();
	char JobName[20] = "\0"; //job–¼
	std::vector<Card> DeckCardList;

	int DeckSeet = 0;
	int Deck_Same_Card = 0;
	int maxCardList = 0;
	PersonManager* person;
	int same = 0;
public:

private:

};