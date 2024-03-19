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




    //m_canvas->resize(this->width(),this->height());
    m_canvas->update();
}






