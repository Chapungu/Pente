#pragma once

#include "qpainter.h"
#include <QWidget>


namespace kapunzu{
namespace drawing{

class BoardCanvas : public QWidget
{
    Q_OBJECT
public:
    BoardCanvas(QWidget* parent);

    ~BoardCanvas(){}

    void resizeEvent(QResizeEvent *e) override;

    using DrawFunction = std::function<void(kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)>;

    void PopulateLineCoords();
    QRect GetRect(){return rect();}
    void AddDrawingFunctions();


    void AddPeice(DrawFunction f){m_DrawPieces.push_back(f);}
    void ClearPeices() { m_DrawPieces.clear(); }

    void AddDrawBoard(DrawFunction f) {m_DrawBoard.push_back(f);}
    void ResetBoard() { m_DrawBoard.clear(); }

    void AddDrawOverlay(DrawFunction f) {m_DrawOverlays.push_back(f);}
    void ResetOverlay() { m_DrawOverlays.clear(); }

    bool m_updateOverlay{false};
    bool m_updatePeices{false};
    bool m_updateBoard{true};

    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent* e) override;
    QPointF slotPiece();

    QPointF GameCoordtoPixel(int row, int column);
    void PixelCoordtoGame();
    int xLinesPixelValues[50];
    int yLinesPixelValues[50];

    int x;
    int y;

Q_SIGNALS:
    void PlacePieceSG(int x, int y, int player);

protected:

    void paintEvent(QPaintEvent * e) override;
   // Borders of the primary drawing Area
    int m_borderLeft{ 0 };
    int m_borderRight{ 0 };
    int m_borderTop{ 0 };
    int m_borderBottom{ 0 };



    QPointF MousePos{0,0};


    std::vector<DrawFunction> m_DrawBoard;
    std::vector<DrawFunction> m_DrawPieces;
    std::vector<DrawFunction> m_DrawOverlays;

};


}
}

/*
 * Notes
 *
 *  1.  Something triggers the need for a repaint, such as a user interaction or changes in the application's state.
    2.  Qt schedules a paint event for the widget.
    3.  The event loop in the application's main thread processes pending events.
    4.  When the paint event is reached in the event queue, Qt calls the widget's paintEvent() method.
    5.  Inside the paintEvent() method, you implement the painting logic to render the contents of the widget.
    6.  After the paintEvent() method returns, Qt updates the display to reflect the changes made by your painting logic.
 *
 *
 */
