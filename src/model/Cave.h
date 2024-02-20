#ifndef CAVE_H_
#define CAVE_H_

#include <chrono>
#include <fstream>
#include <random>
#include <thread>
#include <vector>

#include "Matrix.h"

namespace s21 {
class Cave {
 public:
  Cave();
  Cave(int rows, int cols, int live_chance);
  explicit Cave(const std::string &path_file);

  s21::Matrix GetCave();
  float GetSizeRow();
  float GetSizeCol();

  void NextStep(int death_limit, int birth_limit);
  bool NotEq();
  void Pause(int milisec);
  void SaveCaveToFile(std::string path_file);

 private:
  int cols_;  //столбцы
  int rows_;  //ряды
  s21::Matrix cave_;
  s21::Matrix next_step_;
  bool flag{false};

  void FillRandom(int live_chance);
  int Random100();
  int CountNeighboors(int row, int col);
  void LoadCaveFromFile(std::string path_file);
};

}  // namespace s21

#endif  // CAVE_H_
