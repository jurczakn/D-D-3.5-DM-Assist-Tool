
#include "ddUtilities.h"
#include "character.h"
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
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::setw;
using std::left;

Character::Character(string n, string r, string a, string d, int l, int s, int age, char gender, double ht, string e, string h, string skin, int abil[6], int hp, int speed, int bAB, vector<weapon> w, vector<armor> ar, vector<item> items, vector<skill> skills, int iM, int bst[3])
	: name(n), race(r), alignment(a), deity(d), level(l), size(s), age(age), gender(gender), height(ht), eyes(e), hair(h), skin(skin), hp(hp), speed(speed), baseAttackBonus(bAB), weapons(w), gear(ar), initiativeMod(iM){

	//---------------------------------------------------------------------------------
	//Requirement #14: Demonstrate one dynamically allocated array 
	//---------------------------------------------------------------------------------
	baseSaveThrows = new int[3];

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------
	//Requirement #10: Demonstrate scope(variable name i is used in 3 loops inside this funciton, but cannot access i from another loop, which makes this possible) 
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < 6; i++){//place ability scores and temp scores

		abilities[i] = abil[i];

		tempAbilities[i] = abil[i];
	}
	
	for (int i = 0; i < 3; i++){//place base save throw scores

		baseSaveThrows[i] = bst[i];

	}

	weapons = w;

	for (auto i = weapons.begin(); i != weapons.end(); ++i){//set up attack bonuses for weapons

		if (i->ranged)

			i->attackBonus = abilities[1];

		else 

			i->attackBonus = abilities[0];

	}

	gear = ar;

	this->skills = skills;

	this->items = items;

	currHp = hp;

	setWeight();



}

int Character::getAc(){//calculate armor class

	int ac = 10;//starting ac

	ac += getDexMod();//add dex bonus

	ac -= size;//subtract size penalty, if size negative, size bonus added

	for (auto i = gear.begin(); i != gear.end(); ++i){//add armor bonuses

		ac += i->armorBonus;
	}

	return ac;
}

int Character::getTouchAc(){// return touch armor class

	int ac = 10;//starting ac

	ac += getDexMod();//add dex bonus

	ac -= size;//subtract size penalty, if size negative, size bonus added

	return ac;
}

int Character::getFFAc(){// return flat-footed armor class

	int ac = 10;//starting ac

	ac -= size;//subtract size penalty, if size negative, size bonus added

	for (auto i = gear.begin(); i != gear.end(); ++i){//add armor bonuses

		ac += i->armorBonus;
	}

	return ac;

}

int Character::getSpeed(){

	int s = speed;

	if (speed == 20){//check for armor speed penalty
	
		for (auto i = gear.begin(); i != gear.end(); ++i){

			if (i->speedPen20 < s)

				s = i->speedPen20;


		}
	}

	if (speed == 30){//check for armor speed penalty

		for (auto i = gear.begin(); i != gear.end(); ++i){

			if (i->speedPen30 < s)

				s = i->speedPen30;


		}
	}

	return s;
}

int Character::getStrMod(){

	return getMod(tempAbilities[0]);

}

int Character::getDexMod(){

	return getMod(tempAbilities[1]);

}

int Character::getConMod(){

	return getMod(tempAbilities[2]);

}

int Character::getIntMod(){

	return getMod(tempAbilities[3]);

}

int Character::getWisMod(){

	return getMod(tempAbilities[4]);

}

int Character::getChaMod(){

	return getMod(tempAbilities[5]);

}

void Character::setWeight(){

	weight = 0;

	for (auto i = gear.begin(); i != gear.end(); ++i){//weight of gear

		weight += i->weight;

	}

	for (auto i = weapons.begin(); i != weapons.end(); ++i){//add weight of weapons

		weight += i->weight;

	}

	for (auto i = items.begin(); i != items.end(); ++i){//add weight of possesions

		weight += i->weight;

	}
}

int Character::getGrapple(){

	return baseAttackBonus + getStrMod() + size;

}

int Character::getSkillMod(int s){

	int penalty = 0;

	for (auto i = gear.begin(); i != gear.end(); ++i){//add penalties of gear

		penalty += i->checkPenalty;

	}

	penalty = penalty * skills[s].checkPenalty;

	return skills[s].ranks + getMod(tempAbilities[skills[s].abilMod]) + penalty;//add ranks, ability modifier, and penalty(should be negative)
}

string Character::getSize(){

	switch (size){

	case -4: return "Fine";

	case -3: return "Diminutive";

	case -2: return "Tiny";

	case -1: return "Small";

	case 0: return "Medium";

	case 1: return "Large";

	case 2: return "Huge";

	case 3: return "Gargantuan";

	case 4: return "Colossal";
	}
	
	return "unknown";
}

int Character::getInit(){

	return getDexMod() + initiativeMod;
}

int Character::getSaveThrow(int t){//returns saving throw modifier, pass 1 for fortitude, 2 for reflex, or 3 for will

	if (t == 1)

		return baseSaveThrows[0] + getConMod();

	else if (t == 2)

		return baseSaveThrows[1] + getDexMod();

	else

		return baseSaveThrows[2] + getWisMod();
}

