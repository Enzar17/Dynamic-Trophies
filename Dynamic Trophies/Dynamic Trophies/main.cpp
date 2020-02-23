/* Programmer: Liam McAleavey
 * Class: CS 2250
 * Due Date: Feb 19, 2020
 * Description: This program creates a list of trohpies in vector format
 *				and provides the user with a number of ways to manipulate
 *				that vector, including adding, deleting, and changing
 *				member values
 */

#include <iostream>
#include <string>
#include <vector>
#include "Trophy.h"
using namespace std;

// Reusable strings
const string PROMPT_FOR_NAME = "Please enter the name of the Trophy";
const string PROMPT_FOR_LEVEL = "Please enter the level of your Trophy (between 1 and 10)";
const string PROMPT_FOR_COLOR = "Please enter the color of your Trophy (GOLD, SILVER, or BRONZE)";

// Menu choice handlers
void addTrophy(vector<Trophy*>& trophyVector);
void copyTrophy(vector<Trophy*>& trophyVector);
void deleteTrophy(vector<Trophy*>& trophyVector);
void renameTrophy(vector<Trophy*>& trophyVector);
void relevelTrophy(vector<Trophy*>& trophyVector);
void recolorTrophy(vector<Trophy*>& trophyVector);
void printTrophies(vector<Trophy*>& trophyVector);

// Input handlers
int printMenu();
Trophy* promptForTrophy();
string promptForString(const string& message);
int promptForInt(const string& message, int minimum, int maximum);
TrophyColor promptForColor(const string& message);

// Useful helper methods
string stringToUpper(string value);
int searchForTrophy(vector<Trophy*>& trophyVector, string name);

// main()
// Parameters:
//      none
// Return Value:
//      int - Returns a 0 if main executed correctly, and a 1 if it did not
// Description:
//      Governs the main loop of giving the user a menu, processing their
//      input, and then calling a function add, remove, or alter their
//		collection of trophies
int main()
{
	cout << "***********************************************" << endl
		<< "Welcome to the Trophy editor!" << endl
		<< "With this application, you can manage your trophy" << endl
		<< "collection - add, modify, or remove trophies by" << endl
		<< "using this simple menu!" << endl
		<< "***********************************************" << endl;

	vector<Trophy*> trophies;		// Vector that will store our collection of Trophy pointers

	// Loop the menu, allowing the user to select an action each time
	int input;
	do
	{
		input = printMenu();
		switch (input)
		{
		case 1:		// Add a new Trophy
			addTrophy(trophies);
			break;
		case 2:		// Copy an existing Trophy
			copyTrophy(trophies);
			break;
		case 3:		// Delete an existing Trophy
			deleteTrophy(trophies);
			break;
		case 4:		// Rename a Trophy
			renameTrophy(trophies);
			break;
		case 5:		// Change the level of a Trophy
			relevelTrophy(trophies);
			break;
		case 6:		// Change the color of a Trophy
			recolorTrophy(trophies);
			break;
		case 7:		// Print all Trophies
			printTrophies(trophies);
			break;
		case 8:		// Exit
			cout << "You have chosen to exit the application, good-bye!" << endl;
			break;
		default:
			cout << "That is not a recognized menu selection, choose again." << endl;
			break;
		}

	} while (input != 8);

	// Now that the program is over, delete EVERY trophy from the collection
	int vectorLength = trophies.size();
	for (int i = 0; i < vectorLength; i++)
	{
		vector<Trophy*>::iterator it = trophies.begin();
		trophies[0]->~Trophy();
		trophies.erase(it);
	}

	return 0;
}

// printMenu()
// Parameters:
//      none
// Return Value:
//      int - Returns a whatever the user input for their menu choice
// Description:
//      Prints a selection menu, and then takes an input from the user
//		and returns that input
int printMenu()
{
	string strInput = "";	// Will store whatever thing the user enters
	int input;				// Will store our converted integer value

	cout << "-----------------------------------------" << endl
		<< "Please select an option :" << endl
		<< "1 - Add a new Trophy" << endl
		<< "2 - Copy a Trophy" << endl
		<< "3 - Delete a Trophy" << endl
		<< "4 - Rename a Trophy" << endl
		<< "5 - Change the level of a Trophy" << endl
		<< "6 - Change the color of a Trophy" << endl
		<< "7 - Print All the Trophies" << endl
		<< "8 - Exit the program" << endl
		<< "-----------------------------------------" << endl;
	
	// Get whatever the user puts in
	getline(cin, strInput);

	// Try converting that value to an int. If an exception is thrown,
	// then set userInt to a value outside the acceptable range so they
	// will be prompted again
	try
	{
		input = stoi(strInput);
	}
	catch (exception& e)
	{
		input = -1;
	}

	// Return the validated entry
	return input;
}

// addTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies we'll modify
// Return Value:
//      void
// Description:
//      Creates a new trophy through promptForTrophy(), and then adds that
//		trophy to the back of the trophy vector
void addTrophy(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to add a trophy." << endl;
	Trophy* trophyToAdd = new Trophy(*promptForTrophy());
	trophyVector.push_back(trophyToAdd);
}

// deleteTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies we'll modify
// Return Value:
//      void
// Description:
//      Searches for the index of the trophy we need to delete using searchForTrophy(),
//		and if it is found, erases that trophy from the vector
void deleteTrophy(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to delete an existing trophy." << endl;
	string name = promptForString(PROMPT_FOR_NAME);
	int trophyPosition = searchForTrophy(trophyVector, name);

	if (trophyPosition != -1)
	{
		vector<Trophy*>::iterator it = trophyVector.begin() + trophyPosition;
		trophyVector[trophyPosition]->~Trophy();
		trophyVector.erase(it);
	}
}

// copyTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies we'll modify
// Return Value:
//      void
// Description:
//      Searches for the index of the trophy we need to copy using searchForTrophy(),
//		and if it is found, copies that trophy and adds it to the back of the vector
void copyTrophy(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to copy an existing trophy." << endl;
	string name = promptForString(PROMPT_FOR_NAME);
	int trophyPosition = searchForTrophy(trophyVector, name);

	if (trophyPosition != -1)
	{
		Trophy* trophyToCopy = new Trophy(*trophyVector[trophyPosition]);
		trophyVector.push_back(trophyToCopy);
	}
}

// renameTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies we'll modify
// Return Value:
//      void
// Description:
//      Searches for the index of the trophy we want to rename, and if it is found,
//		prompts the user for a new name and sets it to be the new name of the trophy
void renameTrophy(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to rename an existing trophy." << endl;
	string name = promptForString(PROMPT_FOR_NAME);
	int trophyPosition = searchForTrophy(trophyVector, name);

	if (trophyPosition != -1)
	{
		string newName = promptForString("Please enter the new name of the Trophy");
		trophyVector[trophyPosition]->SetName(newName);
	}
}

// relevelTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies we'll modify
// Return Value:
//      void
// Description:
//      Searches for the index of the trophy we want to relevel, and if it is found,
//		prompts the user for a new level and sets it to be the new level of the trophy
void relevelTrophy(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to change the level of an existing trophy." << endl;
	string name = promptForString(PROMPT_FOR_NAME);
	int trophyPosition = searchForTrophy(trophyVector, name);

	if (trophyPosition != -1)
	{
		int newLevel = promptForInt(PROMPT_FOR_LEVEL, 1, 10);
		trophyVector[trophyPosition]->SetLevel(newLevel);
	}
}

// recolorTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies we'll modify
// Return Value:
//      void
// Description:
//      Searches for the index of the trophy we want to recolor, and if it is found,
//		prompts the user for a new color and sets it to be the new color of the trophy
void recolorTrophy(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to change the color of an existing trophy." << endl;
	string name = promptForString(PROMPT_FOR_NAME);
	int trophyPosition = searchForTrophy(trophyVector, name);

	if (trophyPosition != -1)
	{
		TrophyColor newColor = promptForColor(PROMPT_FOR_COLOR);
		trophyVector[trophyPosition]->SetColor(newColor);
	}
}

// printTrophies()
// Parameters:
//      vector<Trophy>& trophyVector - The refereced vector of trophies
// Return Value:
//      void
// Description:
//      Calls the Print() function for every trophy in the vector
void printTrophies(vector<Trophy*>& trophyVector)
{
	cout << "You have chosen to print all of the trophies." << endl;
	for (int i = 0; i < trophyVector.size(); i++)
	{
		trophyVector[i]->Print();
	}
}

// promptForTrophy()
// Parameters:
//      none
// Return Value:
//      Trophy* - returns a pointer to a Trophy object
// Description:
//      Prompts the user for each value the trophy needs, creates a
//		pointer to a trophy object based on that input, returns that
//		trophy, and then deletes it from memory
Trophy* promptForTrophy()
{
	string name = promptForString(PROMPT_FOR_NAME);
	int level = promptForInt(PROMPT_FOR_LEVEL, 1, 10);
	TrophyColor color = promptForColor(PROMPT_FOR_COLOR);

	Trophy* newTrophy = new Trophy(name, level, color);

	return newTrophy;

	newTrophy->~Trophy();
}

