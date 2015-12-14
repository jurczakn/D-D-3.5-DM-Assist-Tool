#include "inputValidation.h"
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::istringstream;

//-----------------------------------------------------------------------------------
//Requirement #7: Demonstrate error-handling(entire namespace used filter user input 
//-----------------------------------------------------------------------------------
namespace inv{

	int getInt(){//asks user for int and checks input

		cout << "Enter an integer: ";

		string input;

		getline(cin, input);

		std::istringstream instring(input);

		int x;//to store return value

		instring >> x;

		if (instring.fail()){//check for proper input
			cout << "That was not an integer?" << endl;

			x = getInt();
		}

		return x;
	}

	int getInt(int max){//asks user for int and checks input

		cout << "Enter an integer: ";

		string input;

		getline(cin, input);

		std::istringstream instring(input);

		int x;//to store return value

		instring >> x;

		if (instring.fail()){//check for proper input
			cout << "That was not an integer?" << endl;

			x = getInt(max);
		}

		if (x > max || x < 1){//check within range

			cout << "Please use the numbers 1-" << max << " to make your selection." << endl;

			x = getInt(max);
		}

		return x;
	}


	double getDouble(){//asks user for double and checks input

		cout << "Enter an number: ";

		string input;

		getline(cin, input);

		std::istringstream instring(input);

		double x;//to store return value

		instring >> x;

		if (instring.fail()){//check for proper input
			cout << "That was not an integer?" << endl;

			x = getDouble();
		}

		return x;
	}

	double getDouble(double max){//asks user for double and checks input

		cout << "Enter an number: ";

		string input;

		getline(cin, input);

		std::istringstream instring(input);

		double x;//to store return value

		instring >> x;

		if (instring.fail()){//check for proper input
			cout << "That was not an integer?" << endl;

			x = getDouble(max);
		}

		if (x > max || x < 1){//check within range

			cout << "Please use the numbers 1-" << max << " to make your selection." << endl;

			x = getDouble(max);
		}

		return x;
	}

	bool yesNo(){ // checks input for yes no question, yes true, no false
		int askAgain;
		char yesNo;
		do{
			std::cin.get(yesNo);
			std::cin.ignore(100000, '\n');
			askAgain = 1;
			switch (yesNo){
			case 'y':
			case 'Y':
				return true;
				break;
			case 'n':
			case 'N':
				return false;
				break;
			default:
				std::cout << "Please answer yes or no." << std::endl;
				askAgain = 0;
			}
		} while (askAgain == 0);
		return false;
	}

}