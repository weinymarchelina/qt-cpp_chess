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

#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QtMultimediaWidgets>
#include <QPainterPath>
#include <QAudioOutput>
#include <QDebug>

//Intent = Initialize the MenuWindow object with the specified parent.
//Pre = A valid QWidget 'parent' is provided.
//Pos = A MenuWindow object is created with the specified parent and UI elements are set up.
MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    setWindowTitle("Guardians of the Galaxy Vol. 3 Chess Game");

    // Insert the GameWindowPage and ResultWindowPage into the stacked widget
    ui->stackedWidget->insertWidget(1, &_GameWindowPage);
    ui->stackedWidget->insertWidget(2, &_ResultWindowPage);

    // Connect signals and slots
    connect(&_ResultWindowPage, SIGNAL(BackToMenuClicked()), this, SLOT(moveToMenu()));
    connect(&_GameWindowPage, SIGNAL(ShowResultClicked()), this, SLOT(moveToResult()));

    // Set up the background music
    this->music->setMedia(QUrl("qrc:/sounds/sound/bgmusic_1.mp3"));
    this->music->play();

    // Initialize variables
    this->whiteFirst = true;
    this->musicIndex = 1;

    // Set the initial style sheet for the "Choose White First" button
    ui->chooseWhiteFirstButton->setStyleSheet(this->selectedButtonSS);

}

//Intent = Destructor for MenuWindow object.
//Pre = None.
//Pos = MenuWindow object is destroyed and memory is freed.
MenuWindow::~MenuWindow()
{
    delete ui;
}

//Intent = Handle the click event of the "Start Game" button.
//Pre = None.
//Pos = The GameWindowPage is prepared with the specified settings and the stacked //widget is switched to the game page.
void MenuWindow::on_startGameButton_clicked()
{
    // Set the white first setting for the GameWindowPage
    _GameWindowPage.setWhiteFirst(this->whiteFirst);
    // Switch the stacked widget to the game page
    ui->stackedWidget->setCurrentIndex(1);

}

//Intent = Move back to the menu page.
//Pre = None.
//Pos = The stacked widget is switched to the menu page, and the white first setting is reset.
void MenuWindow::moveToMenu()
{
    // Switch the stacked widget to the menu page
    ui->stackedWidget->setCurrentIndex(0);
    // Reset the white first setting
    this->whiteFirst = true;

    // Set the style sheet for the "Choose White First" and "Choose Black First" buttons
    ui->chooseWhiteFirstButton->setStyleSheet(this->selectedButtonSS);
    ui->chooseBlackFirstButton->setStyleSheet(this->normalButtonSS);
}

//Intent = Move to the result page.
//Pre = None.
//Pos = The stacked widget is switched to the result page, and the game result is displayed.
void MenuWindow::moveToResult()
{
    // Get the game result from the GameWindowPage
    QString gameResult = _GameWindowPage.getGameResult();
    // Set the game result for the ResultWindowPage
    _ResultWindowPage.setResult(gameResult);

    // Switch the stacked widget to the result page
    ui->stackedWidget->setCurrentIndex(2);
}

//Intent = Handle the action triggered by the "Next Songs" menu item.
//Pre = None.
//Pos = The music index is incremented and the corresponding music is played.
void MenuWindow::on_actionNext_Songs_triggered()
{
    // Increment the music index
    musicIndex++;

    if (musicIndex > 3)
    {
        musicIndex = 1;
    }


    // Set the media URL for the music based on the music index
    this->music->setMedia(QUrl("qrc:/sounds/sound/bgmusic_" + QString::number(this->musicIndex) + ".mp3"));
    this->music->play();
}

//Intent = Handle the action triggered by the "Previous Music" menu item.
//Pre = None.
//Pos = The music index is decremented and the corresponding music is played.
void MenuWindow::on_actionPrevious_Music_triggered()
{
    // Decrement the music index
    musicIndex--;

    if (musicIndex < 1)
    {
        musicIndex = 3;
    }
    // Set the media URL for the music based on the music index
    this->music->setMedia(QUrl("qrc:/sounds/sound/bgmusic_" + QString::number(this->musicIndex) + ".mp3"));
    this->music->play();
}

//Intent = Handle the action triggered by the "Exit" menu item.
//Pre = None.
//Pos = The application is quit.
void MenuWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


//Intent = Handle the click event of the "Choose White First" button.
//Pre = None.
//Pos = The white first setting is updated and the button style sheets are set accordingly.
void MenuWindow::on_chooseWhiteFirstButton_clicked()
{
    // Set the white first setting and update the button style sheets
    this->whiteFirst = true;
    ui->chooseBlackFirstButton->setStyleSheet(this->normalButtonSS);
    ui->chooseWhiteFirstButton->setStyleSheet(this->selectedButtonSS);
}


//Intent = Handle the click event of the "Choose Black First" button.
//Pre = None.
//Pos = The white first setting is updated and the button style sheets are set accordingly.
void MenuWindow::on_chooseBlackFirstButton_clicked()
{
    // Set the white first setting and update the button style sheets
    this->whiteFirst = false;
    ui->chooseBlackFirstButton->setStyleSheet(this->selectedButtonSS);
    ui->chooseWhiteFirstButton->setStyleSheet(this->normalButtonSS);
}

//Intent = Handle the action triggered by the "Turn Off" menu item.
//Pre = None.
//Pos = The music is paused.
void MenuWindow::on_actionTurn_Off_triggered()
{
    this->music->pause();
}

//Intent = Handle the action triggered by the "Turn On Music" menu item.
//Pre = None.
//Pos = The music is played.
void MenuWindow::on_actionTurn_On_Music_triggered()
{
    this->music->play();
}
