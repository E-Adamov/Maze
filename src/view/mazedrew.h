#ifndef MAZEDREW_H
#define MAZEDREW_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "../controller/ControllerMaze.h"

class MazeDrew : public QWidget {
  Q_OBJECT

 public:
  explicit MazeDrew(QWidget *parent = nullptr);
  s21::ControllerMaze Maze_;
  void DrawFrame(QPainter *painter);
  void DrawMaze(QPainter *painter);
  void DrawPath(QPainter *painter);
  void DrawPoint(QPainter *painter);

 protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent *event) override;
};

#endif  // MAZEDREW_H
