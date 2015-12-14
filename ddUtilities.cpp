#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "ddUtilities.h"
#include "inputValidation.h"
#include "character.h"

using inv::getDouble;
using inv::getInt;
using inv::yesNo;
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
using std::sort;
using std::time;
using std::srand;
using std::rand;

namespace DD{


	//----------------------------------------------------
	//Requirement #8: Demonstrate one overloaded function
	//----------------------------------------------------
	ostream& operator<<(ostream &out, weapon w){

		cout << w.name;

		return out;
	}



	ostream& operator<<(ostream &out, armor a){

		cout << a.name;

		return out;
	}



	ostream& operator<<(ostream &out, item i){

		cout << i.name + " x " + to_string(i.amount);

		return out;
	}

	ostream& operator<<(ostream &out, skill s){

		cout << s.name;

		return out;
	}

	void printWeapon(weapon w){

		cout << "     Attack     | Attack Bonus |   Damage   |  Critical  " << endl;

		cout << setw(16) << w.name << "|";

		cout << setw(14) << w.attackBonus << "|";

		cout << setw(12) << w.damage << "|" << w.critRange[0] << "-" << w.critRange[2] << " *" << w.crit << endl;

		cout << "  Range |     Type     |              Notes              " << endl;

		cout << setw(8) << w.range << "|" << setw(14) << w.type << "|  " << w.notes << endl;

		cout << "Ammunition: ";

		for (int i = 0; i < w.ammo; i++)//represent ammo left

			cout << "*";

		cout << endl;
	}

	void printArmor(armor a){

		cout << "     Armor      | Type | AC Bonus | Weight |   Max Dex  " << endl;

		cout << setw(16) << a.name << "|";

		cout << setw(6) << a.type << "|";

		cout << setw(10) << a.armorBonus << "|";

		cout << setw(8) << a.weight << "|";

		cout << setw(7) << a.maxDexBonus << endl;

		cout << "  Check Penalty | Speed/30 | Speed/20 |Special Properties" << endl;

		cout << setw(16) << a.checkPenalty << "|";

		cout << setw(10) << a.speedPen30 << "|";

		cout << setw(10) << a.speedPen20 << "|";

		cout << a.specProp << endl;

	}

	//----------------------------------------------------
	//Requirement #8: Demonstrate one overloaded function
	//----------------------------------------------------
	void structSelect(vector<int> v){//display options when selecting stuct obj from vector

		for (int i = 0; i < v.size(); i++){//print objects in two columns

			cout << i << ": " << setw(20) << left << v.at(i++);

			if (i < v.size())//check not past last element

				cout << i + 1 << ": " << setw(20) << left << v.at(i);

			cout << endl;
		}
	}

	weapon createWeapon(){//goes step by step to allow user to create weapon

		weapon w;

		cout << "Please enter the name of the weapon: ";

		getline(cin, w.name);

		cout << "Please enter the damage: ";

		getline(cin, w.damage);

		cout << "Please select the critical range.\n\n"
			<<"1: 18-20     2:19-20     3:20" << endl;

		switch (getInt(3)){

		case 1: w.critRange[0] = 18;

			w.critRange[1] = 19;

			w.critRange[2] = 20;

			break;

		case 2: w.critRange[0] = 19;

			w.critRange[1] = 20;

			w.critRange[2] = 20;

			break;

		case 3: w.critRange[0] = 20;

			w.critRange[1] = 20;

			w.critRange[2] = 20;

			break;

		default: w.critRange[0] = 20;

			w.critRange[1] = 20;

			w.critRange[2] = 20;

			break;
		}

		cout << "Please enter crit modifier. ";

		w.crit = getInt();

		cout << "Please enter the range. ";

		w.range = getInt();

		cout << "Is it a ranged weapon?" << endl;

		if (yesNo())

			w.ranged = true;

		else

			w.ranged = false;

		cout << "Please enter the damage type: ";

		getline(cin, w.type);

		cout << "Please enter the weight. ";

		w.weight = getDouble();

		cout << "Please enter notes on weapon. (If none, enter -) " << endl;

		getline(cin, w.notes);

		cout << "Please enter ammunition if any, else enter 0.";

		w.ammo = getInt();

		return w;

	}

	armor createArmor(){

		armor a;

		cout << "Please enter the name of armor: ";

		getline(cin, a.name);

		cout << "Please select armor type. \n\n1: Light\t2: Medium\n3: Heavy\t4: Shield" << endl;

		switch (getInt(4)){

		case 1: a.type = "Light";
			break;

		case 2: a.type = "Medium";
			break;

		case 3: a.type = "Heavy";
			break;

		case 4: a.type = "Shield";
			break;

		default: a.type = "unknown";

		}

		cout << "Please enter armor bonus. ";

		a.armorBonus = getInt();

		cout << "Please enter the check penalty. ";

		a.checkPenalty = getInt();

		cout << "Please enter max dex bonus. ";

		a.maxDexBonus = getInt();

		cout << "Please enter 30 ft speed penalty. (If none, enter 30) ";

		a.speedPen30 = getInt();

		cout << "Please enter 20 ft speed penalty. (If none, enter 20) ";

		a.speedPen20 = getInt();

		cout << "Please enter weight. ";

		a.weight = getDouble();

		cout << "Please enter special properties. (If none, enter -) ";

		getline(cin, a.specProp);


		return a;
	}

	item addItem(){

		item i;

		cout << "Please enter item description: ";

		getline(cin, i.name);

		cout << "How many do you have: ";

		i.amount = getInt();

		cout << "Please enter the item's weight: ";

		i.weight = getDouble();

		return i;
	}

