#include "Player.h"

string Player::getName() const
{
	return name;
}

void Player::setName(const string pName)
{
	name = pName;
}

bool Player::get_isAI() const
{
	return is_AI;
}

void Player::set_isAI(const bool pIs_AI)
{
	is_AI = pIs_AI;
}

void Player::Logic()
{


}