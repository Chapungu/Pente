#include "gamecontrol.h"
#include "BoardCanvas.h"

#include <QDebug>

GameControl::GameControl(QWidget* parent)
{

}

void GameControl::PlacePieceSL(int row, int column, int player)
{
    qDebug() << "PlacePieceSL activated";
    innerBoard[row][column] = player;
}

void GameControl::clearPiece(int row, int column)
{
    innerBoard[row][column] = 0;
}

const int GameControl::getPiece(int row, int column)
{
    return innerBoard[row][column];
}
