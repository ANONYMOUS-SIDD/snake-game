#include "gamescreen.h"
#include "sudokuboard.h"
#include "sudokusolver.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QApplication>
#include <QResizeEvent>

// Predefined puzzles (same as before)
static const QVector<QVector<QVector<int>>> easyPuzzles = {
    { // Puzzle 1
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    },
    { // Puzzle 2
        {0,0,0,2,0,0,0,6,3},
        {3,0,0,0,0,5,4,0,1},
        {0,0,1,0,0,3,9,8,0},
        {0,0,0,0,9,0,0,2,0},
        {0,5,0,1,0,2,0,9,0},
        {0,2,0,0,7,0,0,0,0},
        {0,8,5,3,0,0,6,0,0},
        {9,0,3,6,0,0,0,0,7},
        {6,1,0,0,0,9,0,0,0}
    },

    { // Puzzle 3
        {1,0,0,4,8,9,0,0,6},
        {7,3,0,0,0,0,0,4,0},
        {0,0,0,0,0,1,2,9,5},
        {0,0,7,1,2,0,6,0,0},
        {5,0,0,7,0,3,0,0,8},
        {0,0,6,0,9,5,7,0,0},
        {9,1,4,6,0,0,0,0,0},
        {0,2,0,0,0,0,0,3,7},
        {8,0,0,5,1,2,0,0,4}
    },

    { // Puzzle 4
        {0,2,0,6,0,8,0,0,0},
        {5,8,0,0,0,9,7,0,0},
        {0,0,0,0,4,0,0,1,0},
        {3,7,0,2,0,0,0,6,0},
        {0,0,0,0,9,0,0,0,0},
        {0,5,0,0,0,3,0,9,2},
        {0,9,0,0,1,0,0,0,0},
        {0,0,2,8,0,0,0,7,5},
        {0,0,0,9,0,4,0,3,0}
    },

    { // Puzzle 5
        {0,0,6,0,0,0,0,0,2},
        {0,0,0,3,0,5,0,0,0},
        {0,9,0,0,0,0,4,0,0},
        {8,0,0,0,0,0,0,0,0},
        {0,0,0,7,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,9},
        {0,0,1,0,0,0,0,6,0},
        {0,0,0,2,0,8,0,0,0},
        {6,0,0,0,0,0,3,0,0}
    },

    { // Puzzle 6
        {2,0,0,0,0,0,0,0,9},
        {0,0,0,6,0,0,0,0,0},
        {0,7,4,0,8,0,0,0,0},
        {0,0,0,0,0,3,0,0,2},
        {0,8,0,0,4,0,0,1,0},
        {6,0,0,5,0,0,0,0,0},
        {0,0,0,0,1,0,7,8,0},
        {0,0,0,0,0,6,0,0,0},
        {1,0,0,0,0,0,0,0,5}
    },

    { // Puzzle 7
        {0,0,0,0,6,0,4,0,0},
        {7,0,0,0,0,3,6,0,0},
        {0,0,0,0,9,1,0,8,0},
        {0,0,0,0,0,0,0,0,0},
        {0,5,0,1,8,0,0,0,3},
        {0,0,0,3,0,6,0,4,5},
        {0,4,0,2,0,0,0,6,0},
        {9,0,3,0,0,0,0,0,0},
        {0,2,0,0,0,0,1,0,0}
    },

    { // Puzzle 8
        {0,0,5,3,0,0,0,0,0},
        {8,0,0,0,0,0,0,2,0},
        {0,7,0,0,1,0,5,0,0},
        {4,0,0,0,0,5,3,0,0},
        {0,1,0,0,7,0,0,0,6},
        {0,0,3,2,0,0,0,8,0},
        {0,6,0,5,0,0,0,0,9},
        {0,0,4,0,0,0,0,3,0},
        {0,0,0,0,0,9,7,0,0}
    },

    { // Puzzle 9
        {3,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,6,0,0,0},
        {0,0,1,0,9,5,0,0,0},
        {0,0,0,5,0,0,0,0,0},
        {0,0,0,0,7,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,8,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,4,0}
    },

    { // Puzzle 10
        {0,4,0,0,0,0,8,0,5},
        {0,3,0,0,0,0,0,0,0},
        {0,0,0,7,0,0,0,0,0},
        {0,2,0,0,0,0,0,6,0},
        {0,0,0,0,8,0,4,0,0},
        {0,0,0,0,1,0,0,0,0},
        {0,0,0,6,0,3,0,7,0},
        {5,0,0,2,0,0,0,0,0},
        {1,0,4,0,0,0,0,0,0}
    },

    { // Puzzle 11
        {0,0,0,0,0,0,2,0,0},
        {0,8,0,0,0,7,0,9,0},
        {6,0,2,0,0,0,5,0,0},
        {0,7,0,0,6,0,0,0,0},
        {0,0,0,9,0,1,0,0,0},
        {0,0,0,0,2,0,0,4,0},
        {0,0,5,0,0,0,6,0,3},
        {0,9,0,4,0,0,0,7,0},
        {0,0,6,0,0,0,0,0,0}
    },

    { // Puzzle 12
        {0,0,0,0,7,0,0,0,9},
        {0,4,0,0,0,0,0,0,0},
        {0,0,8,0,0,0,0,3,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,5,0,9,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,6,0,0,0,0,8,0,0},
        {0,0,0,0,0,0,0,5,0},
        {3,0,0,0,1,0,0,0,0}
    },

    { // Puzzle 13
        {8,0,0,0,0,0,0,0,0},
        {0,0,3,6,0,0,0,0,0},
        {0,7,0,0,9,0,2,0,0},
        {0,5,0,0,0,7,0,0,0},
        {0,0,0,0,4,5,7,0,0},
        {0,0,0,1,0,0,0,3,0},
        {0,0,1,0,0,0,0,6,8},
        {0,0,8,5,0,0,0,1,0},
        {0,9,0,0,0,0,4,0,0}
    },

    { // Puzzle 14
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,3,0,8,5},
        {0,0,1,0,2,0,0,0,0},
        {0,0,0,5,0,7,0,0,0},
        {0,0,4,0,0,0,1,0,0},
        {0,9,0,0,0,0,0,0,0},
        {5,0,0,0,0,0,0,7,3},
        {0,0,2,0,1,0,0,0,0},
        {0,0,0,0,4,0,0,0,9}
    },

    { // Puzzle 15
        {0,0,0,3,0,0,0,0,0},
        {0,0,0,0,0,5,0,0,0},
        {0,0,0,0,0,0,0,7,0},
        {0,0,0,0,0,0,3,0,0},
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,6,0,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,8},
        {0,0,0,0,0,0,0,0,0}
    }
};

