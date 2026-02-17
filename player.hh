
/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*
* COMP.CS.110 K2021
*
* Represents a single player in pairs (memory) game.
* The player can have a name and points.
*
*
*
*/

#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
#include <iostream>

class Player
{
public:

    /**
    Constructor: creates a player with the given name.
    @return none
    */
    Player(const std::string& player_name);

    /**
    Returns the players name from the name_ attribute
    @return string, players name
    */
    std::string get_player_name() const;


    /**
    Returns the number of pairs collected by the player so far
    @return unsigned int, number of pairs collected
    */
    unsigned int get_player_pairs() const;

    /**
    Gives a "point" to the player which in this case is a pair
    @return none
    */
    void add_pair_to_player();

private:

    // The name of the player.
    std::string name_;

    // The amount of pairs (points) the player has.
    double pairs_;

};

#endif // PLAYER_HH
