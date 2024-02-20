#include "cavedrew.h"

CaveDrew::CaveDrew(QWidget *parent) : QWidget{parent} {}

void CaveDrew::DrawFrame(QPainter *painter) {
  painter->setPen(QPen(Qt::black, 4, Qt::SolidLine));
  QColor color_back(180, 180, 180, 255);
  painter->setBrush(QBrush(color_back, Qt::SolidPattern));
  painter->drawRect(0, 0, 500, 500);
}

void CaveDrew::DrawCave(QPainter *painter) {
  if (Cave_.GetCave().GetNumColumns() > 0) {
    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    float x = Cave_.GetSizeCol();
    float y = Cave_.GetSizeRow();
    for (int r = 0; r < Cave_.GetCave().GetNumRows(); r++) {
      for (int c = 0; c < Cave_.GetCave().GetNumColumns(); c++) {
        if (Cave_.GetCave()(r, c) == 1) {
          painter->drawRect(c * x, r * y, x, y);
        }
      }
    }
  }
}

void CaveDrew::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  DrawFrame(&painter);
  DrawCave(&painter);
}
