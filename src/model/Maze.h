#ifndef MAZE_H_
#define MAZE_H_

#include <fstream>
#include <random>
#include <vector>

#include "Matrix.h"

namespace s21 {
class Maze {
 public:
  Maze();
  Maze(int rows, int cols);
  explicit Maze(const std::string &path_file);

  void SaveMazeToFile(std::string path_file);

  int GetRows();
  int GetCols();
  float GetSizeRow();
  float GetSizeCol();
  int GetHorizonalWall(int row, int col);
  int GetVerticalWall(int row, int col);
  std::vector<float> GetVectorMazeDraw();

 private:
  int cols_;  //столбцы
  int rows_;  //ряды
  s21::Matrix vertical_;
  s21::Matrix horizontal_;

  std::vector<int> row_sets_;
  int counter_{1};
  std::vector<float> draw_maze_;

  void LoadMazeFromFile(std::string path_file);
  void Generate();
  void VectorToMazeDraw();
  bool RandomBool();

  void AddFirstLine();
  void AddUniqueSet();
  void AddVerticalWalls(int row);
  void AddHorizontalWalls(int row);
  int CalculateUniqueSet(int element);
  void CheckedHorizontalWalls(int row);
  int CalculateHorizontalWalls(int element, int row);
  void PreparatingNewLine(int row);
  void AddEndLine();
  void CheckedEndLine();
  void MergeSets(int index, int element);
};

}  // namespace s21

#endif  // MAZE_H_
