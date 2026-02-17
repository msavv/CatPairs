/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*
* COMP.CS.110 K2021
*
* Class for defining a GameEngine necessary for this program, mostly to handle
* players and their points.
*/

#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "player.hh"
#include <iostream>
#include <vector>
#include <random>
#include <QTime>
#include <math.h>

using namespace std;

class GameEngine
{
public:
    GameEngine( int pairs_amount, int players_amount, string player_names);

    /**
    Creates the given amount of player-objects and saves them into a vector.
    Names the objects Player X or by real names, if the user has given them.
    @param none (Uses the attributes of the GameEngine object)
    @return none
    */
    void create_players();

    /**
    @return int, the amount of pairs of the current player in turn
    */
    int get_pairs_of_current() const;

    /**
    @return int, the amount of player-objects that the GameEngine contains
    */
    int get_player_amount() const;

    /**
    Returns a printable sentence of the current players name and points
    @return string, the sentence as string
    */
    string get_current_player_info() const;

    /**
    Counts the amount of points each player has, and such determines the winner
    or the possible tie-situation and by how many players it is a tie
    @return string, the winner-message or the tie-message to be "printed"
    */
    string check_winner();

    /**
    Adds a point to the current player and checks if they got the last pair
    @return bool, true if it was the last pair, false if not
    */
    bool add_point();

    /**
    Calculates the closest factors of the amount of cards necessary to print,
    so we can get the width of the grid to be printed
    @return int, the bigger factors (enough for our use in the mainwindow
    */
    int calculate_factors() const;

    /**
    Changes the current_player_ pointer to point to the next player in turn
    using the players_ vector
    @return none
    */
    void change_turn();

    /**
    Splits a string into parts by the separator character, and saves them into
    a vector
    @return vector<string>, vector of the strings split parts
    */
    vector<string> split(string to_split);







private:
    // The amount of pairs needed for this run of the game
    int pairs_amount_;

    // The amount of players needed for this run of the game
    int players_amount_;

    // The amount of pairs collected in whole, so we can know when all the pairs
    // have been collected
    int pairs_collected_ = 0;

    // An integer that keeps track of whose turn it is, used in the change_turn
    // function
    int turn_counter_ = 0;

    // The names of the players the user has given. If empty, the players are
    // given generic Player 0 etc. names
    string player_names_;

    // A pointer pointing to the current player in turn
    Player* current_player_;

    // A vector containing the players
    vector<Player> players_;


};

#endif // GAMEENGINE_HH
