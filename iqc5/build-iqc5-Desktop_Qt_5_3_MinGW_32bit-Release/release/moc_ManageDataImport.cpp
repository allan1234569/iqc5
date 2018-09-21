/****************************************************************************
** Meta object code from reading C++ file 'ManageDataImport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/ManageDataImport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManageDataImport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ManageDataImport_t {
    QByteArrayData data[15];
    char stringdata[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManageDataImport_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManageDataImport_t qt_meta_stringdata_ManageDataImport = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 28),
QT_MOC_LITERAL(2, 46, 0),
QT_MOC_LITERAL(3, 47, 26),
QT_MOC_LITERAL(4, 74, 28),
QT_MOC_LITERAL(5, 103, 25),
QT_MOC_LITERAL(6, 129, 28),
QT_MOC_LITERAL(7, 158, 11),
QT_MOC_LITERAL(8, 170, 3),
QT_MOC_LITERAL(9, 174, 16),
QT_MOC_LITERAL(10, 191, 22),
QT_MOC_LITERAL(11, 214, 16),
QT_MOC_LITERAL(12, 231, 4),
QT_MOC_LITERAL(13, 236, 35),
QT_MOC_LITERAL(14, 272, 24)
    },
    "ManageDataImport\0on_Cancel_PushButton_clicked\0"
    "\0on_Save_PushButton_clicked\0"
    "on_Ensure_PushButton_clicked\0"
    "on_Add_ToolButton_clicked\0"
    "on_Delete_ToolButton_clicked\0slt_Editing\0"
    "txt\0slt_EditFinished\0slt_listWidget_Clicked\0"
    "QListWidgetItem*\0item\0"
    "on_tableWidget_itemSelectionChanged\0"
    "on_BtnSelectPath_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManageDataImport[] = {

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
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      13,    0,   76,    2, 0x08 /* Private */,
      14,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ManageDataImport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ManageDataImport *_t = static_cast<ManageDataImport *>(_o);
        switch (_id) {
        case 0: _t->on_Cancel_PushButton_clicked(); break;
        case 1: _t->on_Save_PushButton_clicked(); break;
        case 2: _t->on_Ensure_PushButton_clicked(); break;
        case 3: _t->on_Add_ToolButton_clicked(); break;
        case 4: _t->on_Delete_ToolButton_clicked(); break;
        case 5: _t->slt_Editing((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->slt_EditFinished(); break;
        case 7: _t->slt_listWidget_Clicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->on_tableWidget_itemSelectionChanged(); break;
        case 9: _t->on_BtnSelectPath_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ManageDataImport::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ManageDataImport.data,
      qt_meta_data_ManageDataImport,  qt_static_metacall, 0, 0}
};


const QMetaObject *ManageDataImport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManageDataImport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManageDataImport.stringdata))
        return static_cast<void*>(const_cast< ManageDataImport*>(this));
    return QDialog::qt_metacast(_clname);
}

int ManageDataImport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
