/*	Author: Nick Jurczak
Date: 12/1/2014
Name: barbarian
Purpose: Contains definition of
Barbarian player class, child of
Character class.
*/

#ifndef BARBARIAN_H
#define BARBARIAN_H

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

class Barbarian : public Character{

public:

	virtual string getClass(){

		return "Barbarian";

	}

	Barbarian(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin);

	Barbarian(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin, int abil[6], int hp, int speed, int bAB, vector<weapon> w, vector<armor> ar, vector<item> items, vector<skill> skills, int iM, int bst[3])
		: Character(n, r, a, d, l, s, age, gender, ht, e, h, skin, abil, hp, speed, bAB, w, ar, items, skills, iM, bst){}
};

#endif//BARBARIAN_H