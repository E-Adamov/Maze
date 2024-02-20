#ifndef CONTROLLERMAZE_H_
#define CONTROLLERMAZE_H_

#include "../model/Maze.h"
#include "../model/PathMaze.h"

namespace s21 {

class ControllerMaze {
 public:
  ControllerMaze() {}

  ControllerMaze(int rows, int cols) : maze_(rows, cols) {
    path_maze_ = s21::PathMaze(maze_);
  }
  explicit ControllerMaze(const std::string &path_file) : maze_(path_file) {
    path_maze_ = s21::PathMaze(maze_);
  }

  void SaveMazeToFile(const std::string &path_file) {
    maze_.SaveMazeToFile(path_file);
  }

  int GetHorizonalWall(int row, int col) {
    return maze_.GetHorizonalWall(row, col);
  }
  int GetVerticalWall(int row, int col) {
    return maze_.GetVerticalWall(row, col);
  }

  std::vector<float> GetVectorMazeDraw() { return maze_.GetVectorMazeDraw(); }

  std::vector<float> GetVectorPathDraw() {
    return path_maze_.GetVectorPathDraw();
  }

  void SearchPath(int start_row, int start_col, int end_row, int end_col) {
    path_maze_.SearchPath(start_row, start_col, end_row, end_col);
  }

  std::vector<s21::Point> GetPath() { return path_maze_.GetPath(); }

  void AddPoint(float x, float y) { path_maze_.AddPoint(x, y); }

  std::vector<float> GetTwoPointC() { return path_maze_.GetTwoPointC(); }

  std::vector<float> GetTwoPointN() { return path_maze_.GetTwoPointN(); }

 private:
  s21::Maze maze_;
  s21::PathMaze path_maze_;
};

}  // namespace s21

#endif  // CONTROLLERMAZE_H_