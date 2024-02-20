#include "Matrix.h"

s21::Matrix::Matrix() : matrix_({}) {}

s21::Matrix::Matrix(const int &rows, const int &cols) {
  SetSizeMatrix(rows, cols);
}

void s21::Matrix::SetSizeMatrix(const int &rows, const int &cols) {
  matrix_.resize(rows);
  for (int i = 0; i < rows; ++i) {
    matrix_.at(i).resize(cols);
  }
}

int s21::Matrix::GetNumRows() const { return matrix_.size(); }

int s21::Matrix::GetNumColumns() const {
  if (GetNumRows() > 0) {
    return matrix_[0].size();
  }
  return 0;
}

int &s21::Matrix::operator()(int row, int col) {
  return matrix_.at(row).at(col);
}

bool s21::Matrix::operator==(Matrix &other) {
  bool res = true;
  for (int r = 0; r < GetNumRows(); r++) {
    for (int c = 0; c < GetNumColumns(); c++) {
      if (matrix_[r][c] != other(r, c)) res = false;
    }
  }
  return res;
}

void s21::Matrix::CleanMatrix() {
  for (int r = 0; r < GetNumRows(); r++) {
    for (int c = 0; c < GetNumColumns(); c++) {
      matrix_.at(r).at(c) = 0;
    }
  }
}
