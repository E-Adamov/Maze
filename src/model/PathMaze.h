#ifndef PATHMAZE_H_
#define PATHMAZE_H_

#include <vector>

#include "Matrix.h"
#include "Maze.h"
#include "Point.h"

namespace s21 {
class PathMaze {
 public:
  PathMaze();
  explicit PathMaze(s21::Maze maze);

  void SearchPath(int start_row, int start_col, int end_row, int end_col);
  void VectorPathDraw();
  void AddPoint(float x, float y);
  std::vector<float> GetVectorPathDraw();
  std::vector<float> GetTwoPointC();
  std::vector<float> GetTwoPointN();
  std::vector<s21::Point> GetPath();

 private:
  s21::Maze maze_;
  s21::Matrix visit_matrix_;
  std::vector<s21::Point> path_;
  s21::Point position_;
  std::vector<float> draw_path_;
  std::vector<float> two_point_coordinate_;
  std::vector<float> two_point_number_;

  bool DownIsWall();
  bool UpIsWall();
  bool RightIsWall();
  bool LeftIsWall();
  s21::Point UpPoint();
  s21::Point DownPoint();
  s21::Point RightPoint();
  s21::Point LeftPoint();
  bool SelectNextPosition();
  int IsPointVisit(s21::Point point);
  void AddPosition();
  void DeletePosition();
};

}  // namespace s21

#endif  // PATHMAZE_H_
