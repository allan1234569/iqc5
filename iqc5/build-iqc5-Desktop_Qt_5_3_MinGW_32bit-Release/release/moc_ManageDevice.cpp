/****************************************************************************
** Meta object code from reading C++ file 'ManageDevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/ManageDevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManageDevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ManageDevice_t {
    QByteArrayData data[19];
    char stringdata[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManageDevice_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManageDevice_t qt_meta_stringdata_ManageDevice = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 17),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 21),
QT_MOC_LITERAL(4, 54, 23),
QT_MOC_LITERAL(5, 78, 32),
QT_MOC_LITERAL(6, 111, 16),
QT_MOC_LITERAL(7, 128, 7),
QT_MOC_LITERAL(8, 136, 8),
QT_MOC_LITERAL(9, 145, 27),
QT_MOC_LITERAL(10, 173, 4),
QT_MOC_LITERAL(11, 178, 31),
QT_MOC_LITERAL(12, 210, 4),
QT_MOC_LITERAL(13, 215, 6),
QT_MOC_LITERAL(14, 222, 9),
QT_MOC_LITERAL(15, 232, 11),
QT_MOC_LITERAL(16, 244, 10),
QT_MOC_LITERAL(17, 255, 12),
QT_MOC_LITERAL(18, 268, 5)
    },
    "ManageDevice\0on_btnAdd_clicked\0\0"
    "OnBtnTableEditClicked\0OnBtnTableDeleteClicked\0"
    "on_treeWidget_currentItemChanged\0"
    "QTreeWidgetItem*\0current\0previous\0"
    "on_inputKeyword_textChanged\0arg1\0"
    "on_treeWidget_itemDoubleClicked\0item\0"
    "column\0showEvent\0QShowEvent*\0closeEvent\0"
    "QCloseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManageDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    2,   57,    2, 0x08 /* Private */,
       9,    1,   62,    2, 0x08 /* Private */,
      11,    2,   65,    2, 0x08 /* Private */,
      14,    1,   70,    2, 0x08 /* Private */,
      16,    1,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,   12,   13,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void ManageDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ManageDevice *_t = static_cast<ManageDevice *>(_o);
        switch (_id) {
        case 0: _t->on_btnAdd_clicked(); break;
        case 1: _t->OnBtnTableEditClicked(); break;
        case 2: _t->OnBtnTableDeleteClicked(); break;
        case 3: _t->on_treeWidget_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 4: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ManageDevice::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ManageDevice.data,
      qt_meta_data_ManageDevice,  qt_static_metacall, 0, 0}
};


const QMetaObject *ManageDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManageDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManageDevice.stringdata))
        return static_cast<void*>(const_cast< ManageDevice*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ManageDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE