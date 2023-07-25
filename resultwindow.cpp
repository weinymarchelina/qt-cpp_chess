/***********************************************************************
 * File			:	Board.cpp
 * Author		:	鐘詩靈 B11115010
 *					陳仕興 B11115011
 *					魏美芳 B11115014
 * Create Date	:	2023-05-08
 * Editor		:	鐘詩靈 B11115010
 *					陳仕興 B11115011
 *					魏美芳 B11115014
 * Update Date	:	2023-05-17
 * Description	:	This C++ program simulates chess game with Guardians of the Galaxy theme
*************************************************************************/

#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <QDebug>
#include <QPixmap>

//Intent: Initialize the ResultWindow object with the specified parent.
//Pre: valid QWidget 'parent' is provided.
//Pos: A ResultWindow object is created with the specified parent and UI elements are set up.
ResultWindow::ResultWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);

    // Set the default winner to 'W'
    char winner = 'W';

    // Check the winner and update the UI accordingly
    if (winner == 'W')
    {
        // Set the result label text to "Guardians Wins"
        ui->resultLabel->setText("Guardians\nWins");

        // Load the king image and set it as the result image pixmap
        QPixmap pixmap(":/images/images/king.png");
        ui->resultImage->setPixmap(pixmap);
    }
    else
    {
        // Set the result label text to "Villains Wins"
        ui->resultLabel->setText("Villains\nWins");

        // Load the king1 image and set it as the result image pixmap
        QPixmap pixmap(":/images/images/king1.png");
        ui->resultImage->setPixmap(pixmap);
    }
}

// Destructor
ResultWindow::~ResultWindow()
{
    delete ui;
}

// Intent: Send the signal to get back to menu
// Pre: Button is clicked
// Post: Send the signal to back to menu
void ResultWindow::on_playAgainButton_clicked()
{
    // Emit a signal indicating that the user clicked the "Play Again" button
    emit BackToMenuClicked();
}

// Intent: Exit the game
// Pre: None
// Post: Game is exited
void ResultWindow::on_exitButton_clicked()
{
    // Quit the application
    QApplication::quit();
}

// Intent: To set image and label based on the result
// Pre: gameResult is valid string
// Post: The image and label is set absed on the result
void ResultWindow::setResult(QString gameResult) {
    // Store the game result
    this->gameResult = gameResult;

    // Check the game result and update the UI accordingly
    if (gameResult == "WHITE") {
        // Set the result label text to "Guardians Wins"
        ui->resultLabel->setText("Guardians\nWins");

        // Load the guardian_result image and set it as the result image pixmap
        ui->resultImage->setPixmap(QPixmap(":/images/images/guardian_result.png"));
    }
    else if (gameResult == "BLACK") {
        // Set the result label text to "Villains Wins"
        ui->resultLabel->setText("Villains\nWins");

        // Load the villain_result image and set it as the result image pixmap
        ui->resultImage->setPixmap(QPixmap(":/images/images/villain_result.png"));
    }
    else if (gameResult == "DRAW") {
        // Set the result label text to "Game Draw"
        ui->resultLabel->setText("Game\nDraw");

        // Load the draw_result image and set it as the result image pixmap
        ui->resultImage->setPixmap(QPixmap(":/images/images/draw_result.png"));
    }
}
