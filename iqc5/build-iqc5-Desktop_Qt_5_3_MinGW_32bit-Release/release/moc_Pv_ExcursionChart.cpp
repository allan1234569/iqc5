/****************************************************************************
** Meta object code from reading C++ file 'Pv_ExcursionChart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/PV/Pv_ExcursionChart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pv_ExcursionChart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Pv_ExcursionChart_t {
    QByteArrayData data[9];
    char stringdata[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Pv_ExcursionChart_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Pv_ExcursionChart_t qt_meta_stringdata_Pv_ExcursionChart = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 11),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 13),
QT_MOC_LITERAL(4, 45, 5),
QT_MOC_LITERAL(5, 51, 10),
QT_MOC_LITERAL(6, 62, 6),
QT_MOC_LITERAL(7, 69, 10),
QT_MOC_LITERAL(8, 80, 5)
    },
    "Pv_ExcursionChart\0updateChart\0\0"
    "QwtPlotCurve*\0curve\0QPolygonF&\0points\0"
    "onSelected\0point"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Pv_ExcursionChart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       7,    1,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::QPointF,    8,

       0        // eod
};

void Pv_ExcursionChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Pv_ExcursionChart *_t = static_cast<Pv_ExcursionChart *>(_o);
        switch (_id) {
        case 0: _t->updateChart((*reinterpret_cast< QwtPlotCurve*(*)>(_a[1])),(*reinterpret_cast< QPolygonF(*)>(_a[2]))); break;
        case 1: _t->onSelected((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Pv_ExcursionChart::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Pv_ExcursionChart.data,
      qt_meta_data_Pv_ExcursionChart,  qt_static_metacall, 0, 0}
};


const QMetaObject *Pv_ExcursionChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Pv_ExcursionChart::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Pv_ExcursionChart.stringdata))
        return static_cast<void*>(const_cast< Pv_ExcursionChart*>(this));
    return QDialog::qt_metacast(_clname);
}

int Pv_ExcursionChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
