/*	Author: Nick Jurczak
Date: 12/1/2014
Name: ddUtilites
Purpose: Contains the definitions of several structs, 
including item, weapon, and armor, useful to the 
d&d 3.5 dm assist tool as well as functions
related to their use.  All functions and 
structs are contained in the DD namespace.
*/

#ifndef DDUTILITIES_H
#define DDUTILITIES_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "inputValidation.h"

using inv::getDouble;
using inv::getInt;
using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::ostream;
using std::endl;
using std::setw;
using std::left;
using std::to_string;
using std::vector;

//---------------------------------------------------------------------------------
//Requirement #18: Demonstrate custom namespace
//---------------------------------------------------------------------------------
namespace DD{

	//---------------------------------------------------------------------------------
	//Requirement #16: Demonstrate one struct
	//---------------------------------------------------------------------------------
	struct weapon{

		string name;

		string damage;

		bool ranged;

		int attackBonus;

		int critRange[3];

		int crit;

		int range;

		string type;

		double weight;

		string notes;

		int ammo;
	};

	ostream& operator<<(ostream &out, weapon w);

	struct armor{

		string name;

		string type;

		int armorBonus;

		int maxDexBonus;

		int checkPenalty;

		double weight;

		int speedPen20;

		int speedPen30;

		string specProp;
	};

	ostream& operator<<(ostream &out, armor a);

	struct item{

		string name;

		int amount;

		double weight;
	};

	ostream& operator<<(ostream &out, item i);

	struct skill{

		string name;

		int ranks;

		int abilMod;

		int checkPenalty;

	};

	ostream& operator<<(ostream &out, skill s);

	void printWeapon(weapon w);

	void printArmor(armor a);


	template <class T>
	void structSelect(vector<T> v){//display options when selecting stuct obj from vector

		for (int i = 0; i < v.size(); i++){//print objects in two columns

			cout << i << ": " << setw(20) << left << v.at(i++);

			if (i < v.size())//check not past last element

				cout << i + 1 << ": " << setw(20) << left << v.at(i);

			cout << endl;
		}
	}

	void structSelect(vector<int> v);

	weapon createWeapon();

	armor createArmor();

	item addItem();

	skill createSkill();

	int getMod(int a);

	int selectAbility();

	int selectSize();

	string selectAlignment();

	vector<int> getAbilRolls();

	string selectRace();

	void placeScores(vector<int> &scores, int abilities[6]);
}

#endif//DDUTILITIES_H