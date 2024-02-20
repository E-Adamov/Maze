#include <gtest/gtest.h>
#include <vector>

#include "../model/Cave.cc"
#include "../model/Matrix.cc"
#include "../model/Maze.cc"
#include "../model/PathMaze.cc"
#include "../model/Point.cc"

TEST(maze, generate) {
  s21::Maze maze_test;
  maze_test = s21::Maze(50, 50);
  ASSERT_EQ(maze_test.GetCols(), 50);
  ASSERT_EQ(maze_test.GetRows(), 50);
}

TEST(maze, save) {
  s21::Maze maze_test;
  maze_test = s21::Maze("./test/maze_test.txt");
  maze_test.SaveMazeToFile("./test/maze_test.txt");
}

TEST(maze, load) {
  s21::Maze maze_test;
  maze_test = s21::Maze("./test/maze_test.txt");
  ASSERT_EQ(maze_test.GetCols(), 30);
  ASSERT_EQ(maze_test.GetRows(), 30);
  ASSERT_EQ(maze_test.GetHorizonalWall(0, 0), 1);
  ASSERT_EQ(maze_test.GetVerticalWall(0, 0), 0);
}

TEST(maze, path) {
  s21::Maze maze_test;
  maze_test = s21::Maze("./test/maze_test.txt");
  maze_test.GetVectorMazeDraw();

  s21::PathMaze path_test;
  path_test = s21::PathMaze(maze_test);
  path_test.SearchPath(0, 0, 29, 29);

  path_test.AddPoint(5, 5);
  path_test.AddPoint(495, 495);
  path_test.AddPoint(5, 5);
  path_test.AddPoint(495, 495);
  path_test.GetPath();
  path_test.GetVectorPathDraw();

  path_test.GetTwoPointN();
  path_test.GetTwoPointC();
}

TEST(cave, generate) {
  s21::Cave cave_test;
  cave_test = s21::Cave(50, 50, 40);
  ASSERT_EQ(cave_test.GetCave().GetNumColumns(), 50);
  ASSERT_EQ(cave_test.GetCave().GetNumRows(), 50);
}

TEST(cave, load) {
  s21::Cave cave_test;
  cave_test = s21::Cave("./test/cave_test.txt");
  ASSERT_EQ(cave_test.GetCave().GetNumColumns(), 30);
  ASSERT_EQ(cave_test.GetCave().GetNumRows(), 30);
}

TEST(cave, step) {
  s21::Cave cave_test;
  cave_test = s21::Cave("./test/cave_test.txt");

  while (cave_test.NotEq()) {
    cave_test.NextStep(3, 4);
    cave_test.Pause(1);
  }

  float size_cols = cave_test.GetSizeCol();
  float size_rows = cave_test.GetSizeRow();

  ASSERT_FLOAT_EQ(size_cols, 500.0 / 30);
  ASSERT_FLOAT_EQ(size_rows, 500.0 / 30);
}

TEST(cave, save) {
  s21::Cave cave_test;
  cave_test = s21::Cave("./test/cave_test.txt");
  cave_test.SaveCaveToFile("./test/cave_test.txt");
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
