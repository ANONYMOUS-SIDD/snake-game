#include "sudokuboard.h"
#include "gamesizes.h"
#include <QKeyEvent>
#include <QRegularExpressionValidator>
#include <QFont>
#include <QFrame>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>

SudokuBoard::SudokuBoard(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainGrid = new QGridLayout(this);
    mainGrid->setSpacing(0);
    mainGrid->setContentsMargins(0, 0, 0, 0);

    // FIXED: Vector initialization - resize first, then fill
    cells.resize(9);
    readOnlyCells.resize(9);
    for (int i = 0; i < 9; ++i) {
        cells[i].resize(9);  // Just resize, no second parameter
        readOnlyCells[i].resize(9);

        // Then fill with default values
        for (int j = 0; j < 9; ++j) {
            cells[i][j] = nullptr;
            readOnlyCells[i][j] = false;
        }
    }

    QFrame *outerFrame = new QFrame(this);
    outerFrame->setFrameStyle(QFrame::Box);
    outerFrame->setLineWidth(3);
    outerFrame->setStyleSheet("QFrame { border: 3px solid #2c3e50; }");
    QGridLayout *outerLayout = new QGridLayout(outerFrame);
    outerLayout->setSpacing(0);
    outerLayout->setContentsMargins(0, 0, 0, 0);

    // Calculate cell size based on board size
    int cellSize = GameSizes::cellSize();
    int fontSize = qBound(16, cellSize / 3, 24); // Scale font with cell size

    for (int blockRow = 0; blockRow < 3; ++blockRow) {
        for (int blockCol = 0; blockCol < 3; ++blockCol) {
            QFrame *block = new QFrame(outerFrame);
            block->setFrameStyle(QFrame::Box);
            block->setLineWidth(2);
            block->setStyleSheet("QFrame { border: 2px solid #4a4a4a; }");

            QGridLayout *blockLayout = new QGridLayout(block);
            blockLayout->setSpacing(0);
            blockLayout->setContentsMargins(0, 0, 0, 0);

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int row = blockRow * 3 + i;
                    int col = blockCol * 3 + j;

                    QLineEdit *cell = new QLineEdit(block);
                    cell->setAlignment(Qt::AlignCenter);
                    cell->setMaxLength(1);
                    cell->setFixedSize(cellSize, cellSize);

                    // Scale font based on cell size
                    QFont font("Arial", fontSize, QFont::Bold);
                    cell->setFont(font);

                    cell->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]"), cell));
                    cell->installEventFilter(this);

                    // Style with dynamic sizing
                    int borderRadius = qMax(2, cellSize / 20);
                    cell->setStyleSheet(
                        QString("QLineEdit { "
                                "border: 1px solid #d0d0d0; "
                                "background-color: white; "
                                "padding: 0px; "
                                "border-radius: %1px; "
                                "}"
                                "QLineEdit:focus { "
                                "border: 2px solid #3498db; "
                                "}").arg(borderRadius)
                        );

                    blockLayout->addWidget(cell, i, j);
                    cells[row][col] = cell;

                    connect(cell, &QLineEdit::textEdited, this, [this, row, col](const QString &newText) {
                        onCellTextEdited(newText, row, col);
                    });
                }
            }
            outerLayout->addWidget(block, blockRow, blockCol);
        }
    }

    mainGrid->addWidget(outerFrame, 0, 0);
    setStyleSheet("background-color: #f0f0f0;");

    // Set minimum size
    setMinimumSize(cellSize * 9 + 20, cellSize * 9 + 20);
}

SudokuBoard::~SudokuBoard()
{
    // Clean up if needed
}

void SudokuBoard::setBoard(const QVector<QVector<int>> &initial, const QVector<QVector<int>> &)
{
    int cellSize = GameSizes::cellSize();
    int fontSize = qBound(16, cellSize / 3, 24);
    int borderRadius = qMax(2, cellSize / 20);

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int val = initial[row][col];
            QLineEdit *cell = cells[row][col];
            if (!cell) continue;

            if (val != 0) {
                cell->setText(QString::number(val));
                cell->setReadOnly(true);
                readOnlyCells[row][col] = true;

                // Pre-filled cells style
                cell->setStyleSheet(
                    QString("QLineEdit { "
                            "border: 1px solid #d0d0d0; "
                            "background-color: #f5f5f5; "
                            "color: #1a1a1a; "
                            "font-weight: bold; "
                            "border-radius: %1px; "
                            "}"
                            "QLineEdit:focus { "
                            "border: 2px solid #3498db; "
                            "}").arg(borderRadius)
                    );
            } else {
                cell->clear();
                cell->setReadOnly(false);
                readOnlyCells[row][col] = false;

                // Editable cells style
                cell->setStyleSheet(
                    QString("QLineEdit { "
                            "border: 1px solid #d0d0d0; "
                            "background-color: white; "
                            "color: #333333; "
                            "border-radius: %1px; "
                            "}"
                            "QLineEdit:focus { "
                            "border: 2px solid #3498db; "
                            "}").arg(borderRadius)
                    );
            }
        }
    }
    undoStack.clear();
    oldValueMap.clear();
    checkAllConflicts();
}

void SudokuBoard::clearUserEntries()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!readOnlyCells[row][col] && cells[row][col]) {
                cells[row][col]->clear();
            }
        }
    }
    checkAllConflicts();
}

void SudokuBoard::undo()
{
    if (!undoStack.isEmpty()) {
        UndoEntry entry = undoStack.last();
        if (cells[entry.row][entry.col]) {
            cells[entry.row][entry.col]->setText(entry.oldValue);
        }
        undoStack.pop_back();
        checkAllConflicts();
    }
}

