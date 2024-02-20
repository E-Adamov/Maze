#include "PathMaze.h"

s21::PathMaze::PathMaze() {}

s21::PathMaze::PathMaze(Maze maze) {
  maze_ = maze;
  int rows = maze.GetRows();
  int cols = maze.GetCols();
  visit_matrix_ = s21::Matrix(rows, cols);
}

void s21::PathMaze::SearchPath(int start_row, int start_col, int end_row,
                               int end_col) {
  if (maze_.GetRows() > 0 && maze_.GetCols() > 0) {
    s21::Point start_point = s21::Point(start_row, start_col);
    s21::Point end_point = s21::Point(end_row, end_col);
    position_ = start_point;
    AddPosition();
    while (position_ != end_point) {
      if (SelectNextPosition()) {
        AddPosition();
      } else if (path_.size() != 0) {
        DeletePosition();
      }
    }
    VectorPathDraw();
  }
}

std::vector<s21::Point> s21::PathMaze::GetPath() { return path_; }

void s21::PathMaze::VectorPathDraw() {
  draw_path_.clear();
  float size_row = maze_.GetSizeRow();
  float size_col = maze_.GetSizeCol();
  for (long unsigned int i = 0; i < path_.size(); i++) {
    draw_path_.push_back((path_[i].GetCol() * size_col + size_col / 2));
    draw_path_.push_back((path_[i].GetRow() * size_row + size_row / 2));
  }
}

std::vector<float> s21::PathMaze::GetVectorPathDraw() { return draw_path_; }

void s21::PathMaze::AddPoint(float x, float y) {
  float size_row = maze_.GetSizeRow();
  float size_col = maze_.GetSizeCol();
  float num_row = floor(y / size_row);
  float num_col = floor(x / size_col);
  if (two_point_coordinate_.size() == 4) {
    two_point_coordinate_.clear();
    two_point_number_.clear();
    path_.clear();
    draw_path_.clear();
    visit_matrix_.CleanMatrix();
  }
  two_point_coordinate_.push_back(((num_col) + 0.5) * size_col);
  two_point_number_.push_back(num_col);
  two_point_coordinate_.push_back(((num_row) + 0.5) * size_row);
  two_point_number_.push_back(num_row);
}

std::vector<float> s21::PathMaze::GetTwoPointC() {
  return two_point_coordinate_;
}

std::vector<float> s21::PathMaze::GetTwoPointN() { return two_point_number_; }

bool s21::PathMaze::DownIsWall() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  return maze_.GetHorizonalWall(row, col);
}

bool s21::PathMaze::UpIsWall() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  return row - 1 < 0 ? true : maze_.GetHorizonalWall(row - 1, col);
}

bool s21::PathMaze::RightIsWall() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  return maze_.GetVerticalWall(row, col);
}

bool s21::PathMaze::LeftIsWall() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  return col - 1 < 0 ? true : maze_.GetVerticalWall(row, col - 1);
}

s21::Point s21::PathMaze::UpPoint() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  s21::Point point = s21::Point(row - 1, col);
  return point;
}

s21::Point s21::PathMaze::DownPoint() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  s21::Point point = s21::Point(row + 1, col);
  return point;
}

s21::Point s21::PathMaze::RightPoint() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  s21::Point point = s21::Point(row, col + 1);
  return point;
}

s21::Point s21::PathMaze::LeftPoint() {
  int row = position_.GetRow();
  int col = position_.GetCol();
  s21::Point point = s21::Point(row, col - 1);
  return point;
}

bool s21::PathMaze::SelectNextPosition() {
  bool res = false;
  if (UpIsWall() == false && IsPointVisit(UpPoint()) == false) {
    res = true;
    position_ = UpPoint();
  } else if (RightIsWall() == false && IsPointVisit(RightPoint()) == false) {
    res = true;
    position_ = RightPoint();
  } else if (DownIsWall() == false && IsPointVisit(DownPoint()) == false) {
    res = true;
    position_ = DownPoint();
  } else if (LeftIsWall() == false && IsPointVisit(LeftPoint()) == false) {
    res = true;
    position_ = LeftPoint();
  }
  return res;
}

int s21::PathMaze::IsPointVisit(Point point) {
  int res = true;
  int row = point.GetRow();
  int col = point.GetCol();
  if (row <= visit_matrix_.GetNumRows() &&
      col <= visit_matrix_.GetNumColumns() && row >= 0 && col >= 0)
    res = visit_matrix_(row, col);
  return res;
}

void s21::PathMaze::AddPosition() {
  path_.push_back(position_);
  int row = position_.GetRow();
  int col = position_.GetCol();
  visit_matrix_(row, col) = true;
}

void s21::PathMaze::DeletePosition() {
  path_.pop_back();
  position_ = path_.back();
}
