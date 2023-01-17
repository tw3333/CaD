#pragma once

class CardClass {
public:

	struct CARD {
		int No; //No
		char Name[100]; //name
		int c_damage; //attack powar
		int c_block;
		int c_week;
		int c_heal;
		int c_cure;
		int c_slow;
		int c_hate;
		int c_cost;


		bool turn_next;

		int cost;//cost
		int attribute; //ƒJ[ƒh‚Ì‘®«
	};

	struct PLACE {
		int Num;
		//CARD Card[DECK_TOTAL];
	};

	enum e_Card_Job {
		Card_type_a,
		Card_type_b,
		Card_type_c,

	};

	CARD Card[15] = {
		{0,"—U“±",1,1,e_Card_Job::Card_type_a} ,				
		{1,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{2,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{3,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{4,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{5,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{6,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{7,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{8,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{9,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{10,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{11,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{12,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{13,"—U“±",1,1,e_Card_Job::Card_type_a} ,
		{14,"—U“±",1,1,e_Card_Job::Card_type_a} ,
	};


private:
	
};
