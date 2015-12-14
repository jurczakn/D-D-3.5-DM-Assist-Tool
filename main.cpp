/*	Author: Nick Jurczak
	Date: 12/1/2014
	Name: D&D 3.5 Assist Tool
	Purpose: Allow Dungeon Master to keep track of
	party members' character sheets as well as edit
	and display.
*/

#include "character.h"
#include "fighter.h"
#include "bard.h"
#include "barbarian.h"
#include "ranger.h"
#include "ddUtilities.h"
#include "inputValidation.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using DD::selectAlignment;
using DD::skill;
using DD::createSkill;
using DD::selectAbility;
using DD::item;
using DD::addItem;
using DD::armor;
using DD::createArmor;
using DD::printArmor;
using DD::structSelect;
using DD::weapon;
using DD::createWeapon;
using DD::structSelect;
using DD::selectSize;
using DD::selectRace;
using inv::yesNo;
using inv::getInt;
using inv::getDouble;
using std::cout;
using std::string;
using std::fstream;
using std::ios;

Character* createCharacter();

Character* rollCharacter();

Character* selectPartyMember(vector<Character*>);

template <class T>
bool load(fstream &in, T &c){//attempts to load character from file passed into character passed(returns true if successful, false if not)

	in.read(reinterpret_cast<char*> (&c), sizeof(T));

	if (in.eof()){

		cout << "File ended." << endl;

		return false;
	}

	else{

		//cout << c << " has been loaded." << endl;

		return true;

	}
}

bool loadParty(fstream &in, vector<Character*> p){//attempts to load party members from file(returns true if done successfully, false if not)

	cout << "What file do you with to load?" << endl;

	char inFile[20];

	cin.getline(inFile, 20);

	in.open(inFile, ios::in | ios::binary);

	if (!in){

		in.clear();

		cout << "Sorry, " << inFile << " could not be loaded\nWould you like to try another file?" << endl;

		if (yesNo())

			loadParty(in, p);

		else

			return false;
	}

	Character *c = new Fighter();

	while (load(in, c)){

		p.push_back(c);

	}

	in.close();

	if (p.size() == 0){

		cout << "Sorry, no characters were loaded.\nWould you like to try another file?" << endl;

		if (yesNo())

			loadParty(in, p);

		else

			return false;

	}

	return true;

	/*cout << "What class is the first character?" << endl;

	vector<string> classes = { "Fighter", "Bard", "Barbarian", "Ranger" };

	structSelect(classes);

	int sclass = getInt(4);

	if (sclass == 1){

		Fighter f();

		load(in, f);

		Character * c = &f;

		p.push_back(c);
		
	}*/
}

void save(fstream &out, Character *c){

	//---------------------------------------------------
	//Requirement #02: Demonstrate explicit type casting
	//---------------------------------------------------
	out.write(reinterpret_cast<char*> (c), sizeof(Character));

	cout << c << " has been saved." << endl;
}

void accessParty(vector<Character*> p, char map[][10]);


