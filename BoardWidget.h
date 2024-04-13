#pragma once

#include <QtWidgets>
#include "gamecontrol.h"
#include "BoardCanvas.h"
#include <QPair>
#include <vector>

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

    void add_drawing_functions();
    QPointF slotPiece(QPoint MousePos);
    void PopulateLineCoords();
    QPointF GameCoordtoPixel(int row, int column);
    QPoint PixelCoordtoGame(QPoint Position);
    void PlacePeiceSL(QPoint pos);

    

protected:

    //void mouseMoveEvent(QMouseEvent* e) override;

    GameControl* m_innerGame{nullptr};
    kapunzu::drawing::BoardCanvas* m_canvas{nullptr};
    QPair<int,int> PlayableCoordinates [50][50];
    
    
private:

    int numLines{ 50 };
    std::vector<int>horizontal_line_coords;
    std::vector<int> vertical_line_coords;
    float xInterval{0};
    float yInterval{0};
    QPointF m_mousePos;
    QColor activePlayerColor{ 0,0,0 };

};
