#pragma once

#include "BoardWidget.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "width = " << this->width() << " height = " << this->height();
    m_innerGame = new GameControl(this);
    m_canvas = new kapunzu::drawing::BoardCanvas(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_canvas);
    m_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setLayout(layout);
    qDebug() << "BoardWidget:: " << "width = " << this->width() << " height = " << this->height();


    connect(m_canvas, &kapunzu::drawing::BoardCanvas::PlacePieceSG, m_innerGame, &GameControl::PlacePieceSL);

    auto drawPieces = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
    {
        for (int x = 0; x < 50; x++)
        {
            for (int y = 0; y < 50; y++)
            {
                int player = m_innerGame->getPiece(x, y);
                if (player == 1)
                {
                    painter.save();
                    painter.setBrush(QColor(0, 0, 0));
                    //qDebug() << "Mouse Position = " << MousePos << " Slot Position = " << Position;
                    QPointF position = canvas.GameCoordtoPixel(x, y);
                    painter.drawEllipse(position, 7, 7);
                    painter.restore();
                }
                else
                {
                    continue;
                }
            }
        }
    };

    m_canvas->AddPeice(drawPieces);
    m_canvas->m_updatePeices = true;
    m_canvas->resize(this->width(),this->height());
    m_canvas->update();
}






