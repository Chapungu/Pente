#include "gamecontrol.h"
#include "BoardCanvas.h"

#include <QDebug>

GameControl::GameControl(QWidget* parent)
{

}

void GameControl::PlacePiece(int row, int column, int player)
{
    //qDebug() << "PlacePieceSL activated" << " row = " << row << " column = " << column << " player = " << player;
    if (!CheckValidMove(row, column)) { return; }
    innerBoard[row][column] = player;
    this->nextPlayer();
}

void GameControl::clearPiece(int row, int column)
{
    innerBoard[row][column] = 0;
}

const int GameControl::getPiece(int row, int column)
{
    return innerBoard[row][column];
}

void GameControl::nextPlayer()
{
    int players = 2;
    if (this->State.activePlayer == players) { this->State.activePlayer = 1; }
    else { this->State.activePlayer++; }
}

int GameControl::getCurrentPlayer()
{
    return this->State.activePlayer;
}

QColor GameControl::getPlayerColor(int player)
{
    return State.Get_Color.value(player);
}

bool GameControl::CheckValidMove(int row, int column)
{
    if (innerBoard[row][column] != 0) { return false; }
    return true;
}

void GameControl::CheckTakeMove(int row, int column)
{

}