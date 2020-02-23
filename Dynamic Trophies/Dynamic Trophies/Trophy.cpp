#include "Trophy.h"
#include <iostream>

using namespace std;

// Default constructor
Trophy::Trophy()
{
	m_name = new string("");
	m_level = new int(1);
	m_color = new TrophyColor(BRONZE);
}

// Override constructor with details
Trophy::Trophy(string name, int level, TrophyColor color)
{
	m_name = new string(name);
	m_level = new int(level);
	m_color = new TrophyColor(color);
}

// Copy constructor (create a duplicate of an existing trophy object)
Trophy::Trophy(const Trophy& trophy)
{
	m_name = new string(*trophy.m_name);
	m_level = new int(*trophy.m_level);
	m_color = new TrophyColor(*trophy.m_color);
}

// Destructor
Trophy::~Trophy()
{
	// Delete all dynamic data members
	delete m_name;
	delete m_level;
	delete m_color;

	// Set all their pointers to a safe value
	m_name = NULL;
	m_level = NULL;
	m_color = NULL;
}

// GetName()
// Parameters:
//      none
// Return Value:
//      string - the value of m_name
// Description:
//      returns m_name
const string Trophy::GetName()
{
	return *m_name;
}

// GetLevel()
// Parameters:
//      none
// Return Value:
//      int - the value of m_level
// Description:
//      returns m_level
const int Trophy::GetLevel()
{
	return *m_level;
}

// GetColor()
// Parameters:
//      none
// Return Value:
//      TrophyColor - the value of m_color
// Description:
//      returns m_color
const TrophyColor Trophy::GetColor()
{
	return *m_color;
}

// SetName()
// Parameters:
//      string name - the name to which we're setting m_name
// Return Value:
//      void
// Description:
//      sets the value of m_name
void Trophy::SetName(string name)
{
	*m_name = name;
}

// SetLevel()
// Parameters:
//      int level - the level to which we're setting m_level
// Return Value:
//      void
// Description:
//      sets the value of m_level
void Trophy::SetLevel(int level)
{
	*m_level = level;
}

// SetColor()
// Parameters:
//      TrophyColor color - the enum value to which we're setting m_color
// Return Value:
//      void
// Description:
//      sets the value of m_color
void Trophy::SetColor(TrophyColor color)
{
	*m_color = color;
}

// Print()
// Parameters:
//      none
// Return Value:
//      void
// Description:
//      Converts m_color to a user-friendly string, and then prints out
//		the values of m_name, m_level, and m_color in a nice, organized way
const void Trophy::Print()
{
	string color = "";		// We'll use this to convert the enum to a string

	// Get a string version of our enumerated color value
	switch (GetColor())
	{
	case BRONZE:
		color = "BRONZE";
		break;

	case SILVER:
		color = "SILVER";
		break;

	case GOLD:
		color = "GOLD";
		break;
	}

	// Print a formatted string [ name : level : color ]
	cout << "[ " << GetName() << " : " << GetLevel() << " : " << color << " ]" << endl;
}

// operator=
// Parameters:
//      const Trophy& trophy - the trophy object from which we're copying
// Return Value:
//      *this - returns values to the copy constructor instead of making it point
//				to the same memory location as the first trophy
// Description:
//      Overrides the = operator to allow a deep copy of dynamic data from one
//		trophy object to another.
Trophy& Trophy::operator= (const Trophy& trophy)
{
	*m_name = *trophy.m_name;
	*m_level = *trophy.m_level;
	*m_color = *trophy.m_color;

	return *this;
}