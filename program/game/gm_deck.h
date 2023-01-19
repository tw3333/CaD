#pragma once
#include "gm_card.h"

class DeckClass {
	char JobName[20] = "\0"; //job名
	CardClass DeckCardList[10] = { }; // カードリスト(10枚)

	int DeckSeet = 0;
	int Deck_Same_Card = 0;

	int same = 0;
public:

private:

};