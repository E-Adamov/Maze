#ifndef CAVEDREW_H
#define CAVEDREW_H

#include <QPainter>
#include <QWidget>

#include "../controller/ControllerCave.h"

class CaveDrew : public QWidget {
  Q_OBJECT

 public:
  explicit CaveDrew(QWidget *parent = nullptr);
  s21::ControllerCave Cave_;
  void DrawFrame(QPainter *painter);
  void DrawCave(QPainter *painter);

 protected:
  void paintEvent(QPaintEvent *) override;
};

#endif  // CAVEDREW_H
