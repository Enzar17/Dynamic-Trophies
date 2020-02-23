#pragma once

// Guard the header
#ifndef TROPHY_H
#define TROPHY_H

// include the libraries this class will need
#include <string>

using namespace std;

enum TrophyColor { BRONZE, SILVER, GOLD };	// Defines the type of our trophy

class Trophy
{
	// Public methods
public:
	// Constructors
	Trophy();
	Trophy(string name, int level, TrophyColor color);
	Trophy(const Trophy& trophy);

	// Destructor
	~Trophy();

	// Getters
	const string GetName();
	const int GetLevel();
	const TrophyColor GetColor();

	// Setters
	void SetName(string name);
	void SetLevel(int level);
	void SetColor(TrophyColor color);

	// Print information to the console
	const void Print();

	// Override the = operator to get a deep copy for the copy constructor
	Trophy& operator= (const Trophy& trophy);

	// Private members
private:
	string* m_name;			// The name of the trophy
	int* m_level;			// The level value of the trophy (1 - 10)
	TrophyColor* m_color;	// The color of the trohpy
};

#endif