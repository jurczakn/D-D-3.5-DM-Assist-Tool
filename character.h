//---------------------------------------------------------------------------------
//Requirement #19: Demonstrate header file
//---------------------------------------------------------------------------------

/*	Author: Nick Jurczak
Date: 12/1/2014
Name: character
Purpose: Contains the definition of the
abstract Character class, which is the 
base class for every available player
class.  It contains all variables a
player character needs as well as 
necessary accessors and mutators.
Also contains the pure virtual
funciton getClass which must be
overloaded in every child class
that inherites from this class.
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "ddUtilities.h"
#include <string>
#include <vector>
#include <fstream>

using DD::armor;
using DD::weapon;
using DD::item;
using DD::skill;
using std::string;
using std::vector;
using std::ostream;
using std::fstream;

class Character{//abstract class all player classes and monsters will use

protected:

	//store base information
	string name;

	string race;

	string alignment;

	string deity;

	int level;

	int size;

	int age;

	char gender;

	double height;

	double weight;

	string eyes;

	string hair;

	string skin;

	//store abilities and temp, [0] = Str, [1] = Dex, [2] = Con, [3] = Intel, [4] = Wix, [5] = Cha
	int abilities[6];

	int tempAbilities[6];

	//store hp and curr hp
	int hp;

	int currHp;

	int speed;

	int baseAttackBonus;

	int initiativeMod;

	int *baseSaveThrows;

	//---------------------------------------------------------------------------------
	//Requirement #16: Demonstrate one object 
	//---------------------------------------------------------------------------------
	vector<weapon> weapons;

	vector<armor> gear;

	vector<item> items;

	vector<skill> skills;

public:

	//use current ability score
	int getStr(){

		return tempAbilities[0];
	}

	int getDex(){

		return tempAbilities[1];

	}

	int getCon(){

		return tempAbilities[2];

	}

	int getIntel(){

		return tempAbilities[3];

	}

	int getWis(){

		return tempAbilities[4];

	}

	int getCha(){

		return tempAbilities[5];

	}

	int getHp(){

		return currHp;

	}

	string getName(){

		return name;

	}

	int getBAB(){//return base attack bonus

		return baseAttackBonus;

	}

	vector<weapon> getWeapons(){

		return weapons;

	}

	vector<armor> getGear(){

		return gear;

	}

	vector<item> getItems(){

		return items;

	}

	vector<skill> getSkills(){

		return skills;

	}

	int getSkillMod(int s);

	int getAc();

	int getTouchAc();

	int getFFAc();

	int getSpeed();

	int getStrMod();

	int getDexMod();

	int getConMod();

	int getIntMod();

	int getWisMod();

	int getChaMod();

	void setWeight();

	int getGrapple();

	string getSize();

	int getInit();

	friend void printCharSheet(Character *c);

	friend ostream& operator<<(ostream&, Character*);

	void raceAdj();

	int getSaveThrow(int t);

	void removeWeapon(int);

	void placeWeapon(weapon);

	void removeGear(int);

	void placeGear(armor);

	void removeItem(int);

	void placeItem(item);

	void addSkill(skill);

	void adjustHP(int);

	void adjustAb(int, int);

	void resetChar();

	//---------------------------------------------------------------------------------
	//Requirement #21: Demonstrate default constructor 
	//---------------------------------------------------------------------------------
	Character(){
	
		baseSaveThrows = new int[3];
	
	}

	Character(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin)
		: name(n), race(r), alignment(a), deity(d), level(l), size(s), age(age), gender(gender), height(ht), eyes(e), hair(h), skin(skin){
	
		baseSaveThrows = new int[3];
	
	}

	Character(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin, int abil[6], int hp, int speed, int bAB, vector<weapon> w, vector<armor> ar, vector<item> items, vector<skill> skills, int iM, int bst[3]);

	//---------------------------------------------------------------------------------
	//Requirement #24: Demonstrate polymorhism
	//---------------------------------------------------------------------------------
	virtual string getClass() = 0;

	//---------------------------------------------------------------------------------
	//Requirement #21: Demonstrate destructor
	//---------------------------------------------------------------------------------
	~Character(){

		delete[] baseSaveThrows;

	}

	//virtual void save(fstream&) = 0;

};


#endif//CHARACTER_H