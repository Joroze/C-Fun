#pragma once

#include <string>
using namespace std;

class Config
{
	friend class Board;
	friend class Player;

private:

	string str_Player_1; // to read P1 string
	string str_Player_2; // to read P2 string

public:

	Config(); // Default Constructor -> Reads from the 'config.txt' file

	string version_and_date = "(5/25/15) v.1.6";

};