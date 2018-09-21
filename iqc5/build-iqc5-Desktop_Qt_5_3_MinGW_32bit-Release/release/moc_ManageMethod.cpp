/****************************************************************************
** Meta object code from reading C++ file 'ManageMethod.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/ManageMethod.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManageMethod.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ManageMethod_t {
    QByteArrayData data[18];
    char stringdata[286];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManageMethod_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManageMethod_t qt_meta_stringdata_ManageMethod = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 20),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 17),
QT_MOC_LITERAL(4, 53, 21),
QT_MOC_LITERAL(5, 75, 23),
QT_MOC_LITERAL(6, 99, 20),
QT_MOC_LITERAL(7, 120, 35),
QT_MOC_LITERAL(8, 156, 5),
QT_MOC_LITERAL(9, 162, 27),
QT_MOC_LITERAL(10, 190, 4),
QT_MOC_LITERAL(11, 195, 31),
QT_MOC_LITERAL(12, 227, 16),
QT_MOC_LITERAL(13, 244, 4),
QT_MOC_LITERAL(14, 249, 6),
QT_MOC_LITERAL(15, 256, 10),
QT_MOC_LITERAL(16, 267, 12),
QT_MOC_LITERAL(17, 280, 5)
    },
    "ManageMethod\0on_btnCancel_clicked\0\0"
    "on_btnAdd_clicked\0OnBtnTableEditClicked\0"
    "OnBtnTableDeleteClicked\0on_btnSearch_clicked\0"
    "on_inputSubject_currentIndexChanged\0"
    "index\0on_inputKeyword_textChanged\0"
    "arg1\0on_treeWidget_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0closeEvent\0"
    "QCloseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManageMethod[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    1,   64,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x08 /* Private */,
      11,    2,   70,    2, 0x08 /* Private */,
      15,    1,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void ManageMethod::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ManageMethod *_t = static_cast<ManageMethod *>(_o);
        switch (_id) {
        case 0: _t->on_btnCancel_clicked(); break;
        case 1: _t->on_btnAdd_clicked(); break;
        case 2: _t->OnBtnTableEditClicked(); break;
        case 3: _t->OnBtnTableDeleteClicked(); break;
        case 4: _t->on_btnSearch_clicked(); break;
        case 5: _t->on_inputSubject_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ManageMethod::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ManageMethod.data,
      qt_meta_data_ManageMethod,  qt_static_metacall, 0, 0}
};


const QMetaObject *ManageMethod::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManageMethod::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManageMethod.stringdata))
        return static_cast<void*>(const_cast< ManageMethod*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ManageMethod::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
