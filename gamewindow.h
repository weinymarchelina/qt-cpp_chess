#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QMap>
#include <QString>
#include <QLabel>
#include <board.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    QString getGameResult();
    void setWhiteFirst(bool);
    void setTimeLimit(int);

signals:
    void ShowResultClicked();

private slots:
    void on_resignButton_clicked();
    void squareSelected();
    void on_buttonQ_clicked();
    void on_buttonB_clicked();
    void on_buttonN_clicked();
    void on_buttonR_clicked();
    void on_drawButton_clicked();

private:
    Ui::GameWindow *ui;
    QPushButton *squareButtons[8][8];
    QVector<Position> validMoves;
    QMap<QPushButton *, QString> originalColors;
    QPushButton *selectedButton;
    char currentSelectedPiece;
    bool isPieceSelected;
    Position selectedPosition;
    Board board;
    bool inPromotionStatus;
    bool isOfferDraw;
    bool isCheckmate;
    QString gameResult;
    void resetGame();
    bool isWhiteTurn;
    void updateTurn();
    void endGame();
    bool checkCheckmate(Position targetPos);
    void handlePromotion(char selectedPromotion);
    void resetSelected();
};

#endif // GAMEWINDOW_H
