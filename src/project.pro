TEMPLATE = app
TARGET = labyrinth2015
INCLUDEPATH += . coresrc gui
LIBS += -lboost_serialization
CONFIG += staticlib
CONFIG += warn_off
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -static-libstdc++
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS += coresrc/CardPack.h \
           coresrc/Game.h \
           coresrc/MazeBoard.h \
           coresrc/MazeCard.h \
           coresrc/MazeField.h \
           coresrc/Player.h \
           coresrc/Treasure.h \
           coresrc/TreasureCard.h \
           gui/GCardPack.h \
           gui/GFreeCard.h \
           gui/GMazeBoard.h \
           gui/GMazeCard.h \
           gui/GNewGameDialog.h \
           gui/GPlayer.h \
           gui/GTreasure.h \
           gui/MainWindow.h
FORMS += gui/GNewGameDialog.ui gui/MainWindow.ui
SOURCES += coresrc/CardPack.cpp \
           coresrc/Game.cpp \
           coresrc/MazeBoard.cpp \
           coresrc/MazeCard.cpp \
           coresrc/MazeField.cpp \
           coresrc/Player.cpp \
           coresrc/Treasure.cpp \
           coresrc/TreasureCard.cpp \
           gui/GCardPack.cpp \
           gui/GFreeCard.cpp \
           gui/GMazeBoard.cpp \
           gui/GMazeCard.cpp \
           gui/GNewGameDialog.cpp \
           gui/GPlayer.cpp \
           gui/GTreasure.cpp \
           gui/main.cpp \
           gui/MainWindow.cpp
RESOURCES += gui/resources.qrc
