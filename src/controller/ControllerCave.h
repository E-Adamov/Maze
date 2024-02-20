#ifndef CONTROLLERCAVE_H_
#define CONTROLLERCAVE_H_

#include "../model/Cave.h"

namespace s21 {

class ControllerCave {
 public:
  ControllerCave() {}

  ControllerCave(int rows, int cols, int live_chance)
      : cave_(rows, cols, live_chance) {}

  explicit ControllerCave(const std::string &path_file) : cave_(path_file) {}

  void SaveCaveToFile(const std::string &path_file) {
    cave_.SaveCaveToFile(path_file);
  }

  void NextStep(int death_limit, int birth_limit) {
    cave_.NextStep(death_limit, birth_limit);
  }

  s21::Matrix GetCave() { return cave_.GetCave(); }

  float GetSizeRow() { return cave_.GetSizeRow(); }

  float GetSizeCol() { return cave_.GetSizeCol(); }

  bool NotEq() { return cave_.NotEq(); }

  void Pause(int milisec) { cave_.Pause(milisec); }

 private:
  s21::Cave cave_;
};

}  // namespace s21

#endif  // CONTROLLERCAVE_H_