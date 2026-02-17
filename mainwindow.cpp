/*
* Program author
* Name: Markus Savvakis
* Student number: H291753
* UserID: snmasa
* E-Mail: markus.savvakis@tuni.fi
*/

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer_(new QTimer(this))
{
    ui->setupUi(this);

    connect(timer_, &QTimer::timeout, this, &MainWindow::timer_timeout);

    load_icons();
    init_greetings();
}

MainWindow::~MainWindow()
{
    delete GameEngine_;
    delete ui;
}

void MainWindow::init_greetings()
{
    // Here we insert a cat picture, null the clock and welcome the player
    ui->catLabel2->setPixmap(icons_.at(0).scaled(300,300));
    ui->lcdNumberSec->display(0);
    ui->statusLabel->setText("Welcome!");
    ui->currentLabel->setText("Waiting for players");

    // Enable the start button, show the greetingsBox, hide other boxes
    ui->startButton->setDisabled(false);
    ui->buttonBox->setHidden(true);
    ui->congratsBox->setHidden(true);
    ui->greetingsBox->setHidden(false);
}

void MainWindow::start_game()
{
    // Start the clock, hide te previous greetingsBox
    timer_->start(1000);
    ui->greetingsBox->setHidden(true);

    // Initialize the GameEngine object
    string names = player_names_.toStdString();
    GameEngine_ = new GameEngine(pairs_, players_, names);

    // Disable start button, update the status label and call init_buttons()
    ui->startButton->setDisabled(true);
    round_update();
    return init_buttons();
}

void MainWindow::on_startButton_clicked()
{
    return start_game();
}

void MainWindow::create_buttons() {

    // We use the GameEngines function to get the bigger close factorial which
    // will be our grids width
    width_ = GameEngine_->calculate_factors();
    int boxside = 0;

    // The width_*10 is for the space between the buttons, and the remaining
    // space is shared for the buttons of the row
    boxside = ( GRIDWIDTH - width_*10 ) / width_;
    QSize boxsize_ = QSize( boxside, boxside );

    // Go through the pairs
    for ( int i = 1; i <= pairs_; ++i) {

        // Create 2 buttons for each pair
        for ( int y = 0; y != 2; ++y) {

            // Create the button, set its ID as 1px invisible text, make it the
            // correct size, give it the backside icon, connect it to its slot
            QPushButton* new_button = new QPushButton("", this);
            new_button->setText(QString::number(i));
            new_button->setStyleSheet("font-size: 1px;");
            new_button->setFixedSize(boxsize_);
            new_button->setIconSize(boxsize_);
            new_button->setIcon(icons_.at(0));
            connect(new_button, &QPushButton::clicked,
                    this, &MainWindow::card_pressed);

            // Add the pointer to the cardbuttons_ vector
            cardbuttons_.push_back(new_button);
        }

    }
}

void MainWindow::add_buttons_to_grid() {
    // Start at (1,1)
    int row = 1;
    int column = 1;

    // Go through the buttons
    for ( QPushButton* new_button : cardbuttons_ ) {
        // Check if a new row is needed
        if (column > width_) {
            column = 1;
            ++row;
        }

        // Insert the button to the grid, move forwards on the column
        ui->buttonGrid->addWidget(new_button, row, column);
        ++column;
    }
}

void MainWindow::init_buttons() {

    // Create the buttons
    create_buttons();

    // Shuffle the buttons so that they will be in random order
    random_shuffle( cardbuttons_.begin(), cardbuttons_.end() );

    // Add the buttons to the grid
    add_buttons_to_grid();

    // Make the buttonBox visible
    ui->buttonBox->setHidden(false);
}

void MainWindow::card_pressed() {

    // Get pointer of the button that was pressed, block new game button
    // as it might cause an error if pressed while on the timeout
    QPushButton* button = static_cast<QPushButton*>(sender());
    ui->newButton->blockSignals(true);

    // Get the buttons id, set the correct icon,
    // block pressing the same button again, add to pressed_buttons_
    int button_id = button->text().toInt();
    button->setIcon(icons_.at(button_id));
    button->blockSignals(true);
    pressed_buttons_.push_back(button);

    // Check if 2 have been pressed, block all other buttons and have a delay
    // if true, so that the user can view the cards, call two_buttons_pressed()
    if ( pressed_buttons_.size() == 2 ) {
        for ( QPushButton* button_block : cardbuttons_ ) {
            button_block->blockSignals(true);
        }
        QTimer::singleShot(800, this, &MainWindow::two_buttons_pressed);
    }
}

