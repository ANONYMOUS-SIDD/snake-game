# Core Qt Modules Required For The Application
QT += core gui widgets

# C++ Language Standard Configuration
CONFIG += c++17

# Source Files To Be Compiled
SOURCES += \
    gamescreen.cpp \
    homescreen.cpp \
    main.cpp \
    home.cpp \
    mainHomeScreen.cpp \
    snake.cpp \
    minesweeper.cpp \
    sudokuboard.cpp \
    sudokucontroller.cpp \
    sudokugame.cpp \
    sudokusolver.cpp

# Header Files Containing Class Declarations
HEADERS += \
    gamescreen.h \
    gamesizes.h \
    gamesizes.h \           # Add this line
    basegamescreen.h \       # Add this line (optional)
    home.h \
    homescreen.h \
    mainHomeScreen.h \
    snake.h \
    minesweeper.h \
    sudokuboard.h \
    sudokucontroller.h \
    sudokugame.h \
    sudokusolver.h

# UI Form Files (Currently Empty)
FORMS +=
