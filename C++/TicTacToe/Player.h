#pragma once
#include "Config_Reader.h"

class Player
{
protected:

	Config config;

	string name;
	bool is_AI;

public:

	string getName() const;
	void setName(const string);

	bool get_isAI() const;
	void set_isAI(const bool);

	void Logic();


};
