macx: {
QT += core gui openglwidgets
}
unix:!macx {
QT += core gui opengl widgets
LIBS += -lglut -lGLU
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 warn_off

#TARGET = A1_Maze

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/Cave.cc \
    ../model/Matrix.cc \
    ../model/Maze.cc \
    ../model/PathMaze.cc \
    ../model/Point.cc \
    ../view/cavedrew.cpp \
    ../view/main.cpp \
    ../view/mainwindow.cpp \
    ../view/mazedrew.cpp

HEADERS += \
    ../controller/ControllerCave.h \
    ../controller/ControllerMaze.h \
    ../model/Cave.h \
    ../model/Matrix.h \
    ../model/Maze.h \
    ../model/PathMaze.h \
    ../model/Point.h \
    ../view/cavedrew.h \
    ../view/mainwindow.h \
    ../view/mazedrew.h

FORMS += \
    ../view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