static const QVector<QVector<QVector<int>>> mediumPuzzles = {
    { // Puzzle 1
        {0,0,0,2,6,0,7,0,1},
        {6,8,0,0,7,0,0,9,0},
        {0,0,0,0,0,3,0,0,4},
        {3,0,0,0,0,0,0,8,0},
        {0,0,5,0,0,9,0,0,0},
        {0,7,0,0,1,0,0,0,6},
        {0,0,0,8,0,0,1,0,0},
        {0,1,0,0,3,0,0,4,0},
        {7,0,4,0,0,0,0,0,0}
    },
    { // Puzzle 2
        {0,2,0,6,0,8,0,0,0},
        {5,8,0,0,0,9,7,0,0},
        {0,0,0,0,4,0,0,1,0},
        {3,7,0,2,0,0,0,6,0},
        {0,0,0,0,9,0,0,0,0},
        {0,5,0,0,0,3,0,9,2},
        {0,9,0,0,1,0,0,0,0},
        {0,0,2,8,0,0,0,7,5},
        {0,0,0,9,0,4,0,3,0}
    },

    { // Puzzle 3
        {0,0,0,0,0,0,2,0,0},
        {0,8,0,0,0,7,0,9,0},
        {6,0,2,0,0,0,5,0,0},
        {0,7,0,0,6,0,0,0,0},
        {0,0,0,9,0,1,0,0,0},
        {0,0,0,0,2,0,0,4,0},
        {0,0,5,0,0,0,6,0,3},
        {0,9,0,4,0,0,0,7,0},
        {0,0,6,0,0,0,0,0,0}
    },

    { // Puzzle 4
        {1,0,0,0,0,7,0,9,0},
        {0,3,0,0,2,0,0,0,8},
        {0,0,9,6,0,0,5,0,0},
        {0,0,5,3,0,0,9,0,0},
        {0,1,0,0,8,0,0,0,2},
        {6,0,0,0,0,4,0,0,0},
        {3,0,0,0,0,0,0,1,0},
        {0,4,0,0,0,0,0,0,7},
        {0,0,7,0,0,0,3,0,0}
    },

    { // Puzzle 5
        {0,0,0,6,0,0,4,0,0},
        {7,0,0,0,0,3,6,0,0},
        {0,0,0,0,9,1,0,8,0},
        {0,0,0,0,0,0,0,0,0},
        {0,5,0,1,8,0,0,0,3},
        {0,0,0,3,0,6,0,4,5},
        {0,4,0,2,0,0,0,6,0},
        {9,0,3,0,0,0,0,0,0},
        {0,2,0,0,0,0,1,0,0}
    },

    { // Puzzle 6
        {0,0,0,0,0,0,0,1,2},
        {0,0,0,0,3,5,0,0,0},
        {0,0,0,7,0,0,0,0,0},
        {0,0,0,0,0,0,3,0,0},
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,6,0,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,8},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 7
        {0,6,0,0,0,0,0,0,0},
        {0,0,0,3,0,5,0,0,0},
        {0,0,0,0,0,0,4,0,0},
        {8,0,0,0,0,0,0,0,0},
        {0,0,0,7,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,9},
        {0,0,1,0,0,0,0,6,0},
        {0,0,0,2,0,8,0,0,0},
        {6,0,0,0,0,0,3,0,0}
    },

    { // Puzzle 8
        {2,0,0,0,0,0,0,0,9},
        {0,0,0,6,0,0,0,0,0},
        {0,7,4,0,8,0,0,0,0},
        {0,0,0,0,0,3,0,0,2},
        {0,8,0,0,4,0,0,1,0},
        {6,0,0,5,0,0,0,0,0},
        {0,0,0,0,1,0,7,8,0},
        {0,0,0,0,0,6,0,0,0},
        {1,0,0,0,0,0,0,0,5}
    },

    { // Puzzle 9
        {0,0,5,3,0,0,0,0,0},
        {8,0,0,0,0,0,0,2,0},
        {0,7,0,0,1,0,5,0,0},
        {4,0,0,0,0,5,3,0,0},
        {0,1,0,0,7,0,0,0,6},
        {0,0,3,2,0,0,0,8,0},
        {0,6,0,5,0,0,0,0,9},
        {0,0,4,0,0,0,0,3,0},
        {0,0,0,0,0,9,7,0,0}
    },

    { // Puzzle 10
        {3,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,6,0,0,0},
        {0,0,1,0,9,5,0,0,0},
        {0,0,0,5,0,0,0,0,0},
        {0,0,0,0,7,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,8,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,4,0}
    },

    { // Puzzle 11
        {0,4,0,0,0,0,8,0,5},
        {0,3,0,0,0,0,0,0,0},
        {0,0,0,7,0,0,0,0,0},
        {0,2,0,0,0,0,0,6,0},
        {0,0,0,0,8,0,4,0,0},
        {0,0,0,0,1,0,0,0,0},
        {0,0,0,6,0,3,0,7,0},
        {5,0,0,2,0,0,0,0,0},
        {1,0,4,0,0,0,0,0,0}
    },

    { // Puzzle 12
        {0,0,0,0,7,0,0,0,9},
        {0,4,0,0,0,0,0,0,0},
        {0,0,8,0,0,0,0,3,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,5,0,9,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,6,0,0,0,0,8,0,0},
        {0,0,0,0,0,0,0,5,0},
        {3,0,0,0,1,0,0,0,0}
    },

    { // Puzzle 13
        {8,0,0,0,0,0,0,0,0},
        {0,0,3,6,0,0,0,0,0},
        {0,7,0,0,9,0,2,0,0},
        {0,5,0,0,0,7,0,0,0},
        {0,0,0,0,4,5,7,0,0},
        {0,0,0,1,0,0,0,3,0},
        {0,0,1,0,0,0,0,6,8},
        {0,0,8,5,0,0,0,1,0},
        {0,9,0,0,0,0,4,0,0}
    },

    { // Puzzle 14
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,3,0,8,5},
        {0,0,1,0,2,0,0,0,0},
        {0,0,0,5,0,7,0,0,0},
        {0,0,4,0,0,0,1,0,0},
        {0,9,0,0,0,0,0,0,0},
        {5,0,0,0,0,0,0,7,3},
        {0,0,2,0,1,0,0,0,0},
        {0,0,0,0,4,0,0,0,9}
    },

    { // Puzzle 15
        {0,0,0,3,0,0,0,0,0},
        {0,0,0,0,0,5,0,0,0},
        {0,0,0,0,0,0,0,7,0},
        {0,0,0,0,0,0,3,0,0},
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,6,0,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,8},
        {0,0,0,0,0,0,0,0,0}
    }
};

