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