int main(int argc, char *argv[]){

	cout << "Thank you for using the Dungeons and Dragons\nDungeon Master Assist Tool. \nIt is based of Dungeons and Dragons\n"
		<< "version 3.5 by Wizards of the Coast.\nIt allows to to create digital copies\nof your character sheets to view and edit.\n"
		<< "You will be asked to start by creating\nyour first character.\n"
		<< "At several points, this program references\nthe Player's Handbook Core Rulebook v3.5.\nIf you do not have a copy\n"
		<< "or are new to Dungeon's and Dragons\nyou can download a copy from \nminus.com/mdnd35\n(along with several other reference books)\n"
		<< "or viewable in-browser from\nwww.aegisoft.be/costa/data/roleplay/D&D%203.5%20-%20Players%20Handbook%20%5BOEF%5D.pdf" << endl;

	//---------------------------------------------------------------------------------
	//Requirement #24: Demonstrate polymorhism
	//---------------------------------------------------------------------------------
	vector<Character*> party;

	int selection;

	//---------------------------------------------------------------------------------
	//Requirement #6: Would cause a syntax error, using {} instead of [] for array
	//---------------------------------------------------------------------------------
	//char map{10}{10};
	//---------------------------------------------------------------------------------
	//Requirement #14: Demonstrate one multi-dementional array 
	//---------------------------------------------------------------------------------
	char map[10][10];

	for (int i = 0; i < 10; i++){

		for (int j = 0; j < 10; j++){

			map[i][j] = '#';

		}

	}

	//-------------------------------------------------
	//Requirement #01: Demonstrate simple output
	//-------------------------------------------------
	cout << "Add the first member to your party." << endl;//make user create at least one character to run program

	vector<string> startMenu = { "Input Character", "Roll New Character" };

	structSelect(startMenu);
	
	selection = getInt(2);

	switch (selection){

	case 1: party.push_back(createCharacter());

		break;

	case 2: party.push_back(rollCharacter());

		break;
	}

	//-------------------------------------------------
	//Requirement #04: Demonstrate a loop
	//-------------------------------------------------
	do{

		//---------------------------------------------------------------------------------------------------------------------------
		//Requirement #9: Demonstrate functional decomposition (Only main menu in main function, each selection has its own function) 
		//---------------------------------------------------------------------------------------------------------------------------
		vector<string> mainMenu = { "Input Character", "Roll New Character", "Print Char Sheet", "Access Party Member", "Print Map", "Reset Map", "Save and Quit" };

		structSelect(mainMenu);

		selection = getInt(7);

		switch (selection){

		case 1: party.push_back(createCharacter());

			break;

		case 2: party.push_back(rollCharacter());

			break;

		case 3: printCharSheet(selectPartyMember(party));

			break;

		case 4: try{

			accessParty(party, map);

		}
				//---------------------------------------------------------------------------------
				//Requirement #25: Demonstrate exceptions
				//---------------------------------------------------------------------------------
				catch (string e){

					cout << "Sorry, your party is " << e << ". Please try adding a character first." << endl;

				}

			break;

		case 5: for (int i = 0; i < 10; i++){

			for (int j = 0; j < 10; j++){

				cout << map[i][j];

			}
			cout << endl;
		}

				break;

		case 6: for (int i = 0; i < 10; i++){

			for (int j = 0; j < 10; j++){

				map[i][j] = '#';

			}
		}

		}

	} while (selection != 7);

	//---------------------------------------------------------------------------------
	//Requirement #23: Demonstrate file IO
	//---------------------------------------------------------------------------------
	fstream iofile;

	//---------------------------------------------------------------------------------
	//Requirement #15: Demonstrate command line argument
	//---------------------------------------------------------------------------------
	if (argc < 2){

		//---------------------------------------------------------------------------------
		//Requirement #15: Demonstrate command line argument usage statment
		//---------------------------------------------------------------------------------
		cout << "usage: " << argv[0] << " [save_file]" << endl;

		cout << "What would you like to name the save file for your party?" << endl;

		//-------------------------------------------------
		//Requirement #12: Use at least one c-style string
		//-------------------------------------------------
		char filename[20];

		//-------------------------------------------------
		//Requirement #01: Demonstrate simple input
		//-------------------------------------------------
		cin.getline(filename, 20);

		//-------------------------------------------------
		//Requirement #03: Demonstate bitwise operator
		//-------------------------------------------------
		iofile.open(filename, ios::out | ios::binary);
	}

	else {

		//---------------------------------------------------------------------------------
		//Requirement #15: Demonstrate command line argument
		//---------------------------------------------------------------------------------
		iofile.open(argv[1], ios::out | ios::binary);

	}

	for (auto i = party.begin(); i != party.end(); ++i){

		save(iofile, *i);

	}

	iofile.close();

	//------------------------------------------------------------------------------------------------
	//Requirement #7: Demonstrate debugging(commented out section below is what I used for debugging) 
	//------------------------------------------------------------------------------------------------
	/*Character *gOldman;// = rollCharacter();

	printCharSheet(gOldman);

	fstream iofile;

	char file[] = "Lurch.dat";

	iofile.open(file, ios::in | ios::binary);

	gOldman = load(iofile);

	printCharSheet(gOldman);

	cin.get();
	vector<weapon> gutzWeps;

	weapon greatSword{ "greatsword", "1d8", false, 4, { 19, 20, 20 }, 2, 10, "slash", 5.5, "Badass", 0 };

	gutzWeps.push_back(greatSword);

	vector<armor> gear;

	armor leather{ "leather", "light", 4, 8, 1, 3.4, 20, 25, "-" };

	gear.push_back(leather);

	item b = { "rocks", 3, 1.2 };

	item c = { "bags", 4, 0.2 };

	item d = { "health potion", 2, 1.2 };

	vector<item> items;

	items.push_back(b);

	items.push_back(c);

	items.push_back(d);

	vector<skill> skills;

	skill swim{ "swim", 3, 1, -2 };

	skills.push_back(swim);

	int abil[6] = { 18, 12, 17, 14, 15, 9 };

	int bst[3] = { 2, 0, -2 };

	Character *guts;

	guts = new Fighter("Gutz", "Human", "Neutral Good", "None", 1, -1, 22, 'M', 6.2, "Blue", "Black", "White", abil, 15, 30, 4, gutzWeps, gear, items, skills, 2, bst);

	printCharSheet(guts);

	cout << (guts->getItems()).at(0);

	Character *gutz = createCharacter();

	weapon w = createWeapon();

	cout << "     Attack     | Attack Bonus |   Damage   |  Critical  " << endl;

	cout << setw(16) << w.name << "|";

	cout << setw(14) << " " << "|";

	cout << setw(12) << w.damage << "|" << w.critRange[0] << "-" << w.critRange[2] << " *" << w.crit << endl;

	cout << "  Range |     Type     |              Notes              " << endl;

	cout << setw(8) << w.range << "|" << setw(14) << w.type << "|  " << w.notes << endl;

	cout << "Ammunition: ";

	for (int i = 0; i < w.ammo; i++)//represent ammo left

		cout << "*";

	cout << endl;

	armor a = createArmor();

	printArmor(a);

	item i = addItem();

	cout << i << endl;

	item b = { "rocks", 3, 1.2 };

	item c = { "bags", 4, 0.2 };

	item d = { "health potion", 2, 1.2 };

	vector<item> items;

	items.push_back(i);

	items.push_back(b);

	items.push_back(c);

	items.push_back(d);

	item e = { "lock-picks", 4, 0.1 };

	items.push_back(e);

	cout << b;

	cout << endl << "Which item do you want to print?" << endl;

	structSelect(items);

	cout << items.at(getInt(items.size()) - 1);
*/
	return 0;
}

