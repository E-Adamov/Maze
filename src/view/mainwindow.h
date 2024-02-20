#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QEventLoop>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_CreateMaze_clicked();
  void on_spinBox_XMaze_valueChanged(int arg1);
  void on_spinBox_YMaze_valueChanged(int arg1);
  void on_pushButton_LoadMaze_clicked();
  void on_pushButton_SaveMaze_clicked();

  void on_pushButton_CreateCave_clicked();
  void on_pushButton_NextStep_clicked();
  void on_pushButton_SaveCave_clicked();
  void on_pushButton_LoadCave_clicked();
  void on_pushButton_AutoStep_clicked();
  void on_spinBox_XCave_valueChanged(int arg1);
  void on_spinBox_YCave_valueChanged(int arg1);
  void on_spinBox_ChanceCave_valueChanged(int arg1);
  void on_spinBox_LimitBorn_valueChanged(int arg1);
  void on_spinBox_LimitDaeth_valueChanged(int arg1);
  void on_spinBox_AutoStep_valueChanged(int arg1);

 private:
  Ui::MainWindow *ui;
  int x_maze{10}, y_maze{10};
  int x_cave{50}, y_cave{50}, chance_cave{40};
  int death_limit{3}, birth_limit{4};
  int milisec{100};
  void Pause(int delay);
};
#endif  // MAINWINDOW_H
