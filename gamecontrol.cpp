#include "gamecontrol.h"

GameControl::GameControl(QWidget* parent) {}

void GameControl::setPeice(int row, int column, int player)
{
    innerBoard[row][column] = player;
}

void GameControl::clearPeice(int row, int column)
{
    innerBoard[row][column] = 0;
}
