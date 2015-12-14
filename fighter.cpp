#include "ddUtilities.h"
#include "character.h"
#include "fighter.h"
#include "inputValidation.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using DD::getMod;
using DD::armor;
using DD::weapon;
using DD::skill;
using DD::printArmor;
using DD::printWeapon;
using DD::getAbilRolls;
using DD::selectRace;
using DD::structSelect;
using DD::createArmor;
using DD::createWeapon;
using DD::createSkill;
using DD::addItem;
using DD::placeScores;
using inv::yesNo;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::setw;
using std::left;

//---------------------------------------------------------------------------------
//Requirement #21: Demonstrate copy constructor
//---------------------------------------------------------------------------------
Fighter::Fighter(const Fighter &obj){

	baseSaveThrows = new int[3];

	name = obj.name;

	race = obj.race;

	alignment = obj.alignment;

	deity = obj.deity;

	level = obj.level;

	size = obj.size;

	age = obj.age;

	gender = obj.gender;

	height = obj.height;

	eyes = obj.eyes;

	hair = obj.hair;

	skin = obj.skin;

	for (int i = 0; i < 6; i++){

		abilities[i] = obj.abilities[i];

		tempAbilities[i] = obj.tempAbilities[i];

	}

	hp = obj.hp;

	currHp = obj.currHp;

	speed = obj.speed;

	baseAttackBonus = obj.baseAttackBonus;

	weapons = obj.weapons;

	gear = obj.gear;

	skills = obj.skills;

	initiativeMod = obj.initiativeMod;

	for (int i = 0; i < 3; i++){

		baseSaveThrows[i] = obj.baseSaveThrows[i];

	}


}


Fighter::Fighter(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin)
	: Character(n, r, a, d, l, s, age, gender, ht, e, h, skin){

	vector<int> scores = getAbilRolls();

	for (int i = 0; i < 6; i++){//set ability scores to 0

		abilities[i] = 0;
		
	}

	speed = 30;//set base speed

	raceAdj();//adjust scores and speed by race

	//have user place character scores
	cout << "Now please choose where you will place each ability score.\nRemember, for a Fighter, strength is of the most importance, \nbut constitution and dex are also important." << endl

		<< "Your race as already been used to adjust your ability scores." << endl;

	placeScores(scores, abilities);//placed rolled scores in abilites

	for (int i = 0; i < 6; i++){//place ability scores and temp scores

		tempAbilities[i] = abilities[i];
	}

	hp = 10 + getConMod();//set hp

	currHp = hp;//set current hp

	baseAttackBonus = 1;//set base attack bonus

	baseSaveThrows[0] = 2;//set base saving throw 

	baseSaveThrows[1] = 0;

	baseSaveThrows[2] = 0;

	initiativeMod = 0;

	cout << "Now please input your gear and possessions." << "\n(If you are unsure, you can use the \nstarting package on page 39 of the players manual)" << endl;

	cout << "Input first weapon." << endl;//add weapons

	do{

		weapons.push_back(createWeapon());

		if (weapons.back().ranged)//add attack bonus

			//---------------------------------------------------------------------------------
			//Requirement #24: Demonstrate inheritance (getDexMod())
			//---------------------------------------------------------------------------------
			weapons.back().attackBonus = baseAttackBonus + getDexMod();

		else

			weapons.back().attackBonus = baseAttackBonus + getStrMod();

		cout << "Do you want to add another weapon?" << endl;

	} while (yesNo());

	cout << "Do you have gear to add?" << endl;//add armor

	while (yesNo()){

		gear.push_back(createArmor());

		cout << "Do you have another peice of armor to add?" << endl;

	}

	cout << "Do you have other possessions to add?" << endl;

	while (yesNo()){//add items

		items.push_back(addItem());

		cout << "Do you have another item to add?" << endl;

	}

	cout << "Please enter your first skill." << endl;

	do{

		skills.push_back(createSkill());

		cout << "Do you want to add another skill?" << endl;

	} while (yesNo());


}

//void Fighter::save(fstream& out){



