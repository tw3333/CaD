#include "gm_card.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


//std::ifstream file("date/cards.csv");
//std::string line;


//void Card::LoadCardDate() {
//	
//	while (getline(file, line)) {
//		std::istringstream linestream(line);
//		std::string value;
//
//		std::vector<std::string> values;
//		while (getline(linestream, value, ',')) {
//			values.push_back(value);
//		}
//
//		int id = stoi(values[0]);
//		std::string job = values[1];
//		std::string name = values[2];
//		int cost = stoi(values[3]);
//		int damage = stoi(values[4]);
//		int protection = stoi(values[5]);
//		int weak = stoi(values[6]);
//		int slow = stoi(values[7]);
//		int heal = stoi(values[8]);
//		int hate = stoi(values[9]);
//		int addcost = stoi(values[10]);
//		bool effect = (values[11] == "TRUE");
//
//		Card card(id, job, name, cost, damage, protection, weak, slow, heal, hate, addcost, effect);
//		cards.push_back(card);
//	}
//
//
//	file.close();
//
//}





//カードの画像を読み込み/取得する関数
//arg1...cardNoを入力
//void Card::SetCardGraph(int i) {
//	
//	switch (i)
//	{
//		case1: cardGraph = LoadGraph("graphics/card_1.png"); break;
//		case2: cardGraph = LoadGraph("graphics/card_2.png"); break;
//		case3: cardGraph = LoadGraph("graphics/card_3.png"); break;
//		case4: cardGraph = LoadGraph("graphics/card_4.png"); break;
//		case5: cardGraph = LoadGraph("graphics/card_5.png"); break;
//		case6: cardGraph = LoadGraph("graphics/card_6.png"); break;
//		case7: cardGraph = LoadGraph("graphics/card_7.png"); break;
//		case8: cardGraph = LoadGraph("graphics/card_8.png"); break;
//		case9: cardGraph = LoadGraph("graphics/card_9.png"); break;
//		case10: cardGraph = LoadGraph("graphics/card_10.png"); break;
//		case11: cardGraph = LoadGraph("graphics/card_11.png"); break;
//		case12: cardGraph = LoadGraph("graphics/card_12.png"); break;
//		case13: cardGraph = LoadGraph("graphics/card_13.png"); break;
//		case14: cardGraph = LoadGraph("graphics/card_14.png"); break;
//		case15: cardGraph = LoadGraph("graphics/card_15.png"); break;
//
//		default: cardGraph = LoadGraph("graphics/card_chara1_flame.png"); break;
//	}
//
//
//}


// std::vector<Card> Card::CreateCardsFromCSV(const char* filename) {
//     
//     std::vector<Card> cards;
//     std::ifstream file(filename);
//
//	 if(!file.good()) { return cards;}
//
//	 std::string line;
//	 getline(file, line); //最初の一行飛ばす
//    
//	 while (getline(file, line)) {
//		 std::istringstream linestream(line);
//		 std::string value;
//
//		 std::vector<std::string> values;
//		 while (getline(linestream, value, ',')) {
//			 values.push_back(value);
//		 }
//
//		 int id = stoi(values[0]);
//		 std::string job = values[1];
//		 std::string name = values[2];
//		 int cost = stoi(values[3]);
//		 int damage = stoi(values[4]);
//		 int protection = stoi(values[5]);
//		 int weak = stoi(values[6]);
//		 int slow = stoi(values[7]);
//		 int heal = stoi(values[8]);
//		 int hate = stoi(values[9]);
//		 int addcost = stoi(values[10]);
//		 bool effect = (values[11] == "TRUE");
//
//		 Card card(id, job, name, cost, damage, protection, weak, slow, heal, hate, addcost, effect);
//		 cards.push_back(card);
//
//	 }
//
//	 return cards;
//	 file.close();
//}




