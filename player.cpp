
/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*/

#include "player.hh"

Player::Player(const std::string& player_name):
    name_(player_name), pairs_(0)
{

}

std::string Player::get_player_name() const
{
    return name_;
}

unsigned int Player::get_player_pairs() const
{
    return pairs_;
}

void Player::add_pair_to_player()
{
    pairs_ += 1;
}
