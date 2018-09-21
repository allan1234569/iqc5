/****************************************************************************
** Meta object code from reading C++ file 'InputDataMulti.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/InputDataMulti.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InputDataMulti.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InputDataMulti_t {
    QByteArrayData data[21];
    char stringdata[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InputDataMulti_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InputDataMulti_t qt_meta_stringdata_InputDataMulti = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 19),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 18),
QT_MOC_LITERAL(4, 55, 25),
QT_MOC_LITERAL(5, 81, 16),
QT_MOC_LITERAL(6, 98, 4),
QT_MOC_LITERAL(7, 103, 6),
QT_MOC_LITERAL(8, 110, 23),
QT_MOC_LITERAL(9, 134, 4),
QT_MOC_LITERAL(10, 139, 23),
QT_MOC_LITERAL(11, 163, 4),
QT_MOC_LITERAL(12, 168, 11),
QT_MOC_LITERAL(13, 180, 3),
QT_MOC_LITERAL(14, 184, 7),
QT_MOC_LITERAL(15, 192, 5),
QT_MOC_LITERAL(16, 198, 27),
QT_MOC_LITERAL(17, 226, 6),
QT_MOC_LITERAL(18, 233, 9),
QT_MOC_LITERAL(19, 243, 10),
QT_MOC_LITERAL(20, 254, 12)
    },
    "InputDataMulti\0on_btnClose_clicked\0\0"
    "on_btnSave_clicked\0on_treeWidget_itemChanged\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_dateEdit_dateChanged\0date\0"
    "on_spinBox_valueChanged\0arg1\0eventFilter\0"
    "obj\0QEvent*\0event\0on_inputKeyword_textChanged\0"
    "rowAdd\0rowDelete\0closeEvent\0QCloseEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InputDataMulti[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    2,   66,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
      10,    1,   74,    2, 0x08 /* Private */,
      12,    2,   77,    2, 0x08 /* Private */,
      16,    1,   82,    2, 0x08 /* Private */,
      17,    0,   85,    2, 0x08 /* Private */,
      18,    0,   86,    2, 0x08 /* Private */,
      19,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::QDate,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 14,   13,   15,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   15,

       0        // eod
};

void InputDataMulti::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InputDataMulti *_t = static_cast<InputDataMulti *>(_o);
        switch (_id) {
        case 0: _t->on_btnClose_clicked(); break;
        case 1: _t->on_btnSave_clicked(); break;
        case 2: _t->on_treeWidget_itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_dateEdit_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 4: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->rowAdd(); break;
        case 8: _t->rowDelete(); break;
        case 9: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject InputDataMulti::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_InputDataMulti.data,
      qt_meta_data_InputDataMulti,  qt_static_metacall, 0, 0}
};


const QMetaObject *InputDataMulti::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputDataMulti::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputDataMulti.stringdata))
        return static_cast<void*>(const_cast< InputDataMulti*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int InputDataMulti::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
