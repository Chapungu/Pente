#pragma once

#include "BoardWidget.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent)
{
	qDebug() << "width = " << this->width() << " height = " << this->height();
	m_innerGame = new GameControl(this);
	m_canvas = new kapunzu::drawing::BoardCanvas(this);
	auto layout = new QVBoxLayout;
	layout->addWidget(m_canvas);
	m_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setLayout(layout);
	qDebug() << "BoardWidget:: " << "width = " << this->width() << " height = " << this->height();


	connect(m_canvas, &kapunzu::drawing::BoardCanvas::PlacePieceSG, m_innerGame, &GameControl::PlacePieceSL);
}

void BoardWidget::add_drawing_functions()
{

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
					QPointF position = GameCoordtoPixel(x, y);
					painter.drawEllipse(position, 7, 7);
					painter.restore();
				}
				else
				{
				}
			}
		}
	};

	auto drawLines = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
	{
		int xLinesPixelValues[50];
		int yLinesPixelValues[50];
		painter.save();
		painter.setBrush(QColor(210, 180, 140));
		painter.drawRect(0, 0, this->width(), this->height());
		painter.restore();
		// Draw vertical lines
		for (auto value : xLinesPixelValues)
		{
			painter.drawLine(value, 0, value, this->height());
		}

		// Draw horizontal lines
		for (auto value : yLinesPixelValues)
		{
			painter.drawLine(0, value, this->width(), value);
		}
	};

	auto drawHeldPeice = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
	{
		painter.save();
		painter.setBrush(QColor(0, 0, 0));
		QPointF Position = slotPiece();
		//qDebug() << "Mouse Position = " << MousePos << " Slot Position = " << Position;
		painter.drawEllipse(Position, 7, 7);
		painter.restore();
	};

	m_canvas->AddDrawOverlay(drawHeldPeice);
	m_canvas->AddDrawBoard(drawLines);
	m_canvas->AddPeice(drawPieces);

	m_canvas->resize(this->width(), this->height());
	m_canvas->update();
}


QPointF BoardWidget::slotPiece()
{
	/*
	x = 50 - 1;
	y = 50 - 1;

	while (MousePos.x() < xLinesPixelValues[x]) { x--; }
	//if(MousePos.x() - xLinesPixelValues[x] > xLinesPixelValues[x] - MousePos.x()){x++;}

	while (MousePos.y() < yLinesPixelValues[y]) { y--; }
	//if(MousePos.y() - yLinesPixelValues[y] > yLinesPixelValues[y] - MousePos.y()){y++;}

	QPointF PiecePos;
	PiecePos.setX(xLinesPixelValues[x]);
	PiecePos.setY(yLinesPixelValues[y]);
	//qDebug() <<"LinesValues(" << xLinesPixelValues[x] << "," << yLinesPixelValues[y] << ")" << "slotPiece(" << x << "," << y << ") MousePos = " << MousePos;
	return PiecePos;
	*/
	return QPointF{0, 0};
}

void BoardWidget::PopulateLineCoords()
{
	/*
	int numLines{ 50 };
	// Calculate the interval between lines
	float xInterval = static_cast<float>(800) / (numLines + 1);
	float yInterval = static_cast<float>(800) / (numLines + 1);

	// Draw vertical lines
	for (int i = 0; i <= numLines; i++) {
	    int x = static_cast<int>(xInterval * i + 1);
	    xLinesPixelValues[i] = x;
	}

	// Draw horizontal lines
	for (int i = 0; i <= numLines; i++) {
	    int y = static_cast<int>(yInterval * i + 1);
	    yLinesPixelValues[i] = y;
	}
	int cs = 1;
	*/
}

QPointF BoardWidget::GameCoordtoPixel(int row, int column)
{
	/*
	QPointF position;
	position.setX(xLinesPixelValues[row]);
	position.setY(yLinesPixelValues[column]);
	return position;
	*/
	return QPointF{ 0,0 };
}

void BoardWidget::PixelCoordtoGame()
{
}

