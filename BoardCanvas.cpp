#include "BoardCanvas.h"
#include "qevent.h"
#include <QPainter>
#include <QDebug>

namespace kapunzu{
namespace drawing{

void BoardCanvas::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    // Draw the board
    if(m_updateBoard)
    {
        for (const auto &drawFunc  : m_DrawBoard) {
            drawFunc (*this, painter);
        }m_updateBoard = true;
    }
    if(m_updateOverlay){
        for (const auto &drawFunc  : m_DrawOverlays) {
            drawFunc (*this, painter);
        }
    }m_updateOverlay = true;
}

BoardCanvas::BoardCanvas(QWidget *parent):QWidget(parent)
{
    qDebug() << "BoardCanvas:: " << "width = " << this->width() << " height = " << this->height();
    this->setAttribute(Qt::WA_MouseTracking);


    PopulateLineCoords();
}

void BoardCanvas::resizeEvent(QResizeEvent *e)
{
    PopulateLineCoords();
    QWidget::resizeEvent(e);
}

void BoardCanvas::PopulateLineCoords()
{
    const int numLines{50};
    // Calculate the interval between lines
    float xInterval = static_cast<float>(this->width()) / (numLines + 1);
    float yInterval = static_cast<float>(this->height()) / (numLines + 1);

    // Draw vertical lines
    for (int i = 1; i <= numLines; i++) {
        int x = static_cast<int>(xInterval * i);
        xLinesPixelValues[i] = x;
    }

    // Draw horizontal lines
    for (int i = 1; i <= numLines; i++) {
        int y = static_cast<int>(yInterval * i);
        yLinesPixelValues[i] = y;
    }
}

void BoardCanvas::AddDrawingFunctions()
{
    auto drawLines = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
    {
        // Draw vertical lines
        for (auto value: xLinesPixelValues) {
            painter.drawLine(value, 0, value, this->height());
        }

        // Draw horizontal lines
        for (auto value: yLinesPixelValues) {
            painter.drawLine(0, value, this->width(), value);
        }
    };
    auto drawHeldPeice = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
    {
        painter.save();
        painter.setBrush(QColor(0,0,0));
        painter.drawEllipse(slotPeice(), 7,7);
        painter.restore();
    };

    this->AddDrawOverlay(drawHeldPeice);
    this->AddDrawBoard(drawLines);
}

void BoardCanvas::mouseMoveEvent(QMouseEvent *e)
{
    MousePos.setY(e->y());
    MousePos.setX(e->x());
    m_updateOverlay = true;
    this->update();
}

QPointF BoardCanvas::slotPeice()
{
    int x{0};
    int y{0};


    while(MousePos.x() < xLinesPixelValues[x]){x++;}
    if(MousePos.x() - xLinesPixelValues[x] > xLinesPixelValues[x] - MousePos.x()){x++;}

    while(MousePos.y() < yLinesPixelValues[y]){y++;}
    if(MousePos.y() - yLinesPixelValues[y] > yLinesPixelValues[y] - MousePos.y()){y++;}

    QPointF PeicePos(xLinesPixelValues[x],yLinesPixelValues[y]);

    return PeicePos;
}


}
}