static const QVector<QVector<QVector<int>>> hardPuzzles = {
    { // Puzzle 1
        {0,0,0,6,0,0,4,0,0},
        {7,0,0,0,0,3,6,0,0},
        {0,0,0,0,9,1,0,8,0},
        {0,0,0,0,0,0,0,0,0},
        {0,5,0,1,8,0,0,0,3},
        {0,0,0,3,0,6,0,4,5},
        {0,4,0,2,0,0,0,6,0},
        {9,0,3,0,0,0,0,0,0},
        {0,2,0,0,0,0,1,0,0}
    },
    { // Puzzle 2
        {0,8,0,0,0,9,0,3,0},
        {6,0,0,7,0,0,1,0,0},
        {0,2,0,0,4,0,0,0,9},
        {2,0,9,0,0,3,0,0,7},
        {0,0,0,0,1,0,0,0,0},
        {8,0,0,6,0,0,2,0,3},
        {4,0,0,0,9,0,0,7,0},
        {0,0,7,0,0,8,0,0,5},
        {0,3,0,5,0,0,0,1,0}
    },

    { // Puzzle 3
        {0,0,0,0,0,0,0,1,2},
        {0,0,0,0,3,5,0,0,0},
        {0,0,0,7,0,0,0,0,0},
        {0,0,0,0,0,0,3,0,0},
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,6,0,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,8},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 4
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,3,0,8,5},
        {0,0,1,0,2,0,0,0,0},
        {0,0,0,5,0,7,0,0,0},
        {0,0,4,0,0,0,1,0,0},
        {0,9,0,0,0,0,0,0,0},
        {5,0,0,0,0,0,0,7,3},
        {0,0,2,0,1,0,0,0,0},
        {0,0,0,0,4,0,0,0,9}
    },

    { // Puzzle 5
        {8,0,0,0,0,0,0,0,0},
        {0,0,3,6,0,0,0,0,0},
        {0,7,0,0,9,0,2,0,0},
        {0,5,0,0,0,7,0,0,0},
        {0,0,0,0,4,5,7,0,0},
        {0,0,0,1,0,0,0,3,0},
        {0,0,1,0,0,0,0,6,8},
        {0,0,8,5,0,0,0,1,0},
        {0,9,0,0,0,0,4,0,0}
    },

    { // Puzzle 6
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 7
        {0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,2,0,0,0},
        {0,0,0,0,3,0,0,0,0},
        {0,0,0,4,0,0,0,0,0},
        {0,0,5,0,0,0,0,0,0},
        {0,6,0,0,0,0,0,0,0},
        {7,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,8,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 8
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 9
        {1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,2},
        {0,0,0,0,0,3,0,0,0},
        {0,0,0,0,4,0,0,0,0},
        {0,0,0,5,0,0,0,0,0},
        {0,0,6,0,0,0,0,0,0},
        {0,7,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,8,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 10
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,9,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 11
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,2,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 12
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,3,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 13
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,4,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 14
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,5,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    },

    { // Puzzle 15
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,6,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    }
};
GameScreen::GameScreen(QWidget *parent) : QWidget(parent)
{
    selectedRow = selectedCol = -1;
    setupUI();
    solver = new SudokuSolver(this);
    connect(solver, &SudokuSolver::cellUpdated, this, &GameScreen::onSolverCellUpdated);
    connect(solver, &SudokuSolver::solvingFinished, this, &GameScreen::onSolverFinished);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScreen::updateTimerDisplay);
    elapsedSeconds = 0;
}

