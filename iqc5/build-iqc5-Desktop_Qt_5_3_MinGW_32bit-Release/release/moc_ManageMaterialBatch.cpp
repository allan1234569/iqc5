/****************************************************************************
** Meta object code from reading C++ file 'ManageMaterialBatch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/ManageMaterialBatch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManageMaterialBatch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ManageMaterialBatch_t {
    QByteArrayData data[20];
    char stringdata[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManageMaterialBatch_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManageMaterialBatch_t qt_meta_stringdata_ManageMaterialBatch = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 32),
QT_MOC_LITERAL(2, 53, 0),
QT_MOC_LITERAL(3, 54, 16),
QT_MOC_LITERAL(4, 71, 7),
QT_MOC_LITERAL(5, 79, 8),
QT_MOC_LITERAL(6, 88, 21),
QT_MOC_LITERAL(7, 110, 23),
QT_MOC_LITERAL(8, 134, 21),
QT_MOC_LITERAL(9, 156, 27),
QT_MOC_LITERAL(10, 184, 4),
QT_MOC_LITERAL(11, 189, 31),
QT_MOC_LITERAL(12, 221, 4),
QT_MOC_LITERAL(13, 226, 6),
QT_MOC_LITERAL(14, 233, 17),
QT_MOC_LITERAL(15, 251, 20),
QT_MOC_LITERAL(16, 272, 18),
QT_MOC_LITERAL(17, 291, 10),
QT_MOC_LITERAL(18, 302, 12),
QT_MOC_LITERAL(19, 315, 5)
    },
    "ManageMaterialBatch\0"
    "on_treeWidget_currentItemChanged\0\0"
    "QTreeWidgetItem*\0current\0previous\0"
    "OnBtnTableEditClicked\0OnBtnTableDeleteClicked\0"
    "on_pushButton_clicked\0on_inputKeyword_textChanged\0"
    "arg1\0on_treeWidget_itemDoubleClicked\0"
    "item\0column\0on_btnAdd_clicked\0"
    "on_btnDelete_clicked\0on_btnSave_clicked\0"
    "closeEvent\0QCloseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManageMaterialBatch[] = {

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
       1,    2,   64,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      11,    2,   75,    2, 0x08 /* Private */,
      14,    0,   80,    2, 0x08 /* Private */,
      15,    0,   81,    2, 0x08 /* Private */,
      16,    0,   82,    2, 0x08 /* Private */,
      17,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void ManageMaterialBatch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ManageMaterialBatch *_t = static_cast<ManageMaterialBatch *>(_o);
        switch (_id) {
        case 0: _t->on_treeWidget_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 1: _t->OnBtnTableEditClicked(); break;
        case 2: _t->OnBtnTableDeleteClicked(); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->on_btnAdd_clicked(); break;
        case 7: _t->on_btnDelete_clicked(); break;
        case 8: _t->on_btnSave_clicked(); break;
        case 9: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ManageMaterialBatch::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ManageMaterialBatch.data,
      qt_meta_data_ManageMaterialBatch,  qt_static_metacall, 0, 0}
};


const QMetaObject *ManageMaterialBatch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManageMaterialBatch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManageMaterialBatch.stringdata))
        return static_cast<void*>(const_cast< ManageMaterialBatch*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ManageMaterialBatch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
