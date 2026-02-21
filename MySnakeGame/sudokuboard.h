#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QMap>

class SudokuBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuBoard(QWidget *parent = nullptr);
    ~SudokuBoard();

    void setBoard(const QVector<QVector<int>> &initial, const QVector<QVector<int>> &solution);
    void clearUserEntries();
    void undo();
    void setCellReadOnly(int row, int col, bool readOnly);
    bool isCellReadOnly(int row, int col) const;
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value, bool recordUndo = true);
    void setAllReadOnly(const QVector<QVector<bool>> &readOnlyMap);
    void setAllCellsEnabled(bool enabled);
    bool hasConflict(int row, int col) const;

signals:
    void cellFocused(int row, int col);
    void boardCompleted();  // New signal for when board is solved

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;  // Add this

private slots:
    void onCellTextEdited(const QString &newText, int row, int col);

private:
    struct UndoEntry {
        int row;
        int col;
        QString oldValue;
    };

    QVector<QVector<QLineEdit*>> cells;
    QVector<QVector<bool>> readOnlyCells;
    QVector<UndoEntry> undoStack;
    QMap<QLineEdit*, QString> oldValueMap;

    void checkAllConflicts();
    void updateConflictsForCell(int row, int col);
    void applyConflictStyle(int row, int col, bool hasConflict);
    void storeOldValueForCell(QLineEdit *cell, int row, int col);
    void checkBoardComplete();  // New method
};

#endif // SUDOKUBOARD_H