QPushButton* GameScreen::createButton(const QString &text, const QString &bgColor, const QString &hoverColor)
{
    QPushButton *btn = new QPushButton(text, this);
    btn->setFixedSize(GameSizes::controlButtonWidth(), GameSizes::controlButtonHeight());
    btn->setFont(QFont("Arial", GameSizes::buttonFontSize(), QFont::Bold));
    btn->setStyleSheet(QString(
                           "QPushButton { background-color: %1; color: white; border: none; border-radius: 6px; }"
                           "QPushButton:hover { background-color: %2; }"
                           "QPushButton:disabled { background-color: #95a5a6; }"
                           ).arg(bgColor, hoverColor));
    return btn;
}

QPushButton* GameScreen::createNumberButton(int number)
{
    QPushButton *btn = new QPushButton(QString::number(number), this);
    int buttonSize = GameSizes::buttonSize();
    btn->setFixedSize(buttonSize, buttonSize);
    btn->setFont(QFont("Arial", GameSizes::numberFontSize(), QFont::Bold));
    btn->setStyleSheet(
        "QPushButton { background-color: #ecf0f1; color: #2c3e50; border: 1px solid #bdc3c7; border-radius: 10px; }"
        "QPushButton:hover { background-color: #bdc3c7; }"
        "QPushButton:pressed { background-color: #95a5a6; }"
        "QPushButton:disabled { background-color: #bdc3c7; color: #7f8c8d; }"
        );
    connect(btn, &QPushButton::clicked, this, [this, number]() { onNumberButtonClicked(number); });
    return btn;
}

