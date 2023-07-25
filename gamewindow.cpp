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

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "player.h"
#include "knight.h"
#include "rook.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QtAlgorithms>
#include <QRect>
#include <cctype>
#include <algorithm>

//Intent: Initialize the GameWindow object with the specified parent.
//Pre: valid QWidget 'parent' is provided.
//Pos: A GameWindow object is created with the specified parent and UI elements are set up.
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    // Initialize the class member values
    this->gameResult = "PLAYING";
    this->isCheckmate = false;
    this->isPieceSelected = false;
    this->selectedButton = nullptr;
    this->currentSelectedPiece = ' ';
    this->selectedPosition = Position(-1, -1);
    this->inPromotionStatus = false;
    this->isOfferDraw = false;
    this->validMoves.clear();
    this->originalColors.clear();

    // Set the buttons to be null
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squareButtons[i][j] = nullptr;
        }
    }

    // Set count as the number of buttons counter
    int count = 0;

    // Setup the board by loops through each buttons
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Grab each button from UI and style it
            QString btnName = "box_" + QString::number(count);
            squareButtons[i][j] = GameWindow::findChild<QPushButton *>(btnName);
            squareButtons[i][j]->setFixedHeight(63);

            // Set colors to the buttons according to chess board pattern and also store each button's original color to the map
            if ((i+j) % 2 == 0) {
                squareButtons[i][j]->setStyleSheet("background: #F2DBCC;");
                originalColors[squareButtons[i][j]] = "#F2DBCC";
            }
            else {
                squareButtons[i][j]->setStyleSheet("background: #211A4E;");
                originalColors[squareButtons[i][j]] = "#211A4E";
            }

            // Take the current piece of the board
            char piece = board.board[i][j];

            // Determine the color of the piece
            bool isWhite = true;

            if (islower(piece)) {
                isWhite = false;
                piece = toupper(piece);
            }

            // Create QLabel to store image on the button
            QLabel* storingLabel = new QLabel("", squareButtons[i][j]);

            QPixmap pixmap = "";

            // Based on the piece, get its image
            if (piece == 'P') {
                Pawn piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'K') {
                King piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'Q') {
                Queen piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'B') {
                Bishop piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'N') {
                Knight piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'R') {
                Rook piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }

            // Store the image to the label of the button
            storingLabel->setPixmap(pixmap);
            storingLabel->setAlignment(Qt::AlignCenter);
            squareButtons[i][j]->setLayout(new QVBoxLayout());
            squareButtons[i][j]->layout()->addWidget(storingLabel);

            // Set each button to call squareSelected function everytime the button is clicked
            connect(squareButtons[i][j], SIGNAL(clicked()), this, SLOT(squareSelected()));

            // Increment counter
            count++;
        }
    }
}

// Intent: To set the turn of the game window to either white or black, based on the provided boolean value
// Pre: The whiteFirst parameter should be a valid boolean value
// Post: The isWhiteTurn variable is updated to the value of whiteFirst, and the turn is updated by calling the updateTurn function
void GameWindow::setWhiteFirst(bool whiteFirst)
{
    this->isWhiteTurn = whiteFirst;
    updateTurn();
}


// Intent: To reset the selected button after unselected or moved a piece
// Pre: validMoves and originalColor is needed
// Post: All the changed style button got their original style back
void GameWindow::resetSelected(){
    // Get the original color and set it to the button
    QString originalColor = originalColors[this->selectedButton];
    this->selectedButton->setStyleSheet("background: " + originalColor + ";");

    // Set the color of button of validMoves back to original
    for (Position& pos : this->validMoves)
    {
        QString originalColor = originalColors[squareButtons[pos.y][pos.x]];

        squareButtons[pos.y][pos.x]->setStyleSheet("background: " + originalColor + ";");
    }

    // Reset the related state
    this->isPieceSelected = false;
    this->currentSelectedPiece = ' ';
    this->selectedPosition = Position(-1, -1);
    this->selectedButton = nullptr;
    this->validMoves.clear();
}

