/****************************************************************************
** Meta object code from reading C++ file 'SixSigma_QCRulesScreening.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/SixSigma_QCRulesScreening.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SixSigma_QCRulesScreening.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SixSigma_QCRulesScreening_t {
    QByteArrayData data[11];
    char stringdata[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SixSigma_QCRulesScreening_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SixSigma_QCRulesScreening_t qt_meta_stringdata_SixSigma_QCRulesScreening = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 28),
QT_MOC_LITERAL(2, 55, 0),
QT_MOC_LITERAL(3, 56, 4),
QT_MOC_LITERAL(4, 61, 34),
QT_MOC_LITERAL(5, 96, 31),
QT_MOC_LITERAL(6, 128, 19),
QT_MOC_LITERAL(7, 148, 25),
QT_MOC_LITERAL(8, 174, 16),
QT_MOC_LITERAL(9, 191, 4),
QT_MOC_LITERAL(10, 196, 6)
    },
    "SixSigma_QCRulesScreening\0"
    "on_input_keyword_textChanged\0\0arg1\0"
    "on_treeWidget_itemSelectionChanged\0"
    "on_stackedWidget_currentChanged\0"
    "slt_hasParamChanged\0on_treeWidget_itemClicked\0"
    "QTreeWidgetItem*\0item\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SixSigma_QCRulesScreening[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    0,   42,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    2,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,

       0        // eod
};

void SixSigma_QCRulesScreening::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SixSigma_QCRulesScreening *_t = static_cast<SixSigma_QCRulesScreening *>(_o);
        switch (_id) {
        case 0: _t->on_input_keyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_treeWidget_itemSelectionChanged(); break;
        case 2: _t->on_stackedWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slt_hasParamChanged(); break;
        case 4: _t->on_treeWidget_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SixSigma_QCRulesScreening::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SixSigma_QCRulesScreening.data,
      qt_meta_data_SixSigma_QCRulesScreening,  qt_static_metacall, 0, 0}
};


const QMetaObject *SixSigma_QCRulesScreening::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SixSigma_QCRulesScreening::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SixSigma_QCRulesScreening.stringdata))
        return static_cast<void*>(const_cast< SixSigma_QCRulesScreening*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SixSigma_QCRulesScreening::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
