#include "board.h"

void Board::displayBoard(string table[3][3])
{
	cout << "Game: TIC-TAC-TOE - Jordan Rosenberg - " << config.version_and_date << " \n" << endl;
	cout << "\n\t ---------------------" << endl;
	cout << "\t| {" << table[0][0] << "} ~-~ {" << table[0][1] << "} ~-~ {" << table[0][2] << "} |" << endl;
	cout << "\t| -=-=-=-=-=-=-=-=-=- |" << endl;
	cout << "\t| {" << table[1][0] << "} ~-~ {" << table[1][1] << "} ~-~ {" << table[1][2] << "} |" << endl;
	cout << "\t| -=-=-=-=-=-=-=-=-=- |" << endl;
	cout << "\t| {" << table[2][0] << "} ~-~ {" << table[2][1] << "} ~-~ {" << table[2][2] << "} |" << endl;
	cout << "\t ---------------------\n" << endl;
}

// TODO: If both players have the same first letter in their name,
// capitalize one of them to distinct between the two.
string Board::player_NameChecker(string pName)
{
	if (pName.length() > 1)
	{
		pName = pName.substr(0, 1);
		cout << "\a** \"" << pName << "\" is too long for a name in this game. Shortened to \"" << pName << "\". " << endl;
	}

	return pName;
}

Player Board::getTurn() const
{
	return playerTurn;
}

void Board::setTurn(Player TURN)
{
	playerTurn = TURN;
}

bool Board::getDraw() const
{
	return draw;
}

void Board::flipTurn()
{
	playerFlip = !playerFlip; // Small bool toggle for switching sides

	if (playerFlip == 1)
	{
		cout << "\n\n* \"" << Player_1 << "\" moves first! \n" << endl;
		playerTurn = Player_1;
	}

	else if (playerFlip == 0)
	{
		cout << "\n\n* \"" << Player_2 << "\" moves first! \n" << endl;
		playerTurn = Player_2;
	}

}

void Board::playerTurn_Logic(string table[3][3])
{

	int choice;

	int row = 0, column = 0;

	if (playerTurn == Player_1)
	{
		cout << "\n\tPlayer \""<<Player_1<<"\" Turn" << endl;
	}

	else if (playerTurn == Player_2)
	{
		cout << "\n\tPlayer \""<<Player_2<<"\" Turn" << endl;
	}

	cout << "\tPlayer [" << playerTurn << "]: Choose A Cell: ";
	cin >> choice;

	switch (choice)
	{
	case 1: row = 0; column = 0; break;
	case 2: row = 0; column = 1; break;
	case 3: row = 0; column = 2; break;
	case 4: row = 1; column = 0; break;
	case 5: row = 1; column = 1; break;
	case 6: row = 1; column = 2; break;
	case 7: row = 2; column = 0; break;
	case 8: row = 2; column = 1; break;
	case 9: row = 2; column = 2; break;

	default:
		system("cls");
		displayBoard(table);
		cout << "\tYou didn't select the correct number! Try again..." << endl;
		playerTurn_Logic(table); // Calls & Starts the function over again and overwrites its data.
	}
	
	if (playerTurn == Player_1 && table[row][column] != Player_1.getName() && table[row][column] != Player_2.getName())
	{
		table[row][column] = Player_1.getName();
		playerTurn = Player_2;
	}
	else if (playerTurn == Player_2 && table[row][column] != Player_2.getName() && table[row][column] != Player_1.getName())
	{
		table[row][column] = Player_2.getName();
		playerTurn = Player_1;
	}

	else
	{
		system("cls");
		displayBoard(table);
		cout << "\a\tThe cell you've chosen is used. Try again!" << endl;
		playerTurn_Logic(table); // Calls & Starts the function over again and overwrites its data.
	}

}

