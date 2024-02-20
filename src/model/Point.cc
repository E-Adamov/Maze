#include "Point.h"

s21::Point::Point() {}

s21::Point::Point(int row, int col) {
  row_ = row;
  col_ = col;
}

int s21::Point::GetRow() { return row_; }

int s21::Point::GetCol() { return col_; }

bool s21::Point::operator!=(const Point &other) {
  bool res = true;
  if (row_ == other.row_ && col_ == other.col_) res = false;
  return res;
}
