#ifndef POINT_H_
#define POINT_H_

namespace s21 {
class Point {
 public:
  Point();
  Point(int row, int col);

  int GetRow();
  int GetCol();

  bool operator!=(const s21::Point &other);

 private:
  int row_;
  int col_;
};
}  // namespace s21

#endif  // POINT_H_