// promptForString()
// Parameters:
//      const string& message - the string we'll print to the user
// Return Value:
//      string - the validated string the user enters
// Description:
//      Prompts the user for a string, validates the string (checks to ensure
//		it is not the empty string) and then returns that string
string promptForString(const string& message)
{
	string userString = "";		// Will store the user's string

	cout << message << endl;
	getline(cin, userString);

	// While the user hasn't entered anything, keep prompting
	while (userString == "")
	{
		cout << "That is not a valid name.  Try again.";
		getline(cin, userString);
	}

	// Return the validated entry
	return userString;
}

// promptForInt()
// Parameters:
//      const string& message - the string we'll print to the user
//		int minimum - the minimum value they can enter
//		int maximum - the maximum value they can enter
// Return Value:
//      int - the validated int the user enters
// Description:
//      Prompts the user for an integer, validates that it is between the right
//		min and max value, and then returns that int
int promptForInt(const string& message, int minimum, int maximum)
{
	string userInput = "";	// Will store whatever thing the user enters
	int userInt = 0;		// Will store the user's converted input

	// Prompt the user for an int value and pull in whatever they enter
	cout << message << endl;
	getline(cin, userInput);

	// Try converting that value to an int. If an exception is thrown,
	// then set userInt to a value outside the acceptable range so they
	// will be prompted again
	try
	{
		userInt = stoi(userInput);
	}
	catch (exception& e)
	{
		userInt = minimum - 1;
	}

	// While the user has entered an unacceptable value, keep prompting
	while (userInt < minimum || userInt > maximum)
	{
		cout << "That value is outside the acceptable range.  Try again." << endl;
		getline(cin, userInput);

		// Same error catch as above
		try
		{
			userInt = stoi(userInput);
		}
		catch (exception & e)
		{
			userInt = minimum - 1;
		}
	}

	// Return the validated entry
	return userInt;
}

// stringToUpper()
// Parameters:
//      string value - the string we'll be modifying
// Return Value:
//      string - the modified string
// Description:
//      Prompts the user for a string, and then iterates through each
//		character and makes sure it is upper case
string stringToUpper(string value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = toupper(value[i]);
	}

	return value;
}

// promptForColor()
// Parameters:
//      const string& message - the string we'll print to the user
// Return Value:
//      TrophyColor - the color enum version of what the user entered
// Description:
//      Prompts the user for a color, converts the string they enter to upper case,
//		and then checks to ensure it is a valid color. If it is, return the TrophyColor
//		enum version of the string
TrophyColor promptForColor(const string& message)
{
	TrophyColor color = BRONZE;		// Variable for the color we're converting to
	string value = "";				// Stores the string the user enters
	cout << message << endl;

	// We'll always want to get their input at least once
	do
	{
		// Take in the user's input
		getline(cin, value);

		// Everything from here is case insensitive
		value = stringToUpper(value);

		// If it's a correct value, change the color enum to match what the user entered
		if (value == "BRONZE" || value == "SILVER" || value == "GOLD")
		{
			if (value == "BRONZE")
			{
				color = BRONZE;
			}

			else if (value == "SILVER")
			{
				color = SILVER;
			}

			else
			{
				color = GOLD;
			}

		}

		// Otherwise, print this error and go again
		else
		{
			cout << "That is not an acceptable color.  Try again." << endl;
		}
	} while (value != "BRONZE" && value != "SILVER" && value != "GOLD");

	// Return the corresponding correct enum
	return color;
}

// searchForTrophy()
// Parameters:
//      vector<Trophy>& trophyVector - the vector of trophies we'll be searching
//		string name - the name of the trophy we're searching for
// Return Value:
//      int - the index of the trophy, if we find it (-1 if not)
// Description:
//      Prompts the user for the name of a trophy, and searches our vector for a trophy
//		with that name. If we find it, returns the index. If not, returns -1
int searchForTrophy(vector<Trophy*>& trophyVector, string name)
{
	vector<Trophy*>::iterator it = trophyVector.begin();	// Initialize our iterator
	int position = 0;									// Initialize our position

	// Stop when we've reached the end of the vector or we've found the right trophy name
	while (it != trophyVector.end() && trophyVector[position]->GetName() != name)
	{
		++it;
		++position;
	}

	// If we're not at the end of the vector, then we've found the position, so return it
	if (it != trophyVector.end())
	{
		return position;
	}

	// If the trophy was not found, print this error, return -1
	cout << "ERROR: The Trophy was not found" << endl;
	return -1;
}