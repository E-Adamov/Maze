#include "Cave.h"

s21::Cave::Cave() {
  rows_ = 0;
  cols_ = 0;
}

s21::Cave::Cave(int rows, int cols, int live_chance) {
  rows_ = rows;
  cols_ = cols;
  cave_ = s21::Matrix(rows_, cols_);
  FillRandom(live_chance);
  next_step_ = s21::Matrix(rows_, cols_);
}

s21::Cave::Cave(const std::string &path_file) { LoadCaveFromFile(path_file); }

s21::Matrix s21::Cave::GetCave() { return cave_; }

float s21::Cave::GetSizeRow() { return 500.0 / rows_; }

float s21::Cave::GetSizeCol() { return 500.0 / cols_; }

int s21::Cave::Random100() {
  std::random_device rd;
  return rd() % 100;
}

int s21::Cave::CountNeighboors(int row, int col) {
  int res = 0;
  for (int i = -1; i < 2; ++i) {
    for (int j = -1; j < 2; ++j) {
      if (i || j) {
        if ((row + i < 0) || (col + j < 0) || (row + i == rows_) ||
            (col + j == cols_)) {
          res++;
        } else {
          res += cave_((row + i), (col + j));
        }
      }
    }
  }
  return res;
}

void s21::Cave::NextStep(int death_limit, int birth_limit) {
  next_step_.CleanMatrix();
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      if (cave_(r, c) == 1) {
        if (CountNeighboors(r, c) < death_limit) {
          next_step_(r, c) = false;
        } else {
          next_step_(r, c) = true;
        }
      } else {
        if (CountNeighboors(r, c) > birth_limit) {
          next_step_(r, c) = true;
        } else {
          next_step_(r, c) = false;
        }
      }
    }
  }
  if (cave_ == next_step_) {
    flag = true;
  } else {
    flag = false;
  }
  cave_ = next_step_;
}

void s21::Cave::Pause(int milisec) {
  std::chrono::duration<int, std::milli> timespan(milisec);
  std::this_thread::sleep_for(timespan);
}

bool s21::Cave::NotEq() {
  bool res = true;
  if (flag) res = false;
  return res;
}

void s21::Cave::SaveCaveToFile(std::string path_file) {
  std::ofstream out(path_file);
  {
    out << "Cave" << std::endl;
    out << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        out << cave_(i, j) << " ";
      }
      out << std::endl;
    }
  }
}

void s21::Cave::FillRandom(int live_chance) {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      cave_(r, c) = (Random100() < live_chance ? 1 : 0);
    }
  }
}

void s21::Cave::LoadCaveFromFile(std::string path_file) {
  std::ifstream in(path_file);
  std::string str;
  in >> str;
  if (str == "Cave") {
    in >> rows_ >> cols_;
    cave_ = s21::Matrix(rows_, cols_);
    next_step_ = s21::Matrix(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        in >> cave_(r, c);
      }
    }
  }
}
