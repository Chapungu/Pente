#include "BoardCanvas.h"
#include "qevent.h"
#include <QPainter>
#include <QDebug>

namespace kapunzu {
    namespace drawing {

        void BoardCanvas::paintEvent(QPaintEvent* e)
        {
            QPainter painter(this);
            painter.setPen(Qt::black);
            // Draw the board
            if (m_updateBoard)
            {
                for (const auto& drawFunc : m_DrawBoard) {
                    drawFunc(*this, painter);
                }m_updateBoard = true;
            }
            if (m_updatePeices) {
                for (const auto& drawFunc : m_DrawPieces) {
                    drawFunc(*this, painter);
                }
            }m_updatePeices = true;

            if (m_updateOverlay) {
                for (const auto& drawFunc : m_DrawOverlays) {
                    drawFunc(*this, painter);
                }
            }m_updateOverlay = true;
        }

        BoardCanvas::BoardCanvas(QWidget* parent) :QWidget(parent)
        {
            qDebug() << "BoardCanvas:: " << "width = " << this->width() << " height = " << this->height();
            this->setAttribute(Qt::WA_MouseTracking);

            AddDrawingFunctions();

        }

        void BoardCanvas::resizeEvent(QResizeEvent* e)
        {

            QWidget::resizeEvent(e);
        }

        void BoardCanvas::AddDrawingFunctions()
        {

        }

        void BoardCanvas::mouseMoveEvent(QMouseEvent* e)
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


    }
}