void GameScreen::setupUI()
{
    // Get screen geometry for responsive layout
    QRect screenGeo = GameSizes::screenGeometry();
    int screenWidth = screenGeo.width();
    int screenHeight = screenGeo.height();

    // Calculate margins based on screen size
    int margin = GameSizes::standardMargin();
    int leftMargin = screenWidth > 1000 ? 80 : margin * 2;

    // Main horizontal layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(leftMargin, margin, margin, margin);
    mainLayout->setSpacing(GameSizes::standardSpacing() * 2);

    // Left: Sudoku board with dynamic sizing
    board = new SudokuBoard(this);
    int boardDim = GameSizes::boardSize();
    board->setFixedSize(boardDim, boardDim);
    board->setMinimumSize(300, 300); // Ensure minimum size
    connect(board, &SudokuBoard::cellFocused, this, &GameScreen::onCellFocused);
    mainLayout->addWidget(board);

    // Right panel: vertical layout with proper spacing
    QVBoxLayout *rightPanel = new QVBoxLayout();
    rightPanel->setSpacing(GameSizes::standardSpacing());
    rightPanel->setAlignment(Qt::AlignTop);

    // Timer section
    timeCaptionLabel = new QLabel("Time", this);
    timeCaptionLabel->setFont(QFont("Arial", GameSizes::buttonFontSize()));
    timeCaptionLabel->setAlignment(Qt::AlignCenter);
    timeCaptionLabel->setStyleSheet("color: #7f8c8d;");

    timerLabel = new QLabel("00:00", this);
    QFont timerFont("Arial", GameSizes::titleFontSize(), QFont::Bold);
    timerLabel->setFont(timerFont);
    timerLabel->setStyleSheet(
        "QLabel { color: #2c3e50; background-color: white; border-radius: 6px; padding: 5px; }"
        );
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setFixedWidth(GameSizes::timerWidth());
    timerLabel->setMinimumWidth(80);

    rightPanel->addWidget(timeCaptionLabel, 0, Qt::AlignHCenter);
    rightPanel->addWidget(timerLabel, 0, Qt::AlignHCenter);
    rightPanel->addSpacing(GameSizes::standardSpacing());

    // Keypad 3x3 grid with dynamic sizing
    keypadLayout = new QGridLayout();
    keypadLayout->setSpacing(GameSizes::standardSpacing());

    int pos = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            int num = pos + 1;
            QPushButton *btn = createNumberButton(num);
            numberButtons.append(btn);
            keypadLayout->addWidget(btn, r, c, Qt::AlignCenter);
            pos++;
        }
    }
    rightPanel->addLayout(keypadLayout);

    // New Game button
    newGameButton = createButton("NEW GAME", "#2ecc71", "#27ae60");
    newGameButton->setFont(QFont("Arial", GameSizes::buttonFontSize() + 2, QFont::Bold));
    connect(newGameButton, &QPushButton::clicked, this, &GameScreen::onNewGameClicked);
    rightPanel->addWidget(newGameButton, 0, Qt::AlignHCenter);

    rightPanel->addSpacing(GameSizes::standardSpacing() / 2);

    // Other buttons
    undoButton = createButton("UNDO", "#3498db", "#2980b9");
    clearAllButton = createButton("CLEAR ALL", "#e67e22", "#d35400");
    solveButton = createButton("SOLVE", "#9b59b6", "#8e44ad");

    connect(undoButton, &QPushButton::clicked, this, &GameScreen::onUndoClicked);
    connect(clearAllButton, &QPushButton::clicked, this, &GameScreen::onClearAllClicked);
    connect(solveButton, &QPushButton::clicked, this, &GameScreen::onSolveClicked);

    rightPanel->addWidget(undoButton);
    rightPanel->addWidget(clearAllButton);
    rightPanel->addWidget(solveButton);
    rightPanel->addStretch();

    mainLayout->addLayout(rightPanel);

    // Back button with dynamic positioning
    backButton = new QPushButton("←", this);
    backButton->setFont(QFont("Arial", GameSizes::titleFontSize() + 4));
    backButton->setFixedSize(40, 40);
    backButton->setStyleSheet(
        "QPushButton { background-color: transparent; color: #2c3e50; border: none; }"
        "QPushButton:hover { color: #3498db; }"
        );
    backButton->move(margin, margin);
    backButton->raise();
    connect(backButton, &QPushButton::clicked, this, &GameScreen::onBackClicked);

    // Win overlay with dynamic sizing
    overlay = new QWidget(this);
    overlay->setGeometry(rect());
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 180);");
    overlay->hide();

    QVBoxLayout *overlayLayout = new QVBoxLayout(overlay);
    overlayLayout->setAlignment(Qt::AlignCenter);

    // Center box with dynamic size
    QWidget *centerBox = new QWidget(overlay);
    int boxWidth = qMin(450, static_cast<int>(screenWidth * 0.4));
    int boxHeight = qMin(400, static_cast<int>(screenHeight * 0.4));
    centerBox->setFixedSize(boxWidth, boxHeight);
    centerBox->setStyleSheet("background-color: white; border-radius: 20px; padding: 30px;");

    QVBoxLayout *centerLayout = new QVBoxLayout(centerBox);
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->setSpacing(GameSizes::standardSpacing());

    // Win message
    winMessageLabel = new QLabel("🎉 You Win! 🎉", centerBox);
    int winFontSize = qBound(20, boxWidth / 12, 32);
    winMessageLabel->setFont(QFont("Arial", winFontSize, QFont::Bold));
    winMessageLabel->setAlignment(Qt::AlignCenter);
    winMessageLabel->setStyleSheet("color: #27ae60;");
    winMessageLabel->setWordWrap(true);
    centerLayout->addWidget(winMessageLabel);

    // Win time
    winTimeLabel = new QLabel(centerBox);
    int timeFontSize = qBound(16, boxWidth / 15, 24);
    winTimeLabel->setFont(QFont("Arial", timeFontSize));
    winTimeLabel->setAlignment(Qt::AlignCenter);
    winTimeLabel->setStyleSheet("color: #2c3e50; margin: 10px;");
    winTimeLabel->setWordWrap(true);
    centerLayout->addWidget(winTimeLabel);

    // New Game button in overlay
    newGameOverlayButton = new QPushButton("New Game", centerBox);
    int buttonFontSize = qBound(14, boxWidth / 20, 18);
    newGameOverlayButton->setFont(QFont("Arial", buttonFontSize));
    newGameOverlayButton->setStyleSheet(
        "QPushButton { background-color: #3498db; color: white; border-radius: 10px; padding: 10px 20px; }"
        "QPushButton:hover { background-color: #2980b9; }"
        );
    newGameOverlayButton->setMinimumWidth(boxWidth / 2);
    connect(newGameOverlayButton, &QPushButton::clicked, this, &GameScreen::onNewGameFromOverlay);
    centerLayout->addWidget(newGameOverlayButton);

    overlayLayout->addWidget(centerBox);
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Update overlay geometry when window is resized
    if (overlay) {
        overlay->setGeometry(rect());
    }

    // Update back button position
    if (backButton) {
        int margin = GameSizes::standardMargin();
        backButton->move(margin, margin);
    }
}

