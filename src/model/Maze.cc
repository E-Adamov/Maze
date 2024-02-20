#include "Maze.h"

s21::Maze::Maze() {}

s21::Maze::Maze(int rows, int cols)
    : vertical_(rows, cols), horizontal_(rows, cols) {
  rows_ = rows;
  cols_ = cols;
  Generate();
  VectorToMazeDraw();
}

s21::Maze::Maze(const std::string &path_file) {
  LoadMazeFromFile(path_file);
  VectorToMazeDraw();
}

void s21::Maze::SaveMazeToFile(std::string path_file) {
  std::ofstream out(path_file);
  {
    out << "Maze" << std::endl;
    out << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        out << vertical_(i, j) << " ";
      }
      out << std::endl;
    }
    out << std::endl;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        out << horizontal_(i, j) << " ";
      }
      out << std::endl;
    }
  }
}

void s21::Maze::LoadMazeFromFile(std::string path_file) {
  std::ifstream in(path_file);
  std::string str;
  in >> str;
  if (str == "Maze") {
    in >> rows_ >> cols_;
    vertical_ = s21::Matrix(rows_, cols_);
    horizontal_ = s21::Matrix(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        in >> vertical_(r, c);
      }
    }
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        in >> horizontal_(r, c);
      }
    }
  }
}

int s21::Maze::GetRows() { return rows_; }

int s21::Maze::GetCols() { return cols_; }

int s21::Maze::GetHorizonalWall(int row, int col) {
  return horizontal_(row, col);
}

int s21::Maze::GetVerticalWall(int row, int col) { return vertical_(row, col); }

void s21::Maze::Generate() { /* Генерация по алгоритму Эллера*/
  if (rows_ > 0 && cols_ > 0) {
    /* Добавление первой строки */
    AddFirstLine();
    for (int r = 0; r < rows_ - 1; r++) {
      /* Присваиваем ячейкам свое уникальное множество */
      AddUniqueSet();
      /* Добавление правой вертикальной стенки */
      AddVerticalWalls(r);
      /* Добавление нижней горизонтальной стенки */
      AddHorizontalWalls(r);
      /* Проверка условие 4.1 и 4.2 */
      CheckedHorizontalWalls(r);
      /* Подготовка новой линии */
      PreparatingNewLine(r);
    }
    /* Добавление последней строки */
    AddEndLine();
  }
}

float s21::Maze::GetSizeRow() { return 500.0 / GetRows(); }

float s21::Maze::GetSizeCol() { return 500.0 / GetCols(); }

void s21::Maze::VectorToMazeDraw() {
  int c, r;
  float size_row = GetSizeRow();
  float size_col = GetSizeCol();
  for (r = 0; r < GetRows(); r++) {
    for (c = 0; c < GetCols(); c++) {
      if (vertical_(r, c) == true) {
        draw_maze_.push_back((c * size_col + size_col));
        draw_maze_.push_back((r * size_row));
        draw_maze_.push_back((c * size_col + size_col));
        draw_maze_.push_back((r * size_row + size_row));
      }
      if (horizontal_(r, c) == true) {
        draw_maze_.push_back((c * size_col));
        draw_maze_.push_back((r * size_row + size_row));
        draw_maze_.push_back((c * size_col + size_col));
        draw_maze_.push_back((r * size_row + size_row));
      }
    }
  }
}

std::vector<float> s21::Maze::GetVectorMazeDraw() { return draw_maze_; }

void s21::Maze::AddFirstLine() { row_sets_ = std::vector<int>(cols_); }

void s21::Maze::AddUniqueSet() {
  for (int i = 0; i < cols_; i++) {
    /* Проверяем на пустую ячейку */
    if (row_sets_[i] == 0) {
      /* Присваиваем ячейки уникальное множество */
      row_sets_[i] = counter_;
      counter_++;
    }
  }
}

void s21::Maze::AddVerticalWalls(int row) {
  for (int i = 0; i < cols_ - 1; i++) {
    /* Ставим стенку или нет */
    bool choise = RandomBool();
    /* Проверка условия для предотовращения зацикливания */
    if (choise == true || row_sets_[i] == row_sets_[i + 1]) {
      vertical_(row, i) = true;
    } else {
      /* Объединение ячеек в одно множество */
      MergeSets(i, row_sets_[i]);
    }
  }
  /* Добавление правой стенки в последней ячейки */
  vertical_(row, cols_ - 1) = true;
}

void s21::Maze::AddHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    /* Ставим стенку или нет */
    bool choise = RandomBool();
    /* Проверка, что множество имеет более одной ячейки (это предовратит
     * замкнутые области  */
    if (CalculateUniqueSet(row_sets_[i]) != 1 && choise == true) {
      /* Ставим горизонтальную стенку */
      horizontal_(row, i) = true;
    }
  }
}

int s21::Maze::CalculateUniqueSet(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < cols_; i++) {
    if (row_sets_[i] == element) {
      countUniqSet++;
    }
  }
  return countUniqSet;
}

void s21::Maze::CheckedHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    if (CalculateHorizontalWalls(row_sets_[i], row) == 0) {
      horizontal_(row, i) = false;
    }
  }
}

int s21::Maze::CalculateHorizontalWalls(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < cols_; i++) {
    if (row_sets_[i] == element && horizontal_(row, i) == false) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

void s21::Maze::PreparatingNewLine(int row) {
  for (int i = 0; i < cols_; i++) {
    if (horizontal_(row, i) == true) {
      /* Присваиваем ячейки пустое множество */
      row_sets_[i] = 0;
    }
  }
}

void s21::Maze::AddEndLine() {
  AddUniqueSet();
  AddVerticalWalls(rows_ - 1);
  CheckedEndLine();
}

void s21::Maze::CheckedEndLine() {
  for (int i = 0; i < cols_ - 1; i++) {
    /* Проверка условия пункта 5.2.1 */
    if (row_sets_[i] != row_sets_[i + 1]) {
      /* Убираем вертикальную стенку */
      vertical_(rows_ - 1, i) = false;
      /* Объединяем множества */
      MergeSets(i, row_sets_[i]);
    }
    /* Добавляем горизонтальные стенки */
    horizontal_(rows_ - 1, i) = true;
  }
  /* Добавляем горизонтальную стенку в последней ячейке */
  horizontal_(rows_ - 1, cols_ - 1) = true;
}

void s21::Maze::MergeSets(int index, int element) {
  int mutable_set = row_sets_[index + 1];
  for (int i = 0; i < cols_; i++) {
    /* Проверка ячеек на одно множество */
    if (row_sets_[i] == mutable_set) {
      /* Объединение ячейки в множество */
      row_sets_[i] = element;
    }
  }
}

bool s21::Maze::RandomBool() {
  std::random_device rd;
  return rd() % 2;
}
