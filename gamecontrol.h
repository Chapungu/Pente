#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QWidget>
#include <vector>



class GameControl: public QWidget
{
public:
    GameControl(QWidget* parent);
    void setPeice(int row, int column, int player);
    void clearPeice(int row, int column);

private:
    int innerBoard[50][50];//row.. Column..



    enum player_colour{empty = 0, black, white, blue, red, green};
};

#endif // GAMECONTROL_H
