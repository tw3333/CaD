#pragma once

class CardClass {
public:

	struct CARD {
		int No; //No
		char Name[100]; //name
		int Atta; //attack powar
		int cost; //cost
		int Card_J; //Card_Job
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
