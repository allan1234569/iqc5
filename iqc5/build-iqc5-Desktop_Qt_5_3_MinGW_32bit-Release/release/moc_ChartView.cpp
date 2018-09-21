/****************************************************************************
** Meta object code from reading C++ file 'ChartView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/ChartView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChartView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChartView_t {
    QByteArrayData data[16];
    char stringdata[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChartView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChartView_t qt_meta_stringdata_ChartView = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 27),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 4),
QT_MOC_LITERAL(4, 44, 26),
QT_MOC_LITERAL(5, 71, 25),
QT_MOC_LITERAL(6, 97, 4),
QT_MOC_LITERAL(7, 102, 23),
QT_MOC_LITERAL(8, 126, 21),
QT_MOC_LITERAL(9, 148, 7),
QT_MOC_LITERAL(10, 156, 22),
QT_MOC_LITERAL(11, 179, 18),
QT_MOC_LITERAL(12, 198, 21),
QT_MOC_LITERAL(13, 220, 33),
QT_MOC_LITERAL(14, 254, 1),
QT_MOC_LITERAL(15, 256, 22)
    },
    "ChartView\0on_inputCustAvg_textChanged\0"
    "\0arg1\0on_inputCustSD_textChanged\0"
    "on_inputStartDate_Changed\0date\0"
    "on_inputEndDate_Changed\0on_IfCaculate_toggled\0"
    "checked\0on_btnCaculate_clicked\0"
    "on_btnInit_clicked\0on_cbkShowAll_toggled\0"
    "on_listWidget_currentIndexChanged\0i\0"
    "on_btnAreaData_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChartView[] = {

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
       1,    1,   64,    2, 0x08 /* Private */,
       4,    1,   67,    2, 0x08 /* Private */,
       5,    1,   70,    2, 0x08 /* Private */,
       7,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,
      13,    1,   84,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QDate,    6,
    QMetaType::Void, QMetaType::QDate,    6,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,

       0        // eod
};

void ChartView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChartView *_t = static_cast<ChartView *>(_o);
        switch (_id) {
        case 0: _t->on_inputCustAvg_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_inputCustSD_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_inputStartDate_Changed((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->on_inputEndDate_Changed((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 4: _t->on_IfCaculate_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_btnCaculate_clicked(); break;
        case 6: _t->on_btnInit_clicked(); break;
        case 7: _t->on_cbkShowAll_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_listWidget_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_btnAreaData_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ChartView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChartView.data,
      qt_meta_data_ChartView,  qt_static_metacall, 0, 0}
};


const QMetaObject *ChartView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChartView.stringdata))
        return static_cast<void*>(const_cast< ChartView*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChartView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