void GameScreen::onCellFocused(int row, int col)
{
    selectedRow = row;
    selectedCol = col;
}

void GameScreen::onNumberButtonClicked(int number)
{
    if (selectedRow == -1 || selectedCol == -1) return;
    if (board->isCellReadOnly(selectedRow, selectedCol)) return;
    board->setValue(selectedRow, selectedCol, number, true);  // record undo
}

void GameScreen::onBackClicked()
{
    stopTimer();
    emit backToHomeClicked();
}

void GameScreen::startNewGame(const QString &difficulty)
{
    currentDifficulty = difficulty;
    generatePuzzle(difficulty);

    elapsedSeconds = 0;
    timerLabel->setText("00:00");
    elapsedTimer.start();
    timer->start(1000);

    hideWinOverlay();
    setButtonsEnabled(true);
    setKeypadEnabled(true);
    board->setAllCellsEnabled(true);
    selectedRow = selectedCol = -1;
}

void GameScreen::stopTimer()
{
    if (timer && timer->isActive()) {
        timer->stop();
    }
}

void GameScreen::generatePuzzle(const QString &difficulty)
{
    int index;
    if (difficulty == "easy") {
        index = QRandomGenerator::global()->bounded(easyPuzzles.size());
        initialBoard = easyPuzzles[index];
    } else if (difficulty == "medium") {
        index = QRandomGenerator::global()->bounded(mediumPuzzles.size());
        initialBoard = mediumPuzzles[index];
    } else {
        index = QRandomGenerator::global()->bounded(hardPuzzles.size());
        initialBoard = hardPuzzles[index];
    }
    board->setBoard(initialBoard, initialBoard);
}

