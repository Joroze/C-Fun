#include "board.h"
#include <thread>

// TIC_TAC_TOE - Jordan Rosenberg

int main()
{

	int restartChoice; // Choice for Restart/Quit of the game
	bool done = false; // Game restart confirmation

	Board *Game; // Game pointer

	do
	{
		Game = new Board; // Dynamically allocate/create a board.
		Game->Core(); // Accessing its core function to run

		cout << "\n\tWould you like to play again?\n\t[1] YES\n\t[2] NO (Quit)\n\n\t-> ";
		cin >> restartChoice;

		switch (restartChoice)
		{
			case 1: // "Resets" the game by deleting the pointer, and breaks.
			{       // This way, a new game is dyn. allocated/made from the loop
				system("cls");
				delete Game;
				break;
			}
			case 2: // Frees memory, disables loop, and breaks.
			{
				delete Game;
				for (int i = 3; i >= 0; i--)
				{
					system("cls");
					cout << "\n\n\n\t\t\tQuit confirmed.\n\n\t\t\tTerminating in " << i << ". . ." << endl;
					this_thread::sleep_for(chrono::seconds(1));
				}
				done = true;
				break;
			}

		}

	} while (!done);

	return 0;
}