bool Board::Gameover(string table[3][3])
{

	for (int i = 0; i < 3; i++) // Check for a win
	{
		//Checks for horizontal, verticle, and diagonal
		if ((table[i][0] == table[i][1] && table[i][1] == table[i][2]) || (table[0][i] == table[1][i] && table[1][i] == table[2][i]) || (table[0][0] == table[1][1] && table[1][1] == table[2][2]) || (table[0][2] == table[1][1] && table[1][1] == table[2][0]))
		{	
			return true; // Only needs to be true for one of these cases
		}

	}

	for (int i = 0; i < 3; i++) // Check for draw
	{
		for (int j = 0; j < 3; j++)
		{
			if (table[i][j] != Player_1.getName() && table[i][j] != Player_2.getName())
			{
				return false;
			}
		}
	}

	draw = true;
	return true;

}

void Board::Core()
{
	// string table[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' }; Same thing.

	string table[3][3] =
	{
		{ "1", "2", "3" },
		{ "4", "5", "6" },
		{ "7", "8", "9" }
	};

	cout << "Game: TIC-TAC-TOE - Jordan Rosenberg - " << config.version_and_date << " \n" << endl;

	Player_1.setName(player_NameChecker(Player_1.getName()));
	Player_2.setName(player_NameChecker(Player_2.getName()));

	setTurn(Player_1); // Manually pre-set to Player 1.

	int user_input;
	bool continueLoop = true;

	cout << "* \"" << Player_1.getName() << "\" moves first! \n" << endl;

	do {
		cout << "[1]: \'Swap\' order" << endl;
		cout << "[2]:  START" << endl;
		cout << "\nINPUT: -> ";
		cin >> user_input;

		switch (user_input)
		{
		case 1:
			system("cls");
			cout << "Game: TIC-TAC-TOE - Jordan Rosenberg - " << config.version_and_date << " \n";
			flipTurn();
			break;
		case 2:
			continueLoop = false;
			break;
		default:
			system("cls");
			cout << "Game: TIC-TAC-TOE - Jordan Rosenberg - " << config.version_and_date << " \n";
			cout << "\a\n\nERROR: Wrong choice. Try again!\n" << endl;
		}

	} while (continueLoop);

	while (!Gameover(table))
	{
		system("cls");
		displayBoard(table);
		playerTurn_Logic(table);
		Gameover(table);
	}

	// Update the board one last time for 'end-game' results
	displayBoard(table);

	if (playerTurn == Player_2 && !draw)
	{
		system("cls");
		displayBoard(table);
		cout << "\n\tPlayer [" << Player_1.getName() << "] Wins! Game Over!" << endl;
	}

	else if (playerTurn == Player_1 && !draw)
	{
		system("cls");
		displayBoard(table);
		cout << "\n\tPlayer [" << Player_2.getName() << "] Wins! Game Over!" << endl;
	}

	else
	{
		system("cls");
		displayBoard(table);
		cout << "\n\tIt's a draw! Game Over!" << endl;
	}
}

void Board::Run()
{

	int user_input;
	bool continueLoop = true;

	do {
		cout << "[1]: Player vs Player" << endl;
		cout << "[2]: Player vs Computer" << endl;
		cout << "[3]: Computer vs Computer" << endl;
		cout << "\nINPUT: -> ";
		cin >> user_input;

		switch (user_input)
		{
		case 1:
		{

			Player_1.set_isAI(false);
			Player_2.set_isAI(false);

			Core();

			continueLoop = false;
			break;
		}
		case 2:
		{
			Player_1.set_isAI(false);
			Player_2.set_isAI(true);

			Core();

			continueLoop = false;
			break;
		}
		case 3:
		{
			Player_1.set_isAI(true);
			Player_2.set_isAI(true);

			Core();
			
			continueLoop = false;
			break;
		}
		default:
			system("cls");
			cout << "Game: TIC-TAC-TOE - Jordan Rosenberg - " << config.version_and_date << " \n";
			cout << "\a\n\nERROR: Wrong choice. Try again!\n" << endl;
		}

	} while (continueLoop);

}

Board::~Board()
{

}

bool operator==(const Player& lhs, const Player& rhs)
{
	return operator==(lhs.getName(), rhs.getName());
}

bool operator!=(const Player& lhs, const Player& rhs)
{
	return !operator==(lhs.getName(), rhs.getName());
}

ostream& operator<<(ostream& os, const Player& Ply)
{
	os << Ply.getName();
	return os;
}