/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*
* COMP.CS.110 K2021
*
* Class for creating our Graphical User Interface, a QT program.
* Mostly works with buttons that call methods that affect the boxes and other
* buttons.
*
* More info in documentation.
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QString>
#include "gameengine.hh"
#include <QPushButton>
#include <algorithm>
#include <QTimer>
#include <QGridLayout>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    // Adds 1 every second to the timer
    void timer_timeout();

    // Calls start_game()
    void on_startButton_clicked();

    // Changes players_ value
    void on_playersSpin_valueChanged(int arg1);

    // Changes pairs_ value
    void on_pairsSpin_valueChanged(int arg1);

    // Changes player_names_ string value
    void on_nameEdit_textChanged(const QString &arg1);

    // Calls new_game();
    void on_newButton_pressed();

private:
    Ui::MainWindow *ui;

    // Starts the timer, creates the GameEngine object, calls init_buttons
    void start_game();

    // Nulls the neccessary attributes and calls init_greetings to start the
    // game again
    void new_game();

    // Enables the greeting page and the input boxes
    void init_greetings();


    // Calls the methods below to create and insert the buttons to the grid
    void init_buttons();

    // Creates the buttons
    void create_buttons();

    // Adds the buttons to the grid
    void add_buttons_to_grid();


    // Hides the card buttons and shows the winner screen
    void init_congrats();

    // Updates the label where the current player is displayed
    void round_update();

    // Called when a cardbutton is pressed, disables it's signals and checks
    // if it was the first or the second card to be pressed, calls
    // two_buttons_pressed() if neccessary
    void card_pressed();

    // Checks if the cards are a pair, adds points to the player if they are
    // and checks for game ending, changes turns if they are not
    void two_buttons_pressed();



    // Loads the .png images into vector<QPixmap> icons_
    void load_icons();

    // The width of the grid where the cardbuttons are placed, neccessary to
    // calculate the width of a single button so they fit nice and tight
    const int GRIDWIDTH = 730;

    // The values used to initialize the GameEngine, default values for if the
    // user does not wish to make any changes
    int pairs_ = 1;
    int players_ = 2;
    QString player_names_ = "";

    // A pointer to the GameEngine_ object that runs in the back, containing
    // info about the players and their points
    GameEngine* GameEngine_ = nullptr;

    // A vector containing the cardbuttons, useful when they need to be deleted
    // at the end of a game
    vector<QPushButton*> cardbuttons_;

    // A vector containing the one/two pressed buttons so that they can be
    // compared if their id's (texts) match
    vector<QPushButton*> pressed_buttons_;

    // A vector containing all the cat pictures
    vector<QPixmap> icons_;

    // The width of the buttons, as in 20 buttons will be 5 by width
    // and 4 by heigth, but the width is enough to know
    int width_;

    // The size of a single button, being a square
    int boxsize_;
    QTimer* timer_;




};
#endif // MAINWINDOW_HH
