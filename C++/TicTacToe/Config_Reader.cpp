#include <fstream>
#include <sstream>
#include <iostream>

#include "Config_Reader.h"

//Read & Parse config.txt file
Config::Config()
{
	string line;
	// WRITE CONTENT =====================================================================
	ifstream fin("config.txt");

	getline(fin, line);

	if (fin.is_open() == false || line != "Game: TIC-TAC-TOE - Jordan Rosenberg - " + version_and_date)
	{
		fin.close();
		cout << "\a(...Failed to validate configuration file. A new one has been created.)\n" << endl;

		ofstream OutputFile("config.txt");

		OutputFile << "Game: TIC-TAC-TOE - Jordan Rosenberg - " << version_and_date << endl;
		OutputFile << endl;
		OutputFile << "[If you want to restore this configuration file to default" << endl;
		OutputFile << "settings, all you have to do is delete the configuration file," << endl;
		OutputFile << "run the program, and it will generate a fresh new copy for you.]" << endl;
		OutputFile << endl;
		OutputFile << "You may edit either Player Name here." << endl;
		OutputFile << "NOTE: Names are limited to 1 character ONLY." << endl;
		OutputFile << "----------------------------------------------------------------" << endl;
		OutputFile << endl;
		OutputFile << endl;
		OutputFile << endl;
		OutputFile << "Player 1 = X" << endl;
		OutputFile << "Player 2 = O" << endl;
		
		OutputFile.close();
		fin.open("config.txt");
	}


	// READ CONTENT =================================================================
	while (getline(fin, line)) 
	{
		/*
		Parses each line in a while loop... Example: "setName = Bob" -> "B" 
		The purpose of this specific parse is because I only allow a single letter to be
		customized so it won't spam up/ruin the board's display frame and stretch it weirdly.
		
		If you want to allow future full/unlimited names, remove the ", 2" from the parameter below
		(including that comma)

		// istringstream sin(line.substr(line.find("=") + 1, 2));

		*/

		istringstream sin(line.substr(line.find("=") + 1));

		if (line.find("Player 1") != -1)
			sin >> str_Player_1;

		else if (line.find("Player 2") != -1)
			sin >> str_Player_2;
	}

	fin.close();

}
