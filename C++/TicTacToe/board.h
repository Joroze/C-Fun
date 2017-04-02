#pragma once

#include "Config_Reader.h"
#include <iostream>

#include "Player.h"
using namespace std;

class Board
{

private:

	// Loads up 'config.txt' file --------><
	Config config; 


	Player Player_1;
	Player Player_2;

	// This function checks to see if a player name length is capped.
	string player_NameChecker(string);
	//------------------------------------><

	Player playerTurn;
	//string turn; // You can also use bool for true/false if it's X's turn or not.
	
	bool playerFlip = true; // Variable used for Player-Turn-Swap toggling.
	void flipTurn();		// Player-Turn-Swap Toggle Function.

	bool draw = false; // bool flag (if a game is a draw or not).

	void displayBoard(string[3][3]); // Displays the board 
	void playerTurn_Logic(string[3][3]);   // Player Turn logic
	bool Gameover(string[3][3]);     // Gameover logic
	
public:
	
	Player getTurn() const; // GET Turn (string).
	bool getDraw() const;   // GET Draw (bool).

	void setTurn(Player); // SET Turn (string).

	void Core(); // Core function that runs the game. Should probably be renamed to 'void Run();'

	void Run();

	~Board(); // Empty destructor


};

inline bool operator == (const Player& lhs, const Player& rhs);

inline bool operator != (const Player& lhs, const Player& rhs);

inline ostream& operator<<(ostream& os, const Player& Ply);