#pragma once

#include <QtWidgets>
#include "gamecontrol.h"
#include "BoardCanvas.h"
#include <QPair>

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(QWidget *parent = nullptr);

    void add_drawing_functions();
    QPointF slotPiece();
    void PopulateLineCoords();
    QPointF GameCoordtoPixel(int row, int column);
    void PixelCoordtoGame();

protected:

    //void mouseMoveEvent(QMouseEvent* e) override;

    GameControl* m_innerGame{nullptr};
    kapunzu::drawing::BoardCanvas* m_canvas{nullptr};
    QPair<int,int> PlayableCoordinates [50][50];
};