	//---------------------------------------------------------------------------------
	//Requirement #11: Demonstrate pass by value
	//---------------------------------------------------------------------------------
	int getMod(int a){//return modifier for ability score passed

		return (a / 2) - 5;
	}

	int selectAbility(){

		vector<string> abil = { "Str", "Dex", "Con", "Int", "Wis", "Cha" };

		structSelect(abil);

		return getInt(6) - 1;
	}

	int selectSize(){

		vector<string> abil = { "Fine", "Diminutive", "Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan", "Colossal" };

		structSelect(abil);

		return getInt(9) - 5;
	}

	skill createSkill(){

		skill s;

		cout << "Please enter the name of the skill: ";

		getline(cin, s.name);

		cout << "How many ranks to you have: ";

		s.ranks = getInt();

		cout << "Please select which ability modifier it uses: " << endl;

		s.abilMod = selectAbility();

		cout << "Please enter the armor check penalty as a negative.\n(If none, enter 0) " << endl;

		s.checkPenalty = getInt();

		return s;
	}

	string selectAlignment(){

		cout << "Please select your character's alignment. \n(For more information see pg. 103 from the player's guide)" << endl;

		vector<string> alignments = { "Lawful Good", "Lawful Neutral", "Lawful Evil", "Neutral Good", "Neutral", "Neutral Evil", "Chaotic Good", "Chaotic Neutral", "Chaotic Evil" };

		structSelect(alignments);

		return alignments[getInt(9) - 1];

	}

	vector<int> getAbilRolls(){//get rolls and return to call

		vector<int> scores;//store scores

		cout << "Do you want the computer to automatically roll your ability scores?" << endl;

		if (yesNo()){

			unsigned seed = time(0);

			srand(seed);
			
				for (int i = 0; i < 6; i++){

					//-------------------------------------------------
					//Requirement #05: Demonstrates one random number
					//-------------------------------------------------
					scores.push_back(rand() % 24 + 1);
		
				}

				//-------------------------------------------------
				//Requirement #03: Demonstrate logical operator
				//-------------------------------------------------
				while ((scores[0] + scores[1] + scores[2] + scores[3] + scores[4] + scores[5]) / 6 < 12 || scores[5] < 14){

					for (int i = 0; i < 6; i++){

						scores[i] = rand() % 24 + 1;

					}

				}
		}


		else{
			cout << "You will now need use a six sided die to get you ability scores." << endl;//explan process

			for (int i = 0; i < 6; i++){

				int roll = 0;

				vector<int> rolls;

				cout << "Please roll the die 5 times, inputing the roll each time to calculate score #" << i + 1 << endl;

				for (int j = 0; j < 5; j++){

					rolls.push_back(getInt(6));

				}

				sort(rolls.begin(), rolls.end());

				rolls.erase(rolls.begin());

				for (auto h = rolls.begin(); h < rolls.end(); ++h){

					roll += *h;

				}

				cout << "Your ability score #" << i + 1
					<< " is: " << roll << endl;

				scores.push_back(roll);

			}

			sort(scores.begin(), scores.end());

			if ((scores[0] + scores[1] + scores[2] + scores[3] + scores[4] + scores[5]) / 6 < 12 || scores[5] < 14){//check if scores are too low(average less than 12, highest less than 13)

				cout << "Your scores are quite low!!\nDo you want to reroll your character?" << endl;

				if (yesNo())

					//---------------------------------------------------------------------------------
					//Requirement 13: Demonstrate recursion
					//---------------------------------------------------------------------------------
					return getAbilRolls();

			}
		}
		return scores;

	}

	string selectRace(){

		cout << "Please select your race from the following choices: " << endl;
		
		cout << "(Your race will effect your ability scores, \nfor more information look at Ch.2 of the player's manual)" << endl;

		vector<string> races = { "Human", "Dwarf", "Elf", "Gnome", "Half-elf", "Half-orc", "Halfling" };

		structSelect(races);

		switch (getInt(7)){

		case 1: return "Human";

		case 2: return "Dwarf";

		case 3: return "Elf";

		case 4: return "Gnome";

		case 5: return "Half-elf";

		case 6: return "Half-orc";

		case 7: return "Halfling";

		}

	}

	//---------------------------------------------------------------------------------
	//Requirement #11: Demonstate pass by reference
	//---------------------------------------------------------------------------------
	void placeScores(vector<int> &scores, int abilities[6]){//asks user to place scores rolled in abilities they choose

		cout << "Which score will you use for strenght: " << endl;

		int scoreSelect;

		structSelect(scores);

		scoreSelect = getInt(6) - 1;

		abilities[0] += scores[scoreSelect];

		scores.erase(scores.begin() + scoreSelect);

		cout << "Which score will you use for dexterity: " << endl;

		structSelect(scores);

		scoreSelect = getInt(5) - 1;

		abilities[1] += scores[scoreSelect];

		scores.erase(scores.begin() + scoreSelect);

		cout << "Which score will you use for constitution: " << endl;

		structSelect(scores);

		scoreSelect = getInt(4) - 1;

		abilities[2] += scores[scoreSelect];

		scores.erase(scores.begin() + scoreSelect);

		cout << "Which score will you use for intelligence: " << endl;

		structSelect(scores);

		scoreSelect = getInt(3) - 1;

		abilities[3] += scores[scoreSelect];

		scores.erase(scores.begin() + scoreSelect);

		cout << "Which score will you use for wisdom: " << endl;

		structSelect(scores);

		scoreSelect = getInt(2) - 1;

		abilities[4] += scores[scoreSelect];

		scores.erase(scores.begin() + scoreSelect);

		cout << "Your last score will be use for charisma. " << endl;

		abilities[5] += scores[0];

	}

}
