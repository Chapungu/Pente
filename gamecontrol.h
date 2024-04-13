#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QWidget>
#include <vector>
#include <QMap>

struct GameState
{
    int activePlayer{ 1 };

    const QMap<int, QColor> Get_Color
    {
        {0,    QColor()},
        {1,    QColor::fromRgb(255,255,255)},
        {2,    QColor(Qt::black)},
        {3,    QColor(Qt::blue)},
        {4,    QColor(Qt::red)},
        {5,    QColor(Qt::green)}
    };
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
    QColor getPlayerColor(int player);

    bool CheckValidMove(int row, int column);

public slots:
    void PlacePiece(int row, int column, int player);

private:
    int innerBoard[50][50] = { 0 };//row.. Column..

    GameState State;


};



#endif // GAMECONTROL_H