//------------------------------------------
//Requirement #8: Demonstrate one function 
//------------------------------------------
Character* createCharacter(){//asks player input for every element of character to create character, returns pointer.

	//---------------------------------------------------------------------------------
	//Requirement #12: Demonstrate one std::string 
	//---------------------------------------------------------------------------------
	string n;

	string r;

	string a;

	string d;

	int l;

	int s;

	int age;

	char g;

	double ht;

	string e;

	string h;

	string skin;

	int abil[6];

	int hp;

	int speed;

	int bAB;

	int bst[3];

	vector<weapon> weapons;

	vector<armor> ar;

	vector<item> items;

	vector<skill> skills;

	int iM;

	cout << "Start by entering basic information.\n" << "Name: ";

	getline(cin, n);

	cout << "Please enter race: ";

	getline(cin, r);

	a = selectAlignment();

	cout << "Please enter deity: ";

	getline(cin, d);

	cout << "Please enter level. ";

	l = getInt();

	cout << "Please select size: " << endl;

	s = selectSize();

	cout << "Please enter age. ";

	age = getInt();

	vector<string> genders = { "Male", "Female", "Other" };

	structSelect(genders);

	int gselect = getInt(3);

	if (gselect == 1)

		g = 'M';

	else if (gselect == 2)

		g = 'F';

	else

		g = 'O';

	cout << "Enter height. ";

	ht = getDouble();

	cout << "Enter eye color: ";

	getline(cin, e);

	cout << "Enter hair color: ";

	getline(cin, h);

	cout << "Enter skin color: ";

	getline(cin, skin);

	cout << "Enter strength score. ";

	abil[0] = getInt();

	cout << "Enter dexterity score. ";

	abil[1] = getInt();

	cout << "Enter constitution score. ";

	abil[2] = getInt();

	cout << "Enter inteligence score. ";

	abil[3] = getInt();

	cout << "Enter wisdom score. ";

	abil[4] = getInt();

	cout << "Enter charisma score. ";

	abil[5] = getInt();

	cout << "Enter hit points. ";

	hp = getInt();

	cout << "Enter initiative modifier. (If none enter 0) ";

	iM = getInt();

	cout << "Enter speed. ";

	speed = getInt();

	cout << "Enter fortitude base save. ";

	bst[0] = getInt();

	cout << "Enter reflex base save. ";

	bst[1] = getInt();

	cout << "Enter will base save. ";

	bst[2] = getInt();

	cout << "Enter base attack bonus. ";

	bAB = getInt();

	cout << "Input first weapon." << endl;

	do{

		weapons.push_back(createWeapon());

		cout << "Do you want to add another weapon?" << endl;

	} while (yesNo());

	cout << "Do you have gear to add?" << endl;

	while (yesNo()){

		ar.push_back(createArmor());

		cout << "Do you have another peice of armor to add?" << endl;

	}

	cout << "Do you have other possessions to add?" << endl;

	while (yesNo()){

		items.push_back(addItem());

		cout << "Do you have another item to add?" << endl;

	}

	cout << "Please enter your first skill." << endl;

	do{

		skills.push_back(createSkill());

		cout << "Do you want to add another skill?" << endl;

	} while (yesNo());

	vector<string> classes = { "Fighter", "Bard", "Barbarian", "Ranger" };

	structSelect(classes);

	int sclass = getInt(4);

	//---------------------------------------------------------------------------------
	//Requirement #17: Demonstrate pointer to object
	//---------------------------------------------------------------------------------
	Character *c;

	switch (sclass){

	case 1: c = new Fighter(n, r, a, d, l, s, age, g, ht, e, h, skin, abil, hp, speed, bAB, weapons, ar, items, skills, iM, bst);

		break;

	case 2: c = new Bard(n, r, a, d, l, s, age, g, ht, e, h, skin, abil, hp, speed, bAB, weapons, ar, items, skills, iM, bst);

		break;

	case 3: c = new Barbarian(n, r, a, d, l, s, age, g, ht, e, h, skin, abil, hp, speed, bAB, weapons, ar, items, skills, iM, bst);

		break;

	case 4: c = new Ranger(n, r, a, d, l, s, age, g, ht, e, h, skin, abil, hp, speed, bAB, weapons, ar, items, skills, iM, bst);

		break;
	}

	return c;

}