// Intent: To handle the click event of a button
// Pre: Button UI must be available
// Post: Handle the user click based on the current state of the game
void GameWindow::squareSelected(){
    // If the game is in waiting for promotion state, disable click for the board
    if (this->inPromotionStatus) {
        return;
    }

    // Get the clicked button element
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    // Convert the button name index to get which box is clicke don the board
    int indexNum = button->objectName().mid(4).toInt();
    int row = indexNum / 8;
    int col = indexNum % 8;

    // If no piece is selected, then select the piece
    if (!this->isPieceSelected)
    {
        // Getting the piece on the board
        char piece = board.board[row][col];

        // If the selected piece is empty, then disbale select
        if (piece == ' ') {
            return;
        }

        // If the user click on enemy piece, disable select
        if (this->isWhiteTurn && islower(piece)) {
            return;
        }
        else if (!this->isWhiteTurn && isupper(piece)) {
            return;
        }

        // Handle selected piece by update the state and styling
        this->isPieceSelected = true;
        this->selectedButton = button;
        this->selectedPosition = Position(col, row);
        button->setStyleSheet("background: gold;");
        this->currentSelectedPiece = piece;

        // Get the color of selected piece
        bool isWhite = true;

        if (islower(piece)) {
            isWhite = false;
            piece = toupper(piece);
        }

        // Get the valid moves of the piece
        if (piece == 'P') {
            Pawn piece(isWhite, Position(col, row));
            this->validMoves = piece.getPossibleMove(board);
        }
        else if (piece == 'K') {
            King piece(isWhite, Position(col, row));
            this->validMoves = piece.getPossibleMove(board);
        }
        else if (piece == 'Q') {
            Queen piece(isWhite, Position(col, row));
            this->validMoves = piece.getPossibleMove(board);
        }
        else if (piece == 'B') {
            Bishop piece(isWhite, Position(col, row));
            this->validMoves = piece.getPossibleMove(board);
        }
        else if (piece == 'N') {
            Knight piece(isWhite, Position(col, row));
            this->validMoves = piece.getPossibleMove(board);
        }
        else if (piece == 'R') {
            Rook piece(isWhite, Position(col, row));
            this->validMoves = piece.getPossibleMove(board);
        }

        // Set styling for the valid moves
        for (Position& pos : this->validMoves)
        {
            squareButtons[pos.y][pos.x]->setStyleSheet("background: coral;");
        }

        return;
    }

    // If a piece is already selected but clicked on other button instead, then disable click
    if (this->isPieceSelected && (this->selectedButton == button))
    {
        resetSelected();
        return;
    }

    // Loop throught each validMoves's position
    for (Position& validPos : this->validMoves) {
        // Get the clicked position
        Position clickedPos(col, row);

        // If the clicked position is equal to valid
        if (clickedPos == validPos) {
            // Set the color of the piece
            bool isWhite = true;

            char piece = this->currentSelectedPiece;

            if (islower(piece)) {
                isWhite = false;
                piece = toupper(piece);
            }

            // Take the label of the button to store image
            QLabel* currentLabel = this->selectedButton->findChild<QLabel*>();
            QLabel* targetLabel = button->findChild<QLabel*>();
            QPixmap pixmap = "";

            // According to the specific piece, move the piece and set pixmap to the specific image
            if (piece == 'P') {
                Pawn piece(isWhite, this->selectedPosition);
                pixmap = piece.imgUrl;
                piece.move(board, clickedPos);

                // If the pawn can fullifil the condition to be promoted, set the game to the promoted state
                if ((isWhite && clickedPos.y == 0) || (!isWhite && clickedPos.y == 7)) {
                    this->inPromotionStatus = true;

                    ui->labelPromotion->setText("Select Promotion");
                    ui->buttonQ->setText("Queen");
                    ui->buttonB->setText("Bishop");
                    ui->buttonN->setText("Knight");
                    ui->buttonR->setText("Rook");

                    ui->buttonQ->setCursor(Qt::PointingHandCursor);
                    ui->buttonB->setCursor(Qt::PointingHandCursor);
                    ui->buttonN->setCursor(Qt::PointingHandCursor);
                    ui->buttonR->setCursor(Qt::PointingHandCursor);
                }
            }
            else if (piece == 'K') {
                King piece(isWhite, this->selectedPosition);
                pixmap = piece.imgUrl;
                piece.move(board, clickedPos);
            }
            else if (piece == 'Q') {
                Queen piece(isWhite, this->selectedPosition);
                pixmap = piece.imgUrl;
                piece.move(board, clickedPos);
            }
            else if (piece == 'B') {
                Bishop piece(isWhite, this->selectedPosition);
                pixmap = piece.imgUrl;
                piece.move(board, clickedPos);
            }
            else if (piece == 'N') {
                Knight piece(isWhite, this->selectedPosition);
                pixmap = piece.imgUrl;
                piece.move(board, clickedPos);
            }
            else if (piece == 'R') {
                Rook piece(isWhite, this->selectedPosition);
                pixmap = piece.imgUrl;
                piece.move(board, clickedPos);
            }

            // Set the target position button to the image
            targetLabel->setPixmap(pixmap);

            // Set the original position button to empty
            QPixmap emptyPixmap = "";
            currentLabel->setPixmap(emptyPixmap);

            // Reset the selected button by calling resetSelected
            resetSelected();

            // Check whether the enemy is on checkmate condition after moving the piece
            this->isCheckmate = checkCheckmate(Position(col, row));

            if (this->isCheckmate) {
                this->gameResult = (this->isWhiteTurn) ? "WHITE" : "BLACK";
                endGame();
            }

            // Change the turn
            this->isWhiteTurn = !isWhiteTurn;
            updateTurn();

            break;
        }
    }
}