void GameScreen::updateTimerDisplay()
{
    if (!elapsedTimer.isValid()) return;

    elapsedSeconds = elapsedTimer.elapsed() / 1000;
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    timerLabel->setText(QString("%1:%2")
                            .arg(minutes, 2, 10, QChar('0'))
                            .arg(seconds, 2, 10, QChar('0')));
}

void GameScreen::onUndoClicked()
{
    board->undo();
}

void GameScreen::onClearAllClicked()
{
    board->clearUserEntries();
}

void GameScreen::onNewGameClicked()
{
    generatePuzzle(currentDifficulty);
    elapsedSeconds = 0;
    timerLabel->setText("00:00");
    elapsedTimer.restart();
}

void GameScreen::onSolveClicked()
{
    board->setAllCellsEnabled(false);
    setButtonsEnabled(false);
    setKeypadEnabled(false);

    QVector<QVector<int>> currentBoard(9, QVector<int>(9, 0));
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            currentBoard[r][c] = board->getValue(r, c);

    solver->setBoard(currentBoard);
    solver->startSolving(50);
}

void GameScreen::onSolverCellUpdated(int row, int col, int value)
{
    board->setValue(row, col, value, false);  // no undo for solver
    QApplication::processEvents();
}

void GameScreen::onSolverFinished(bool solved, int timeMs)
{
    if (solved) {
        timer->stop();
        showWinOverlay(timeMs);
    } else {
        board->setAllCellsEnabled(true);
        setButtonsEnabled(true);
        setKeypadEnabled(true);
    }
}

void GameScreen::onNewGameFromOverlay()
{
    hideWinOverlay();
    startNewGame(currentDifficulty);
}

void GameScreen::showWinOverlay(int timeMs)
{
    int seconds = timeMs / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    QString timeText;
    if (minutes > 0) {
        timeText = QString("Completed in %1:%2")
                       .arg(minutes)
                       .arg(seconds, 2, 10, QChar('0'));
    } else {
        timeText = QString("Completed in %1 seconds").arg(seconds);
    }

    winTimeLabel->setText(timeText);
    overlay->setGeometry(rect());
    overlay->show();
    overlay->raise();

    // Ensure overlay is properly sized
    overlay->updateGeometry();
}

void GameScreen::hideWinOverlay()
{
    overlay->hide();
}

void GameScreen::setButtonsEnabled(bool enabled)
{
    if (undoButton) undoButton->setEnabled(enabled);
    if (clearAllButton) clearAllButton->setEnabled(enabled);
    if (solveButton) solveButton->setEnabled(enabled);
    if (backButton) backButton->setEnabled(enabled);
    if (newGameButton) newGameButton->setEnabled(enabled);
}

void GameScreen::setKeypadEnabled(bool enabled)
{
    for (QPushButton *btn : qAsConst(numberButtons)) {
        if (btn) btn->setEnabled(enabled);
    }
}