void Character::raceAdj(){

	if (race == "Dwarf"){

		abilities[2] += 2;

		abilities[5] -= 2;

		speed -= 10;
	}

	if (race == "Elf"){

		abilities[1] += 2;

		abilities[2] -= 2;
	}

	if (race == "Gnome"){

		abilities[2] += 2;

		abilities[0] -= 2;

		speed -= 10;
	}

	if (race == "Half-orc"){

		abilities[0] += 2;

		abilities[3] -= 2;

		abilities[5] -= 2;
	}

	if (race == "Halfling"){

		abilities[1] += 2;

		abilities[0] -= 2;

		speed -= 10;
	}

}

void Character::removeWeapon(int w){

	weapons.erase(weapons.begin() + w);

}

void Character::placeWeapon(weapon w){

	weapons.push_back(w);

}

void Character::removeGear(int g){

	gear.erase(gear.begin() + g);

}

void Character::placeGear(armor a){

	gear.push_back(a);

}

void Character::removeItem(int i){

	items.erase(items.begin() + i);

}

void Character::placeItem(item i){

	items.push_back(i);

}

void Character::addSkill(skill s){

	skills.push_back(s);

}

void Character::adjustHP(int health){

	currHp += health;

}

void Character::adjustAb(int ab, int t){

	tempAbilities[ab] += t;

}

void Character::resetChar(){

	for (int i = 0; i < 6; i++){//place ability scores and temp scores

		tempAbilities[i] = abilities[i];
	}

	currHp = hp;//reset current hp

}

void printCharSheet(Character *c){// show character sheet of player passed

	cout << "Name: " << c->name << endl;

	cout << "Class: " << setw(15) << left << c->getClass() << "Level: " << setw(3) << left << c->level
		<< "Alignment: " << setw(16) << left << c->alignment << "Deity: " << setw(15) << left << c->deity << endl;

	cout << "Size: " << setw(11) << left << c->getSize() << "Age: " << setw(4) << left << c->age << "Gender: " << c->gender
		<< " Height: " << setw(5) << left << c->height << "Weight: " << setw(5) << left << c->weight << endl
		<< "Eyes: " << setw(8) << left << c->eyes << "Hair: " << setw(8) << left << c->hair << "Skin: " << setw(8) << left << c->skin << endl;

	cout << endl;

	cout << "   Ability     Score  Modifier  Temp     Total  Current  Speed" << endl;

	cout << "    Strength:  " << setw(7) << left << c->abilities[0] << setw(10) << getMod(c->abilities[0]) << setw(5) << c->tempAbilities[0] << "HP: " << setw(7) << left << c->hp << setw(9) << left << c->currHp << c->speed << endl;

	cout << "   Dexterity:  " << setw(7) << left << c->abilities[1] << setw(10) << getMod(c->abilities[1]) << setw(5) << c->tempAbilities[1] << endl;

	cout << "Constituiton:  " << setw(7) << left << c->abilities[2] << setw(10) << getMod(c->abilities[2]) << setw(5) << c->tempAbilities[2] << "Armor Class: " << c->getAc() << endl;

	cout << "Intelligence:  " << setw(7) << left << c->abilities[3] << setw(10) << getMod(c->abilities[3]) << setw(5) << c->tempAbilities[3] << "Touch Armor Class: " << c->getTouchAc() << endl;

	cout << "      Wisdom:  " << setw(7) << left << c->abilities[4] << setw(10) << getMod(c->abilities[4]) << setw(5) << c->tempAbilities[4] << "Flat-Footed Armor Class: " << c->getFFAc() << endl;

	cout << "    Charisma:  " << setw(7) << left << c->abilities[5] << setw(10) << getMod(c->abilities[5]) << setw(5) << c->tempAbilities[5] << "Initiative Modifier: " << c->getInit() << endl;

	cout << endl;

	cout << "Saving Throws  Total" << endl;

	cout << "    Fortitude: " << setw(7) << left << c->getSaveThrow(1) << "Base Attack Bonus: " << c->baseAttackBonus << endl;

	cout << "       Reflex: " << setw(7) << left << c->getSaveThrow(2) << "Grapple Modifier: " << c->getGrapple() << endl;

	cout << "         Will: " << c->getSaveThrow(3) << endl;

	cout << endl;

	cout << "        SKILLS       " << endl;

	cout << "Skill Name  Skill Mod" << endl;

	for (int i = 0; i < c->skills.size(); i++){

		cout << setw(12) << left << c->skills[i].name << c->getSkillMod(i) << endl;

	}

	cout << endl;

	cout << "                    ATTACKS" << endl << endl;

	for (auto i = c->weapons.begin(); i != c->weapons.end(); ++i){

		printWeapon(*i);

	}

	cout << endl;

	cout << "                   GEAR" << endl << endl;

	for (auto i = c->gear.begin(); i != c->gear.end(); ++i){

		printArmor(*i);

	}

	cout << endl;

	cout << "   Possessions" << endl << endl;

	for (int i = 0; i < c->items.size(); i++){

		cout << c->items.at(i) << endl;

	}

	cout << endl;
}


//---------------------------------------------------------------------------------
//Requirement #22: Demonstrate overloaded operator
//---------------------------------------------------------------------------------
ostream& operator<<(ostream &out, Character *c){

	out << c->name;

	return out;
}

