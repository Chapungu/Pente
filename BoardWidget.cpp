#pragma once

#include "BoardWidget.h"
#include "qevent.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent)
{
	
	m_innerGame = new GameControl(this);
	m_canvas = new kapunzu::drawing::BoardCanvas(this);
	auto layout = new QVBoxLayout;
	layout->addWidget(m_canvas);
	m_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setLayout(layout);
	qDebug() << "BoardWidget:: " << "width = " << this->width() << " height = " << this->height();

	PopulateLineCoords();
	add_drawing_functions();

	connect(m_canvas, &kapunzu::drawing::BoardCanvas::PlacePieceSG, this, &BoardWidget::PlacePeiceSL);
}

BoardWidget::~BoardWidget()
{

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
				if (player == 0) { continue; }
				painter.save();
				painter.setBrush(m_innerGame->getPlayerColor(player));
				//qDebug() << "Mouse Position = " << MousePos << " Slot Position = " << Position;
				QPointF position = GameCoordtoPixel(x, y);
				painter.drawEllipse(position, 7, 7);
				painter.restore();
			
			}
		}
	};

	auto drawLines = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
	{
		painter.save();
		painter.setBrush(QColor(210, 180, 140));
		painter.drawRect(0, 0, this->width(), this->height());
		painter.restore();
		// Draw vertical lines
		for (auto value : horizontal_line_coords)
		{
			painter.drawLine(value, 0, value, this->height());
		}

		// Draw horizontal lines
		for (auto value : vertical_line_coords)
		{
			painter.drawLine(0, value, this->width(), value);
		}
	};

	auto drawHeldPeice = [&](kapunzu::drawing::BoardCanvas& canvas, QPainter& painter)
	{
		painter.save();
		painter.setBrush(m_innerGame->getPlayerColor(m_innerGame->getCurrentPlayer()));
		QPointF Pos = slotPiece(m_canvas->mapFromGlobal(QCursor::pos()));
		//qInfo() << "Pos = x: " << Pos.x() << " y: " << Pos.y();
		painter.drawEllipse(Pos, 7, 7);
		painter.restore();
	};
	m_canvas->AddDrawOverlay(drawHeldPeice);

	
	m_canvas->AddDrawBoard(drawLines);
	m_canvas->AddPeice(drawPieces);

	m_canvas->resize(this->width(), this->height());
	m_canvas->update();
}

QPointF BoardWidget::slotPiece(QPoint MousePos)
{

	int x = horizontal_line_coords.size() -1;
	int y = vertical_line_coords.size() -1;

	while (MousePos.x() < horizontal_line_coords[x] && x != 0)
	{
		if (x > 800) x = 800;
		x--;
		if (x < 0) x = 0; 
	}
	//if(MousePos.x() - xLinesPixelValues[x] > xLinesPixelValues[x] - MousePos.x()){x++;}

	while (MousePos.y() < vertical_line_coords[y] && x != 0)
	{
		if (y > 800) y = 800;
		y--;
		if (y < 0) y = 0; 
	}
	//if(MousePos.y() - yLinesPixelValues[y] > yLinesPixelValues[y] - MousePos.y()){y++;}

	QPointF PiecePos;
	PiecePos.setX(horizontal_line_coords[x]);
	PiecePos.setY(vertical_line_coords[y]);
	//qDebug() <<"LinesValues(" << xLinesPixelValues[x] << "," << yLinesPixelValues[y] << ")" << "slotPiece(" << x << "," << y << ") MousePos = " << MousePos;
	return PiecePos;

}

void BoardWidget::PopulateLineCoords()
{
	// Calculate the interval between lines
	xInterval = static_cast<float>(800) / (numLines + 1);
	yInterval = static_cast<float>(800) / (numLines + 1);

	horizontal_line_coords.resize(numLines);
	vertical_line_coords.resize(numLines);


	// Draw vertical lines
	for (int i = 0; i <= numLines - 1; i++) {
	    int x = static_cast<int>(xInterval * i + 1);
		horizontal_line_coords[i] = x;
	}

	// Draw horizontal lines
	for (int i = 0; i <= numLines - 1; i++) {
	    int y = static_cast<int>(yInterval * i + 1);
		vertical_line_coords[i] = y;
	}
}

QPointF BoardWidget::GameCoordtoPixel(int row, int column)
{
	QPointF position;
	position.setX(vertical_line_coords[row]);
	position.setY(horizontal_line_coords[column]);
	return position;

}

QPoint BoardWidget::PixelCoordtoGame(QPoint Position)
{
	int x = horizontal_line_coords.size() - 1;
	int y = vertical_line_coords.size() - 1;

	while (Position.x() < horizontal_line_coords[x] && x != 0)
	{
		x--;
		if (x > 800) x = 800;
		if (x < 0) x = 0;
	}
	//if(MousePos.x() - xLinesPixelValues[x] > xLinesPixelValues[x] - MousePos.x()){x++;}

	while (Position.y() < vertical_line_coords[y] && x != 0)
	{
		y--;
		if (y > 800) y = 800;
		if (y < 0) y = 0;
	}
	//if(MousePos.y() - yLinesPixelValues[y] > yLinesPixelValues[y] - MousePos.y()){y++;}

	QPoint PiecePos;
	PiecePos.setX(x);
	PiecePos.setY(y);
	//qDebug() <<"LinesValues(" << xLinesPixelValues[x] << "," << yLinesPixelValues[y] << ")" << "slotPiece(" << x << "," << y << ") MousePos = " << MousePos;
	return PiecePos;
}

void BoardWidget::PlacePeiceSL(QPoint pos)
{
	QPoint Position = PixelCoordtoGame(pos);
	m_innerGame->PlacePiece(Position.x(),Position.y(),m_innerGame->getCurrentPlayer());
	m_canvas->m_updatePeices = true;
	m_canvas->update();
	//qDebug() << "slot activated" << " x " << Position.x() << " y " << Position.y();
}

//void BoardWidget::mouseMoveEvent(QMouseEvent* e)
//{
//	
//	QWidget::mouseMoveEvent(e);
//	m_mousePos.setY(e->y());
//	m_mousePos.setX(e->x());
//	m_mousePos = slotPiece(m_mousePos);
//	m_canvas->m_updateOverlay = true;
//	m_canvas->update();
//
//}
//
//void BoardWidget::mousePressEvent(QMouseEvent* e)
//{
//	//emit PlacePieceSG(x, y, 1);
//	//qDebug() << "Mouse Pressed";
//	QWidget::mousePressEvent(e);
//}