// GameWindow destructor
GameWindow::~GameWindow()
{
    delete ui;
}

// Intent: To reset the board back to initial state
// Pre: None
// Post: The board and state is reseted
void GameWindow::resetGame() {
    // Reset the current state
    this->isCheckmate = false;
    this->isPieceSelected = false;
    this->selectedButton = nullptr;
    this->currentSelectedPiece = ' ';
    this->selectedPosition = Position(-1, -1);
    this->inPromotionStatus = false;
    this->validMoves.clear();
    this->isOfferDraw = false;

    // Reset the current the UI
    ui->drawButton->setText("Draw");
    ui->resignButton->setText("Resign");
    ui->labelPromotion->setText("Chess battle!");
    ui->buttonQ->setText("");
    ui->buttonB->setText("");
    ui->buttonN->setText("");
    ui->buttonR->setText("");

    // Loop through each piece and set the board to style it according to the initial board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Take the current piece and take its color
            char piece = board.board[i][j];

            bool isWhite = true;

            if (islower(piece)) {
                isWhite = false;
                piece = toupper(piece);
            }

            // Take the label of each button to store image
            QLabel* targetLabel = squareButtons[i][j]->findChild<QLabel*>();
            QPixmap pixmap = "";

            // Take the specific image based on the piece
            if (piece == 'P') {
                Pawn piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'K') {
                King piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'Q') {
                Queen piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'B') {
                Bishop piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'N') {
                Knight piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }
            else if (piece == 'R') {
                Rook piece(isWhite, Position(j, i));
                pixmap = piece.imgUrl;
            }

            // Set the image to the label
            targetLabel->setPixmap(pixmap);
        }
    }
}

// Intent: Reset the game and move to the result page
// Pre: None
// Post: The game is reset and move to the result page
void GameWindow::endGame() {
    // Reset the board to be new board
    Board newBoard;
    this->board = newBoard;

    // Call the resetGame function to reset the game
    resetGame();

    // Emit the ShowResultClicked() signal
    emit ShowResultClicked();
}

// Intent: Resign the game or decline the draw offer
// Pre: The button is clicked
// Post: The game is end or the offer is declined
void GameWindow::on_resignButton_clicked()
{
    // If the game is in promotion status, disable click
    if (this->inPromotionStatus) {
        return;
    }

    // Handle click based on the current state
    if (!this->isOfferDraw) {
        // If the game is not in offer draw status, then the click means resign so assign the winner to be the enemy
        this->gameResult = (isWhiteTurn) ? "BLACK" : "WHITE";

        // End the game
        endGame();
    }
    else {
        // Reset the UI state if is not in offer draw because its in DECLINE draw button
        this->isOfferDraw = false;
        ui->drawButton->setText("Draw");
        ui->resignButton->setText("Resign");
        ui->labelPromotion->setText("Chess battle!");
        ui->buttonQ->setText("");
        ui->buttonB->setText("");
        ui->buttonN->setText("");
        ui->buttonR->setText("");
    }
}

