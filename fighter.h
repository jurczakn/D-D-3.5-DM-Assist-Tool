/*	Author: Nick Jurczak
Date: 12/1/2014
Name: fighter
Purpose: Contains definition of
Fighter player class, child of
Character class.
*/

#ifndef FIGHTER_H
#define FIGHTER_H

#include "character.h"
#include "ddUtilities.h"
#include <string>
#include <vector>

using DD::armor;
using DD::weapon;
using DD::item;
using DD::skill;
using std::string;
using std::vector;
using std::ostream;

//---------------------------------------------------------------------------------
//Requirement #16: Demonstrate one class
//---------------------------------------------------------------------------------
class Fighter : public Character{

public:

	//---------------------------------------------------------------------------------
	//Requirement #24: Demonstrate polymorhism
	//---------------------------------------------------------------------------------
	virtual string getClass(){

		return "Fighter";

	}

	Fighter():Character(){}

	Fighter(const Fighter&);

	Fighter(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin);

	Fighter(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin, int abil[6], int hp, int speed, int bAB, vector<weapon> w, vector<armor> ar, vector<item> items, vector<skill> skills, int iM, int bst[3])
		: Character(n, r, a, d, l, s, age, gender, ht, e, h, skin, abil, hp, speed, bAB, w, ar, items, skills, iM, bst){}

	~Fighter(){

		delete[] baseSaveThrows;

	}

	//virtual void save(fstream&);

};

#endif//FIGHTER_H