void SudokuBoard::setCellReadOnly(int row, int col, bool readOnly)
{
    if (row >= 0 && row < 9 && col >= 0 && col < 9 && cells[row][col]) {
        cells[row][col]->setReadOnly(readOnly);
        readOnlyCells[row][col] = readOnly;
    }
}

bool SudokuBoard::isCellReadOnly(int row, int col) const
{
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        return readOnlyCells[row][col];
    }
    return false;
}

int SudokuBoard::getValue(int row, int col) const
{
    if (row >= 0 && row < 9 && col >= 0 && col < 9 && cells[row][col]) {
        QString text = cells[row][col]->text();
        return text.isEmpty() ? 0 : text.toInt();
    }
    return 0;
}

void SudokuBoard::setValue(int row, int col, int value, bool recordUndo)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9 || !cells[row][col]) return;

    QLineEdit *cell = cells[row][col];
    if (recordUndo && !readOnlyCells[row][col]) {
        // Store old value for undo
        QString oldText = cell->text();
        if (oldText != (value >= 1 && value <= 9 ? QString::number(value) : "")) {
            UndoEntry entry;
            entry.row = row;
            entry.col = col;
            entry.oldValue = oldText;
            undoStack.push_back(entry);
        }
    }
    if (value >= 1 && value <= 9) {
        cell->setText(QString::number(value));
    } else {
        cell->clear();
    }
    checkAllConflicts();
}

void SudokuBoard::setAllReadOnly(const QVector<QVector<bool>> &readOnlyMap)
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            setCellReadOnly(row, col, readOnlyMap[row][col]);
        }
    }
}

void SudokuBoard::setAllCellsEnabled(bool enabled)
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (cells[row][col]) {
                cells[row][col]->setEnabled(enabled);
            }
        }
    }
}

void SudokuBoard::checkAllConflicts()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            updateConflictsForCell(row, col);
        }
    }
}

void SudokuBoard::onCellTextEdited(const QString &newText, int row, int col)
{
    QLineEdit *cell = cells[row][col];
    if (!cell) return;

    QString oldText = oldValueMap.value(cell, QString());
    if (oldText != newText) {
        UndoEntry entry;
        entry.row = row;
        entry.col = col;
        entry.oldValue = oldText;
        undoStack.push_back(entry);
    }
    checkAllConflicts();

    // Check if board is complete and valid
    checkBoardComplete();
}

void SudokuBoard::applyConflictStyle(int row, int col, bool hasConflict)
{
    QLineEdit *cell = cells[row][col];
    if (!cell) return;

    int cellSize = GameSizes::cellSize();
    int borderRadius = qMax(2, cellSize / 20);

    QString baseStyle;
    if (readOnlyCells[row][col]) {
        baseStyle = QString("QLineEdit { "
                            "border: 1px solid #d0d0d0; "
                            "background-color: #f5f5f5; "
                            "color: #1a1a1a; "
                            "font-weight: bold; "
                            "border-radius: %1px; "
                            "}").arg(borderRadius);
    } else {
        baseStyle = QString("QLineEdit { "
                            "border: 1px solid #d0d0d0; "
                            "background-color: white; "
                            "color: #333333; "
                            "border-radius: %1px; "
                            "}").arg(borderRadius);
    }

    if (hasConflict) {
        // Add red border for conflicts
        cell->setStyleSheet(baseStyle +
                            "QLineEdit { border-bottom: 3px solid #e74c3c; }"
                            "QLineEdit:focus { border: 2px solid #3498db; border-bottom: 3px solid #e74c3c; }");
    } else {
        cell->setStyleSheet(baseStyle +
                            "QLineEdit:focus { border: 2px solid #3498db; }");
    }
}

bool SudokuBoard::hasConflict(int row, int col) const
{
    int value = getValue(row, col);
    if (value == 0) return false;

    // Check row
    for (int c = 0; c < 9; ++c) {
        if (c != col && getValue(row, c) == value) return true;
    }

    // Check column
    for (int r = 0; r < 9; ++r) {
        if (r != row && getValue(r, col) == value) return true;
    }

    // Check 3x3 block
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if ((r != row || c != col) && getValue(r, c) == value) return true;
        }
    }
    return false;
}

void SudokuBoard::updateConflictsForCell(int row, int col)
{
    bool conflict = hasConflict(row, col);
    applyConflictStyle(row, col, conflict);
}

void SudokuBoard::checkBoardComplete()
{
    // Check if all cells are filled and no conflicts
    bool complete = true;
    for (int row = 0; row < 9 && complete; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (getValue(row, col) == 0 || hasConflict(row, col)) {
                complete = false;
                break;
            }
        }
    }

    if (complete) {
        emit boardCompleted();
    }
}

void SudokuBoard::storeOldValueForCell(QLineEdit *cell, int row, int col)
{
    Q_UNUSED(row);
    Q_UNUSED(col);
    if (cell) {
        oldValueMap[cell] = cell->text();
    }
}

bool SudokuBoard::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        QLineEdit *cell = qobject_cast<QLineEdit*>(obj);
        if (cell) {
            for (int r = 0; r < 9; ++r) {
                for (int c = 0; c < 9; ++c) {
                    if (cells[r][c] == cell) {
                        storeOldValueForCell(cell, r, c);
                        emit cellFocused(r, c);
                        break;
                    }
                }
            }
        }
    }
    else if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Backspace) {
            undo();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SudokuBoard::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Update cell sizes if needed when board is resized
    int newCellSize = GameSizes::cellSize();
    int fontSize = qBound(16, newCellSize / 3, 24);

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (cells[row][col]) {
                cells[row][col]->setFixedSize(newCellSize, newCellSize);
                QFont font = cells[row][col]->font();
                font.setPointSize(fontSize);
                cells[row][col]->setFont(font);
            }
        }
    }
}
