#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QWidget>
#include <vector>

struct GameState
{
    int activePlayer{ 1 };
};

class GameControl: public QWidget
{
    Q_OBJECT
public:
    GameControl(QWidget* parent);

    void clearPiece(int row, int column);
    const int getPiece(int row, int column);
    void nextPlayer();
    int getCurrentPlayer();

public slots:
    void PlacePiece(int row, int column, int player);

private:
    int innerBoard[50][50];//row.. Column..

    GameState State;

    enum player_colour{empty = 0, black, white, blue, red, green};
};



#endif // GAMECONTROL_H
