#include "gm_card_manager.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

CardManager* CardManager::instance_ = nullptr;


void CardManager::LoadCardDate() {
	
	//Card* card1 = new Card(1, "ê‘", "éaÇÈ", 1, 2, 0, 0, 0, 0, 0, 0, false);

	std::ifstream file("date/card.csv");

    if (!file.is_open()) {
        std::cerr << "failed to open " << "date/card.csv" << std::endl;
        return;
    }

    std::string line;
    
    getline(file, line); //ç≈èâÇÃàÍçsîÚÇŒÇ∑

	while (getline(file, line)) {
		std::istringstream linestream(line);
		std::string value;

		std::vector<std::string> values;
		while (getline(linestream, value, ',')) {
			values.push_back(value);
		}

		int id = stoi(values[0]);
		std::string job = values[1];
		std::string name = values[2];
		int cost = stoi(values[3]);
		int damage = stoi(values[4]);
		int protection = stoi(values[5]);
		int weak = stoi(values[6]);
		int slow = stoi(values[7]);
		int heal = stoi(values[8]);
		int hate = stoi(values[9]);
		int addcost = stoi(values[10]);
		
		bool effect = (values[11] == "TRUE");
		int graph = stoi(values[12]);


		cardDate.push_back(new Card(id, job, name, cost, damage, protection, weak, slow, heal, hate, addcost, effect,graph));

	}

	file.close();

}


//void CardManager::LoadCardGraph() {
//	
//	
//	for (int i = 0; i < 15; i++) {
//
//		switch (i)
//		{
//			case 0: cardDate[0]->c_graph = LoadGraph("graphics/card_1.png");
//			case 1: cardDate[1]->c_graph = LoadGraph("graphics/card_2.png");
//			case 2: cardDate[2]->c_graph = LoadGraph("graphics/card_3.png");
//			case 3: cardDate[3]->c_graph = LoadGraph("graphics/card_4.png");
//			case 4: cardDate[4]->c_graph = LoadGraph("graphics/card_5.png");
//			case 5: cardDate[5]->c_graph = LoadGraph("graphics/card_6.png");
//			case 6: cardDate[6]->c_graph = LoadGraph("graphics/card_7.png");
//			case 7: cardDate[7]->c_graph = LoadGraph("graphics/card_8.png");
//			case 8: cardDate[8]->c_graph = LoadGraph("graphics/card_9.png");
//			case 9: cardDate[9]->c_graph = LoadGraph("graphics/card_10.png");
//
//			case 10: cardDate[10]->c_graph = LoadGraph("graphics/card_11.png");
//			case 11: cardDate[11]->c_graph = LoadGraph("graphics/card_12.png");
//			case 12: cardDate[12]->c_graph = LoadGraph("graphics/card_13.png");
//			case 13: cardDate[13]->c_graph = LoadGraph("graphics/card_14.png");
//			case 14: cardDate[14]->c_graph = LoadGraph("graphics/card_15.png");		
//		}
//	}
//}