void MainWindow::two_buttons_pressed() {

    // Enable the new game button again
    ui->newButton->blockSignals(false);

    // If the cards are pairs, cheer on the player, hide the icons and disable
    // the buttons, add a point to the player and give them another turn,
    // and if it was the last pair, call init_congrats() to get the winner
    if ( pressed_buttons_.at(0)->text() == pressed_buttons_.at(1)->text() ) {
        ui->statusLabel->setText("Well done!");
        pressed_buttons_.at(0)->setIconSize(QSize(0,0));
        pressed_buttons_.at(1)->setIconSize(QSize(0,0));
        pressed_buttons_.at(0)->setDisabled(true);
        pressed_buttons_.at(1)->setDisabled(true);
        if ( GameEngine_->add_point() ) {
            init_congrats();
        }
    }
    // If the cards weren't pairs, say sorry, change turns and hide the buttons
    else {
        ui->statusLabel->setText("Nope, sorry!");
        GameEngine_->change_turn();
        pressed_buttons_.at(0)->setIcon(icons_.at(0));
        pressed_buttons_.at(1)->setIcon(icons_.at(0));
    }

    // Update current label
    round_update();
    // Clear the pressed_buttons_vector
    pressed_buttons_.clear();

    // Enable the cards' signals again
    for ( QPushButton* card : cardbuttons_ ) {
        card->blockSignals(false);
    }

}

void MainWindow::load_icons()
{
    // There are icons that have names from 0 to 20 .png
    const vector<int> ids_ = {0,1,2,3,4,5,6,7,8,9,10,
                             11,12,13,14,15,16,17,18,19,20};
    const string PREFIX(":/resources/");
    const string SUFFIX(".png");

    // Go through the ids and add corresponding images to the icons_ vector
    for ( int i : ids_ ) {
        string str = to_string(i);
        string filename = PREFIX + str + SUFFIX;
        QPixmap image(QString::fromStdString(filename));

        icons_.push_back(image);
    }

}

void MainWindow::init_congrats() {

    // Hide the buttons, stop the timer
    ui->buttonBox->setHidden(true);
    timer_->stop();

    // Get the winner/tie result from GameEngine, congratulate the player(s)
    QString winner_str = QString::fromStdString(GameEngine_->check_winner());
    ui->winnerText->setText(winner_str);
    ui->statusLabel->setText("Well done!");
    ui->currentLabel->setText(" ");

    // Print a cat again, and then show the congratsBox now that it's ready
    ui->catLabel->setPixmap(icons_.at(0).scaled(300,300));
    ui->congratsBox->setHidden(false);

}

void MainWindow::round_update()
{
    // Update the information about the current player and their points amount
    QString current =
            QString::fromStdString(GameEngine_->get_current_player_info());

    ui->currentLabel->setText(current);
}

void MainWindow::new_game()
{
    // Delete the previous GameEngine object and null the pointer
    delete GameEngine_;
    GameEngine_ = nullptr;

    // Delete all the cards from the cardbuttons_ so there's room for new cards
    for ( QPushButton* card : cardbuttons_ ) {
        delete card;
    }

    // Stop the timer, clear the cardbuttons_ vector too, clear the
    // pressed_buttons just in case, initiate the greetings window again
    timer_->stop();
    cardbuttons_.clear();
    pressed_buttons_.clear();
    init_greetings();
}

void MainWindow::timer_timeout()
{
    // Add a second to the timer, every second
    int current_seconds = ui->lcdNumberSec->value();
    ui->lcdNumberSec->display(current_seconds + 1);
}

void MainWindow::on_playersSpin_valueChanged(int arg1)
{
    players_ = arg1;
}

void MainWindow::on_pairsSpin_valueChanged(int arg1)
{
    pairs_ = arg1;
}

void MainWindow::on_nameEdit_textChanged(const QString &arg1)
{
    player_names_ = arg1;
}

void MainWindow::on_newButton_pressed()
{
    return new_game();
}
