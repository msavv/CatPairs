/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*
*
* This is a game where you can select the number of players from 2 to 20,
* and the number of cards from 1 (why would you) to 20.
* You can also name yourselves! If you don't want to, you will get
* generic Player 1, Player 2, etc. names.
* When you have chosen the number of players, cards and your names, you can start the game.
*
* More documentation in instructions.txt
*/

#include "mainwindow.hh"

#include <QApplication>




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
