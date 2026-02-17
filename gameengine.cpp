/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*
*/

#include "gameengine.hh"

GameEngine::GameEngine(int pairs_amount,
                       int players_amount,
                       string player_names):
    pairs_amount_(pairs_amount),
    players_amount_(players_amount),
    player_names_(player_names)
{
    create_players();
}

void GameEngine::create_players()
{
    vector<string> names;
    names = split(player_names_);

    int name_amount = names.size();

    // Checks if the correct amount of names was given
    if ( name_amount != players_amount_ ) {
        // If not, give the players generic names
        names.clear();
        for ( int i = 0; i != players_amount_; ++i ) {
            string name = "Player " + to_string(i+1);
            names.push_back(name);
        }
    }

    // Create a vector containing the player objects
    for ( int i = 0; i != players_amount_; ++i) {
        string name = names.at(i);
        Player new_player(name);
        players_.push_back(new_player);
    }

    // The first player gets the first turn
    current_player_ = &players_.at(0);
}

int GameEngine::get_pairs_of_current() const
{
    return pairs_amount_;
}

int GameEngine::get_player_amount() const
{
    return players_amount_;
}

string GameEngine::get_current_player_info() const
{
    string info = current_player_->get_player_name() + " with " +
                  to_string(current_player_->get_player_pairs()) + " pairs";
    return info;
}

string GameEngine::check_winner()
{
    unsigned int highest_points = 0;
    int ties_between = 0;
    Player* current_leader = &players_.at(0);

    // Checks who has the highest points, and how many points they have.
    for ( Player& current : players_ ) {
        if ( current.get_player_pairs() > highest_points ) {
            current_leader = &current;
            highest_points = current.get_player_pairs();
        }
    }

    // Checks if multiple people have the amount of highest points.
    // Every "winner" adds 1 to the ties_between counter.
    for ( Player& current : players_ ) {
        if ( current.get_player_pairs() == highest_points ) {
            ++ties_between;
        }
    }

    if ( ties_between > 1) {
        return "It's a tie between " + to_string(ties_between) + " players, "
               "together you found all the pairs!";
    }

    return current_leader->get_player_name() + " wins the game with " +
           to_string(highest_points) + " pairs!";
}

bool GameEngine::add_point()
{
    // Add point to the player and to the total amount of collected pairs
    current_player_->add_pair_to_player();
    ++pairs_collected_;

    // Check if it was the last pair
    return pairs_collected_ == pairs_amount_;
}

int GameEngine::calculate_factors() const
{
    int cards_amount = pairs_amount_ * 2;
    int square = sqrt(cards_amount);

    while (((cards_amount / square) * square != cards_amount )) {
        --square;
    }
    return cards_amount / square;
}

void GameEngine::change_turn()
{
    ++turn_counter_;
    // If it was the last players turn, return to the first player
    if (turn_counter_ == players_amount_) {
        turn_counter_ = 0;
    }
    current_player_ = &players_.at(turn_counter_);
}

vector<string> GameEngine::split(string to_split) {
    vector<string> parts;
    string temp;

    for ( char x : to_split ) {
        if ( x == ',' ) {
            parts.push_back(temp);
            temp.clear();
        }
        else {
            temp.push_back(x);
        }
    }
    parts.push_back(temp);
    return parts;
}

