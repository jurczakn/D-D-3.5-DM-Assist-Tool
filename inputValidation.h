/*	Author: Nick Jurczak
Date: 12/1/2014
Name: inputValidation
Purpose: Includes input validation 
funcitons getInt, getDouble, and
yesNo, that are useful for many
implementaions.  They are all 
contained in the inv namespace.
*/

#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::istringstream;


namespace inv{

	int getInt();

	int getInt(int max);

	double getDouble();

	double getDouble(double max);

	bool yesNo();
}

#endif//INPUTVALIDATION_H