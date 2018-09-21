/****************************************************************************
** Meta object code from reading C++ file 'ManageProject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/ManageProject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManageProject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ManageProject_t {
    QByteArrayData data[12];
    char stringdata[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManageProject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManageProject_t qt_meta_stringdata_ManageProject = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 27),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 4),
QT_MOC_LITERAL(4, 48, 25),
QT_MOC_LITERAL(5, 74, 16),
QT_MOC_LITERAL(6, 91, 4),
QT_MOC_LITERAL(7, 96, 21),
QT_MOC_LITERAL(8, 118, 25),
QT_MOC_LITERAL(9, 144, 23),
QT_MOC_LITERAL(10, 168, 17),
QT_MOC_LITERAL(11, 186, 21)
    },
    "ManageProject\0on_inputKeyword_textChanged\0"
    "\0arg1\0on_list_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0OnBtnTableEditClicked\0"
    "OnBtnTableEditDataClicked\0"
    "OnBtnTableDeleteClicked\0on_btnNew_clicked\0"
    "on_btnRefresh_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManageProject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    1,   52,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,
      10,    0,   58,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ManageProject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ManageProject *_t = static_cast<ManageProject *>(_o);
        switch (_id) {
        case 0: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_list_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->OnBtnTableEditClicked(); break;
        case 3: _t->OnBtnTableEditDataClicked(); break;
        case 4: _t->OnBtnTableDeleteClicked(); break;
        case 5: _t->on_btnNew_clicked(); break;
        case 6: _t->on_btnRefresh_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ManageProject::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ManageProject.data,
      qt_meta_data_ManageProject,  qt_static_metacall, 0, 0}
};


const QMetaObject *ManageProject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManageProject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManageProject.stringdata))
        return static_cast<void*>(const_cast< ManageProject*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ManageProject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
