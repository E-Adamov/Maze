#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

namespace s21 {
class Matrix {
 public:
  Matrix();
  Matrix(const int &rows, const int &cols);

  int GetNumRows() const;
  int GetNumColumns() const;

  int &operator()(int row, int col);
  bool operator==(s21::Matrix &other);

  void SetSizeMatrix(const int &rows, const int &cols);
  void CleanMatrix();

 private:
  std::vector<std::vector<int>> matrix_;
};

}  // namespace s21

#endif  // MATRIX_H_
