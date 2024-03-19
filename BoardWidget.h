#pragma once

#include <QtWidgets>
#include "gamecontrol.h"
#include "BoardCanvas.h"
#include <QPair>

class BoardWidget : public QWidget
{
public:
    BoardWidget(QWidget *parent = nullptr);



protected:

    //void mouseMoveEvent(QMouseEvent* e) override;

    GameControl* m_innerGame{nullptr};
    kapunzu::drawing::BoardCanvas* m_canvas{nullptr};
    QPair<int,int> PlayableCoordinates [50][50];
};