Character* rollCharacter(){//create character from scratch with help

	//basic elements storage
	string n;

	string r;

	string a;

	string d;

	int l = 1;

	int s;

	int age;

	char g;

	double ht;

	string e;

	string h;

	string skin;

	//get basic element input
	cout << "Start by entering basic information.\n" << "Name: ";

	getline(cin, n);

	r = selectRace();

	a = selectAlignment();

	cout << "Please enter deity: ";

	getline(cin, d);

	cout << "Please select size: (For more information see chart on page \n134 of the player's manual." << endl;

	s = selectSize();

	cout << "Please enter age. ";

	age = getInt();

	vector<string> genders = { "Male", "Female", "Other" };

	structSelect(genders);

	int gselect = getInt(3);

	if (gselect == 1)

		g = 'M';

	else if (gselect == 2)

		g = 'F';

	else

		g = 'O';

	cout << "Enter height. ";

	ht = getDouble();

	cout << "Enter eye color: ";

	getline(cin, e);

	cout << "Enter hair color: ";

	getline(cin, h);

	cout << "Enter skin color: ";

	getline(cin, skin);

	Character *c;

	vector<string> classes = { "Fighter", "Bard", "Barbarian", "Ranger" };

	structSelect(classes);

	int sclass = getInt(4);

	switch (sclass){

	case 1: c = new Fighter(n, r, a, d, l, s, age, g, ht, e, h, skin);

		break;

	case 2: c = new Bard(n, r, a, d, l, s, age, g, ht, e, h, skin);

		break;

	case 3: c = new Barbarian(n, r, a, d, l, s, age, g, ht, e, h, skin);

		break;

	default: c = new Ranger(n, r, a, d, l, s, age, g, ht, e, h, skin);

		break;
	}
	
	return c;


}