// Intent: Offer draw to the enemy or accept the draw offer
// Pre: Button is clciked
// Post: Darw is offered to enemy or the game is end with draw
void GameWindow::on_drawButton_clicked()
{
    // If the game is in promotion status, disable click
    if (this->inPromotionStatus) {
        return;
    }

    // Handle click based on the current state
    if (!this->isOfferDraw) {
        // Offer draw to the enemy
        QString name = this->isWhiteTurn ? "Guardian" : "Villain";
        this->isWhiteTurn = !this->isWhiteTurn;
        updateTurn();
        this->isOfferDraw = true;
        ui->drawButton->setText("Accept");
        ui->resignButton->setText("Decline");

        ui->labelPromotion->setText("Draw request!");
        ui->buttonQ->setText("");
        ui->buttonB->setText(name);
        ui->buttonN->setText("requested");
        ui->buttonR->setText("draw");
    }
    else {
        // If the game is not in draw state, then the button is ACCEPT button, and declare draw
        this->gameResult = "DRAW";
        endGame();
    }
}

// Intent: Promote the piece
// Pre: UI button for promotion is clicked
// Post: The piece is promoted
void GameWindow::handlePromotion(char selectedPromotion) {
    // If the game is in promotion status, disable click
    if (!this->inPromotionStatus) {
        return;
    }

    // Grab the promoted piece
    Position promotedPos = board.lastMovedPiecePosition;
    char promotedPawn = board.board[promotedPos.y][promotedPos.x];
    bool isWhite = true;

    if (islower(promotedPawn)) {
        isWhite = false;
    }

    QPixmap pixmap = "";

    // Get the selected promotion image
    if (selectedPromotion == 'Q') {
        Queen promotedPiece(isWhite, promotedPos);
        pixmap = promotedPiece.imgUrl;
    }
    else if (selectedPromotion == 'B') {
        Bishop promotedPiece(isWhite, promotedPos);
        pixmap = promotedPiece.imgUrl;
    }
    else if (selectedPromotion == 'N') {
        Knight promotedPiece(isWhite, promotedPos);
        pixmap = promotedPiece.imgUrl;
    }
    else if (selectedPromotion == 'R') {
        Rook promotedPiece(isWhite, promotedPos);
        pixmap = promotedPiece.imgUrl;
    }

    // Set the piece color
    if (!isWhite)
    {
        selectedPromotion = tolower(selectedPromotion);
    }

    // Change the piece to the selected promotion
    board.board[promotedPos.y][promotedPos.x] = selectedPromotion;

    // Grab the label of the button and update the piece image
    QLabel* targetLabel = squareButtons[promotedPos.y][promotedPos.x]->findChild<QLabel*>();
    targetLabel->setPixmap(pixmap);

    // Return the UI back
    ui->labelPromotion->setText("Chess Battle!");
    ui->buttonQ->setText("");
    ui->buttonB->setText("");
    ui->buttonN->setText("");
    ui->buttonR->setText("");

    ui->buttonQ->setCursor(Qt::ArrowCursor);
    ui->buttonB->setCursor(Qt::ArrowCursor);
    ui->buttonN->setCursor(Qt::ArrowCursor);
    ui->buttonR->setCursor(Qt::ArrowCursor);

    // Reset the promotion status back
    this->inPromotionStatus = false;
    updateTurn();
}

// Intent: To handle the promotion of pawn to be queen
// Pre: Button is clicked
// Post: Pawn is promoted to be queen
void GameWindow::on_buttonQ_clicked()
{
    handlePromotion('Q');
}

// Intent: To handle the promotion of pawn to be bishop
// Pre: Button is clicked
// Post: Pawn is promoted to be bishop
void GameWindow::on_buttonB_clicked()
{
    handlePromotion('B');
}

// Intent: To handle the promotion of pawn to be knight
// Pre: Button is clicked
// Post: Pawn is promoted to be knight
void GameWindow::on_buttonN_clicked()
{
    handlePromotion('N');
}

// Intent: To handle the promotion of pawn to be rook
// Pre: Button is clicked
// Post: Pawn is promoted to be rook
void GameWindow::on_buttonR_clicked()
{
    handlePromotion('R');
}

// Intent: To return the gameResult
// Pre: gameResult is a valid string
// Post: gameResult is returned
QString GameWindow::getGameResult() {
    return this->gameResult;
}

