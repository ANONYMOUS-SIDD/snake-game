/****************************************************************************
** Meta object code from reading C++ file 'gamescreen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "gamescreen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamescreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameScreen_t {
    QByteArrayData data[20];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameScreen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameScreen_t qt_meta_stringdata_GameScreen = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameScreen"
QT_MOC_LITERAL(1, 11, 17), // "backToHomeClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "updateTimerDisplay"
QT_MOC_LITERAL(4, 49, 13), // "onUndoClicked"
QT_MOC_LITERAL(5, 63, 17), // "onClearAllClicked"
QT_MOC_LITERAL(6, 81, 16), // "onNewGameClicked"
QT_MOC_LITERAL(7, 98, 14), // "onSolveClicked"
QT_MOC_LITERAL(8, 113, 19), // "onSolverCellUpdated"
QT_MOC_LITERAL(9, 133, 3), // "row"
QT_MOC_LITERAL(10, 137, 3), // "col"
QT_MOC_LITERAL(11, 141, 5), // "value"
QT_MOC_LITERAL(12, 147, 16), // "onSolverFinished"
QT_MOC_LITERAL(13, 164, 6), // "solved"
QT_MOC_LITERAL(14, 171, 6), // "timeMs"
QT_MOC_LITERAL(15, 178, 20), // "onNewGameFromOverlay"
QT_MOC_LITERAL(16, 199, 13), // "onBackClicked"
QT_MOC_LITERAL(17, 213, 21), // "onNumberButtonClicked"
QT_MOC_LITERAL(18, 235, 6), // "number"
QT_MOC_LITERAL(19, 242, 13) // "onCellFocused"

    },
    "GameScreen\0backToHomeClicked\0\0"
    "updateTimerDisplay\0onUndoClicked\0"
    "onClearAllClicked\0onNewGameClicked\0"
    "onSolveClicked\0onSolverCellUpdated\0"
    "row\0col\0value\0onSolverFinished\0solved\0"
    "timeMs\0onNewGameFromOverlay\0onBackClicked\0"
    "onNumberButtonClicked\0number\0onCellFocused"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameScreen[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    3,   80,    2, 0x08 /* Private */,
      12,    2,   87,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,
      17,    1,   94,    2, 0x08 /* Private */,
      19,    2,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,

       0        // eod
};

void GameScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameScreen *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backToHomeClicked(); break;
        case 1: _t->updateTimerDisplay(); break;
        case 2: _t->onUndoClicked(); break;
        case 3: _t->onClearAllClicked(); break;
        case 4: _t->onNewGameClicked(); break;
        case 5: _t->onSolveClicked(); break;
        case 6: _t->onSolverCellUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->onSolverFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->onNewGameFromOverlay(); break;
        case 9: _t->onBackClicked(); break;
        case 10: _t->onNumberButtonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onCellFocused((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameScreen::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameScreen::backToHomeClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameScreen::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GameScreen.data,
    qt_meta_data_GameScreen,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameScreen.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void GameScreen::backToHomeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