Character* selectPartyMember(vector<Character*> p){

	cout << "Select a character from you party to use: " << endl;

		for (int i = 0; i < p.size(); i++){//print objects in two columns

			cout << i << ": " << setw(20) << left << p.at(i++);

			if (i < p.size())//check not past last element

				cout << i + 1 << ": " << setw(20) << left << p.at(i);

			cout << endl;
		}

	return p.at(getInt(p.size()) - 1);

}

void accessParty(vector<Character*> p, char map[10][10]){

	if (p.size() < 1){

		//---------------------------------------------------------------------------------
		//Requirement #25: Demonstrate exceptions
		//---------------------------------------------------------------------------------
		throw "empty";

	}

	Character *c = selectPartyMember(p);

	cout << "What do you want to access?" << endl;

	vector<string> apMenu = { "Modify Ability", "Modify Health", "Add Weapon", "Remove Weapon", "Add Gear", "Remove Gear", "Add Item", "Remove Item", "Add Skill", "Reset Character", "Place/Move on Map"};

	structSelect(apMenu);

	int accessSelect = getInt(11);
	
	if (accessSelect == 1){//mod temp ability

		int ab = selectAbility();

		cout << "By how much would you like to modify it?" << "\n(To decrease use a negative number)" << endl;

		int mod = getInt();

		c->adjustAb(ab, mod);

	}

	if (accessSelect == 2){//mod curr health

		cout << "By how much would you like to modify it?" << "\n(To decrease use a negative number)" << endl;

		int mod = getInt();

		c->adjustHP(mod);

	}

	if (accessSelect == 3){//add weapon

		c->placeWeapon(createWeapon());

	}

	if (accessSelect == 4 && c->getWeapons().size() != 0){//remove weapon

		cout << "Which weapon would you like to remove?" << endl;

		structSelect(c->getWeapons());

		c->removeWeapon(getInt(c->getWeapons().size()) - 1);

	}

	if (accessSelect == 5){//add gear

		c->placeGear(createArmor());

	}

	if (accessSelect == 6 && c->getGear().size() != 0){//remove gear

		cout << "What gear would you like to remove?" << endl;

		structSelect(c->getGear());

		c->removeGear(getInt(c->getGear().size()) - 1);

	}

	//----------------------------------------------------------------------------------------------------------------------
	//Requirement #6: Would cause logic error because the user would expect to remove an item, not add one, then remove one 
	//----------------------------------------------------------------------------------------------------------------------
	//if (accessSelect == 8){//add item
	//
	//	c->placeItem(addItem());
	//
	//}
	if (accessSelect == 7){//add item

		c->placeItem(addItem());

	}

	if (accessSelect == 8 && c->getItems().size() != 0){//remove item

		cout << "What possession would you like to remove?" << endl;

		structSelect(c->getItems());

		c->removeItem(getInt(c->getItems().size()) - 1);

	}

	if (accessSelect == 9){//add item

		c->addSkill(createSkill());

	}

	if (accessSelect == 10){//reset

		cout << "Are you sure? This will permenantly delete all temporary scores." << endl;

		if (yesNo())

			c->resetChar();

	}

	if (accessSelect == 11){//put peice on map
	
		cout << "Enter coordnates for " << c << endl;

		cout << "X coornate, ";

		int x = getInt(10);

		cout << "Y coordnate ";

		int y = getInt(10);
		//---------------------------------------------------------------------------------
		//Requirement #6: Would cause runtime error if user tried to access coordnate 1, 1 
		//---------------------------------------------------------------------------------
		//map[11-y][11-x] = c->getName().at(0)
		map[10 - y][10 - x] = c->getName().at(0);

	}
}