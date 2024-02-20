#include "mazedrew.h"

MazeDrew::MazeDrew(QWidget *parent) : QWidget{parent} {}

void MazeDrew::DrawFrame(QPainter *painter) {
  painter->setPen(QPen(Qt::black, 4, Qt::SolidLine));
  QColor color_back(180, 180, 180, 255);
  painter->setBrush(QBrush(color_back, Qt::SolidPattern));
  painter->drawRect(0, 0, 500, 500);
}

void MazeDrew::DrawMaze(QPainter *painter) {
  painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
  for (int i = 0; i < Maze_.GetVectorMazeDraw().size(); i = i + 4) {
    painter->drawLine(
        Maze_.GetVectorMazeDraw()[i], Maze_.GetVectorMazeDraw()[i + 1],
        Maze_.GetVectorMazeDraw()[i + 2], Maze_.GetVectorMazeDraw()[i + 3]);
  }
}

void MazeDrew::DrawPath(QPainter *painter) {
  painter->setPen(QPen(Qt::red, 2, Qt::SolidLine));
  if (!Maze_.GetVectorPathDraw().empty()) {
    for (int i = 0; i < (Maze_.GetVectorPathDraw().size()) - 2; i = i + 2) {
      painter->drawLine(
          Maze_.GetVectorPathDraw()[i], Maze_.GetVectorPathDraw()[i + 1],
          Maze_.GetVectorPathDraw()[i + 2], Maze_.GetVectorPathDraw()[i + 3]);
    }
  }
}

void MazeDrew::DrawPoint(QPainter *painter) {
  if (!Maze_.GetVectorMazeDraw().empty()) {
    if (!Maze_.GetTwoPointC().empty()) {
      painter->setPen(QPen(Qt::red, 10, Qt::SolidLine));
      if (Maze_.GetTwoPointC().size() == 2) {
        painter->drawPoint(Maze_.GetTwoPointC()[0], Maze_.GetTwoPointC()[1]);
      } else if (Maze_.GetTwoPointC().size() == 4) {
        painter->drawPoint(Maze_.GetTwoPointC()[0], Maze_.GetTwoPointC()[1]);
        painter->drawPoint(Maze_.GetTwoPointC()[2], Maze_.GetTwoPointC()[3]);
        Maze_.SearchPath(Maze_.GetTwoPointN()[1], Maze_.GetTwoPointN()[0],
                         Maze_.GetTwoPointN()[3], Maze_.GetTwoPointN()[2]);
        DrawPath(painter);
      }
    }
  }
}

void MazeDrew::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  DrawFrame(&painter);
  DrawMaze(&painter);
  DrawPoint(&painter);
}

void MazeDrew::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    float x = event->pos().x();
    float y = event->pos().y();
    Maze_.AddPoint(x, y);
    repaint();
  }
}
