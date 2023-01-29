#include "gm_card.h"
#include <fstream>
#include <sstream>
#include <vector>

//ÉJÅ[ÉhÇÃâÊëúÇì«Ç›çûÇ›/éÊìæÇ∑ÇÈä÷êî
//arg1...cardNoÇì¸óÕ
void Card::SetCardGraph(int i) {
	
	switch (i)
	{
		case1: cardGraph = LoadGraph("graphics/card_1.png"); break;
		case2: cardGraph = LoadGraph("graphics/card_2.png"); break;
		case3: cardGraph = LoadGraph("graphics/card_3.png"); break;
		case4: cardGraph = LoadGraph("graphics/card_4.png"); break;
		case5: cardGraph = LoadGraph("graphics/card_5.png"); break;
		case6: cardGraph = LoadGraph("graphics/card_6.png"); break;
		case7: cardGraph = LoadGraph("graphics/card_7.png"); break;
		case8: cardGraph = LoadGraph("graphics/card_8.png"); break;
		case9: cardGraph = LoadGraph("graphics/card_9.png"); break;
		case10: cardGraph = LoadGraph("graphics/card_10.png"); break;
		case11: cardGraph = LoadGraph("graphics/card_11.png"); break;
		case12: cardGraph = LoadGraph("graphics/card_12.png"); break;
		case13: cardGraph = LoadGraph("graphics/card_13.png"); break;
		case14: cardGraph = LoadGraph("graphics/card_14.png"); break;
		case15: cardGraph = LoadGraph("graphics/card_15.png"); break;

		default: cardGraph = LoadGraph("graphics/card_chara1_flame.png"); break;
	}


}


 std::vector<Card> Card::ReadCardsFromCSV(const char* filename) {
     std::vector<Card> cards;
     std::ifstream file(filename);
     std::string line;
     while (std::getline(file, line)) {
         std::stringstream lineStream(line);
         std::string cell;
         Card card;
         std::getline(lineStream, cell, ',');
         card.c_number = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         strcpy(card.cardJob, cell.c_str());
         std::getline(lineStream, cell, ',');
         strcpy(card.Name, cell.c_str());
         std::getline(lineStream, cell, ',');
         card.c_cost = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_damage = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_protec = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_weak = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_slow = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_heal = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_hate = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_addcost = std::stoi(cell);
         std::getline(lineStream, cell, ',');
         card.c_effect = (cell == "TRUE");
         cards.push_back(card);
     }
     return cards;
}




