/****************************************************************************
** Meta object code from reading C++ file 'basewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SerialPortDecode_Common/basewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BaseWindow_t {
    QByteArrayData data[14];
    char stringdata[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseWindow_t qt_meta_stringdata_BaseWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 8),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 16),
QT_MOC_LITERAL(4, 38, 33),
QT_MOC_LITERAL(5, 72, 6),
QT_MOC_LITERAL(6, 79, 11),
QT_MOC_LITERAL(7, 91, 28),
QT_MOC_LITERAL(8, 120, 28),
QT_MOC_LITERAL(9, 149, 24),
QT_MOC_LITERAL(10, 174, 31),
QT_MOC_LITERAL(11, 206, 32),
QT_MOC_LITERAL(12, 239, 29),
QT_MOC_LITERAL(13, 269, 24)
    },
    "BaseWindow\0slt_show\0\0slt_showTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0slt_timeout\0on_action_ReadFile_triggered\0"
    "on_action_ReHandle_triggered\0"
    "on_action_Exit_triggered\0"
    "on_action_DecodeSetup_triggered\0"
    "on_action_OriginalData_triggered\0"
    "on_action_DecodeLog_triggered\0"
    "on_action_Help_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseWindow[] = {

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
       1,    0,   64,    2, 0x0a /* Public */,
       3,    1,   65,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,
      12,    0,   74,    2, 0x0a /* Public */,
      13,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BaseWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BaseWindow *_t = static_cast<BaseWindow *>(_o);
        switch (_id) {
        case 0: _t->slt_show(); break;
        case 1: _t->slt_showTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 2: _t->slt_timeout(); break;
        case 3: _t->on_action_ReadFile_triggered(); break;
        case 4: _t->on_action_ReHandle_triggered(); break;
        case 5: _t->on_action_Exit_triggered(); break;
        case 6: _t->on_action_DecodeSetup_triggered(); break;
        case 7: _t->on_action_OriginalData_triggered(); break;
        case 8: _t->on_action_DecodeLog_triggered(); break;
        case 9: _t->on_action_Help_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject BaseWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BaseWindow.data,
      qt_meta_data_BaseWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *BaseWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BaseWindow.stringdata))
        return static_cast<void*>(const_cast< BaseWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BaseWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
