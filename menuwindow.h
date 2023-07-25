#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "resultwindow.h"
#include "gamewindow.h"
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_startGameButton_clicked();
    void moveToMenu();
    void moveToResult();

    void on_actionNext_Songs_triggered();

    void on_actionPrevious_Music_triggered();

    void on_actionExit_triggered();

    void on_chooseWhiteFirstButton_clicked();

    void on_chooseBlackFirstButton_clicked();

    void on_actionTurn_Off_triggered();

    void on_actionTurn_On_Music_triggered();

private:
    Ui::MenuWindow *ui;
    GameWindow _GameWindowPage;
    ResultWindow _ResultWindowPage;
    int musicIndex;
    QMediaPlayer* music = new QMediaPlayer;
    bool whiteFirst = true;
    QString normalButtonSS = "QPushButton { color: white; text-transform: uppercase; padding: 7px 0px; margin-top: 5px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(4,1,46,1), stop:0.85 rgba(45,7,93,1), stop:1 rgba(80,5,80,1)); border: 1px solid white; } QPushButton:hover { color: gold; text-transform: uppercase; margin-top: 5px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(4,1,46,1), stop:0.85 rgba(45,7,93,1), stop:1 rgba(80,5,80,1)); border: 2px solid gold; }";
    QString selectedButtonSS = "QPushButton { color: gold; text-transform: uppercase; padding: 7px 0px; margin-top: 5px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(4,1,46,1), stop:0.85 rgba(45,7,93,1), stop:1 rgba(80,5,80,1)); border: 2px solid gold; } QPushButton:hover { color: gold; text-transform: uppercase; margin-top: 5px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(4,1,46,1), stop:0.85 rgba(45,7,93,1), stop:1 rgba(80,5,80,1)); border: 2px solid gold; }";
};
#endif // MENUWINDOW_H
