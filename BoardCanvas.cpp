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
    if (m_updatePeices) {
        for (const auto& drawFunc : m_DrawPieces) {
            drawFunc(*this, painter);
        }
    }m_updatePeices = true;

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

    AddDrawingFunctions();
    PopulateLineCoords();
}

void BoardCanvas::resizeEvent(QResizeEvent *e)
{
    PopulateLineCoords();
    QWidget::resizeEvent(e);
}

void BoardCanvas::PopulateLineCoords()
{
    int numLines{50};
    // Calculate the interval between lines
    float xInterval = static_cast<float>(800) / (numLines + 1);
    float yInterval = static_cast<float>(800) / (numLines + 1);

    // Draw vertical lines
    for (int i = 0; i <= numLines; i++) {
        int x = static_cast<int>(xInterval * i+1);
        xLinesPixelValues[i] = x;
    }

    // Draw horizontal lines
    for (int i = 0; i <= numLines; i++) {
        int y = static_cast<int>(yInterval * i+1);
        yLinesPixelValues[i] = y;
    }
    int cs = 1;
}

void BoardCanvas::AddDrawingFunctions()
{

    auto drawLines = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
    {
        painter.save();
        painter.setBrush(QColor(210, 180, 140));
        painter.drawRect(0, 0, this->width(), this->height());
        painter.restore();
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
        QPointF Position = slotPiece();
        //qDebug() << "Mouse Position = " << MousePos << " Slot Position = " << Position;
        painter.drawEllipse(Position, 7, 7);
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

void BoardCanvas::mousePressEvent(QMouseEvent* e)
{
    emit PlacePieceSG(x, y, 1);
    qDebug() << "Mouse Pressed";
	QWidget::mousePressEvent(e);
}

QPointF BoardCanvas::slotPiece()
{
    x = 50-1;
    y = 50-1;

    while(MousePos.x() < xLinesPixelValues[x]){x--;}
    //if(MousePos.x() - xLinesPixelValues[x] > xLinesPixelValues[x] - MousePos.x()){x++;}

    while(MousePos.y() < yLinesPixelValues[y]){y--;}
    //if(MousePos.y() - yLinesPixelValues[y] > yLinesPixelValues[y] - MousePos.y()){y++;}

    QPointF PiecePos;
	PiecePos.setX(xLinesPixelValues[x]);
	PiecePos.setY(yLinesPixelValues[y]);
    //qDebug() <<"LinesValues(" << xLinesPixelValues[x] << "," << yLinesPixelValues[y] << ")" << "slotPiece(" << x << "," << y << ") MousePos = " << MousePos;
    return PiecePos;
}

QPointF BoardCanvas::GameCoordtoPixel(int row,int column)
{
    QPointF position;
    position.setX(xLinesPixelValues[row]);
    position.setY(yLinesPixelValues[column]);
    return position;
}

void BoardCanvas::PixelCoordtoGame()
{
}
}
}
