#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_CreateMaze_clicked() {
  ui->widget_maze->Maze_ = s21::ControllerMaze(y_maze, x_maze);
  ui->widget_maze->repaint();
}

void MainWindow::on_spinBox_XMaze_valueChanged(int arg1) { x_maze = arg1; }

void MainWindow::on_spinBox_YMaze_valueChanged(int arg1) { y_maze = arg1; }

void MainWindow::on_pushButton_LoadMaze_clicked() {
  QString openfile;
  openfile.isNull();
  openfile = QFileDialog::getOpenFileName(
      this, "OpenFile", QDir::homePath() + "/A1_Maze/", "TXT file (*.txt)");
  if ((openfile) != QString("")) {
    ui->widget_maze->Maze_ = s21::ControllerMaze(openfile.toStdString());
    ui->widget_maze->repaint();
  }
}

void MainWindow::on_pushButton_SaveMaze_clicked() {
  QString savefile = "/0";
  savefile = QFileDialog::getSaveFileName(this, "SaveFile",
                                          QDir::homePath() + "/A1_Maze/.txt",
                                          tr("TXT file (*.txt)"));
  ui->widget_maze->Maze_.SaveMazeToFile(savefile.toStdString());
}

void MainWindow::on_pushButton_CreateCave_clicked() {
  ui->widget_cave->Cave_ = s21::ControllerCave(y_cave, x_cave, chance_cave);
  ui->widget_cave->repaint();
}

void MainWindow::on_pushButton_NextStep_clicked() {
  ui->widget_cave->Cave_.NextStep(death_limit, birth_limit);
  ui->widget_cave->repaint();
}

void MainWindow::on_spinBox_XCave_valueChanged(int arg1) { x_cave = arg1; }

void MainWindow::on_spinBox_YCave_valueChanged(int arg1) { y_cave = arg1; }

void MainWindow::on_spinBox_ChanceCave_valueChanged(int arg1) {
  chance_cave = arg1;
}

void MainWindow::on_spinBox_LimitBorn_valueChanged(int arg1) {
  birth_limit = arg1;
}

void MainWindow::on_spinBox_LimitDaeth_valueChanged(int arg1) {
  death_limit = arg1;
}

void MainWindow::on_pushButton_SaveCave_clicked() {
  QString savefile = "/0";
  savefile = QFileDialog::getSaveFileName(this, "SaveFile",
                                          QDir::homePath() + "/A1_Maze/.txt",
                                          tr("TXT file (*.txt)"));
  ui->widget_cave->Cave_.SaveCaveToFile(savefile.toStdString());
}

void MainWindow::on_pushButton_LoadCave_clicked() {
  QString openfile;
  openfile.isNull();
  openfile = QFileDialog::getOpenFileName(
      this, "OpenFile", QDir::homePath() + "/A1_Maze/", "TXT file (*.txt)");
  if ((openfile) != QString("")) {
    ui->widget_cave->Cave_ = s21::ControllerCave(openfile.toStdString());
    ui->widget_cave->repaint();
  }
}

void MainWindow::on_pushButton_AutoStep_clicked() {
  if (ui->widget_cave->Cave_.GetSizeCol() != 0 ||
      ui->widget_cave->Cave_.GetSizeRow() != 0) {
    while (ui->widget_cave->Cave_.NotEq()) {
      ui->widget_cave->Cave_.NextStep(death_limit, birth_limit);
      ui->widget_cave->repaint();
      Pause(milisec);
    }
  }
}

void MainWindow::Pause(int delay) {
  QEventLoop el;
  QTimer::singleShot(delay, &el, SLOT(quit()));
  el.exec();
}

void MainWindow::on_spinBox_AutoStep_valueChanged(int arg1) { milisec = arg1; }