// Intent: To change the display ui of the current turn
// Pre: isWhiteTurn have valid value
// Post: Change the ui display of the current turn
void GameWindow::updateTurn()
{
    // If the game is in promotion status then disable update
    if (this->inPromotionStatus) {
        return;
    }

    // Update the ui turn indicator based on the current turn
    if (this->isWhiteTurn) {
        ui->img_villain1->setPixmap(QPixmap(""));
        ui->img_villain2->setPixmap(QPixmap(""));
        ui->img_guardian1->setPixmap(QPixmap(":/images/images/guardian1_mark.png"));
        ui->img_guardian2->setPixmap(QPixmap(":/images/images/guardian2_mark.png"));
        ui->turnLabel->setText("Guardians (white) turn");
    }
    else {
        ui->img_guardian1->setPixmap(QPixmap(""));
        ui->img_guardian2->setPixmap(QPixmap(""));
        ui->img_villain1->setPixmap(QPixmap(":/images/images/villain1_mark.png"));
        ui->img_villain2->setPixmap(QPixmap(":/images/images/villain2_mark.png"));
        ui->turnLabel->setText("Villain (black) turn");
    }
}

// Intent: To know whether the enemy is on checkmate
// Pre: Have the current piece pos as parameter
// Post: Returns boolean
bool GameWindow::checkCheckmate(Position currentPiecePos) {
    // Initialize player class
    Player player(board.board);

    // Get the current player color and enemy color
    QString color = isWhiteTurn ? "WHITE" : "BLACK";
    QString enemyColor = !isWhiteTurn ? "WHITE" : "BLACK";
    bool isWhite = isWhiteTurn ? true : false;
    QVector<Position> checks;
    bool checksPossibility = false;

    QVector<Position> playerPieces = player.getOwnPieces(color);
    QVector<Position> enemyPieces = player.getEnemyPieces(color);

    // Get the position of the enemy king position
    Position enemyKingPos = player.getKingPosition(enemyColor);

    for (Position piecePos : playerPieces) {
        QVector<Position> possibleMoves;    // To store all the current piece possible moves
        char piece = player.getPieceAt(piecePos);  // Copy the piece icon to 'piece'

        // If the player color is white copy all the possible moves of white pieces
        if (isWhite)
        {
            // Appends all the player pieces' possible moves
            if (piece == 'P')
            {
                Pawn piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'K')
            {
                King piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'Q')
            {
                Queen piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'B')
            {
                Bishop piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'N')
            {
                Knight piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'R')
            {
                Rook piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
        }
        // If the player color is black copy all the possible moves of black pieces
        else
        {
            // Appends all the palyer pieces' possible moves
            if (piece == 'p')
            {
                Pawn piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'k')
            {
                King piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'q')
            {
                Queen piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'b')
            {
                Bishop piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'n')
            {
                Knight piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
            else if (piece == 'r')
            {
                Rook piece(isWhite, piecePos);
                possibleMoves = piece.getSimulation(board);
            }
        }

        // Simulate each move and check if the enrmy king is still in check
        for (const Position& move : possibleMoves)
        {
            if (move.x == enemyKingPos.x && move.y == enemyKingPos.y) {

                checks.push_back(piecePos);
                checksPossibility = true;

            }
        }
    }

    if (!checksPossibility) {
        return false;
    }

    for (Position piecePos : enemyPieces)
    {
        QVector<Position> possibleMoves;    // To store all the current piece possible moves
        char piece = player.getPieceAt(piecePos);  // Copy the piece icon to 'piece'

        // Appends all the enemy pieces' possible moves
        if (piece == 'P')
        {
            Pawn piece(true, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'K')
        {
            King piece(true, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'Q')
        {
            Queen piece(true, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'B')
        {
            Bishop piece(true, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'N')
        {
            Knight piece(true, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'R')
        {
            Rook piece(true, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'p')
        {
            Pawn piece(false, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'k')
        {
            King piece(false, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'q')
        {
            Queen piece(false, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'b')
        {
            Bishop piece(false, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'n')
        {
            Knight piece(false, piecePos);
            possibleMoves = piece.getSimulation(board);
        }
        else if (piece == 'r')
        {
            Rook piece(false, piecePos);
            possibleMoves = piece.getSimulation(board);
        }

        // Simulate each move and check if the enemy can capture the player piece that cause the check
        for (const Position& move : possibleMoves) {
            for (auto it = checks.begin(); it != checks.end(); ) {
                Position& check = *it;
                if (move.y == check.y && move.x == check.x) {
                    // delete the check from checks if it is the same with move
                    it = checks.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (checks.empty()) {
            return false;
        }
    }

    // If the enemy king is invalid then the enemy king is gone, which means checkmate
    if (enemyKingPos == Position(-1, -1)) {
        return true;
    }

    return checksPossibility;
}
