/****************************************************************************
** Meta object code from reading C++ file 'AnalyzeRule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/AnalyzeRule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnalyzeRule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AnalyzeRule_t {
    QByteArrayData data[23];
    char stringdata[420];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnalyzeRule_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnalyzeRule_t qt_meta_stringdata_AnalyzeRule = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 27),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 4),
QT_MOC_LITERAL(4, 46, 32),
QT_MOC_LITERAL(5, 79, 16),
QT_MOC_LITERAL(6, 96, 4),
QT_MOC_LITERAL(7, 101, 20),
QT_MOC_LITERAL(8, 122, 24),
QT_MOC_LITERAL(9, 147, 21),
QT_MOC_LITERAL(10, 169, 23),
QT_MOC_LITERAL(11, 193, 24),
QT_MOC_LITERAL(12, 218, 22),
QT_MOC_LITERAL(13, 241, 21),
QT_MOC_LITERAL(14, 263, 27),
QT_MOC_LITERAL(15, 291, 5),
QT_MOC_LITERAL(16, 297, 31),
QT_MOC_LITERAL(17, 329, 16),
QT_MOC_LITERAL(18, 346, 6),
QT_MOC_LITERAL(19, 353, 32),
QT_MOC_LITERAL(20, 386, 7),
QT_MOC_LITERAL(21, 394, 8),
QT_MOC_LITERAL(22, 403, 16)
    },
    "AnalyzeRule\0on_inputKeyword_textChanged\0"
    "\0arg1\0on_projectList_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_btnCancel_clicked\0"
    "on_checkBox_stateChanged\0on_btnSetRule_clicked\0"
    "on_inputTea_textChanged\0"
    "on_inputBias_textChanged\0"
    "on_inputCV_textChanged\0on_btnAddRule_clicked\0"
    "on_listWidget_doubleClicked\0index\0"
    "on_treeWidget_itemDoubleClicked\0"
    "QTreeWidgetItem*\0column\0"
    "on_treeWidget_currentItemChanged\0"
    "current\0previous\0DrawProjectChart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnalyzeRule[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       4,    1,   82,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    1,   88,    2, 0x08 /* Private */,
      11,    1,   91,    2, 0x08 /* Private */,
      12,    1,   94,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    1,   98,    2, 0x08 /* Private */,
      16,    2,  101,    2, 0x08 /* Private */,
      19,    2,  106,    2, 0x08 /* Private */,
      22,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,    6,   18,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 17,   20,   21,
    QMetaType::Void,

       0        // eod
};

void AnalyzeRule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnalyzeRule *_t = static_cast<AnalyzeRule *>(_o);
        switch (_id) {
        case 0: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_projectList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_btnCancel_clicked(); break;
        case 3: _t->on_checkBox_stateChanged(); break;
        case 4: _t->on_btnSetRule_clicked(); break;
        case 5: _t->on_inputTea_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_inputBias_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_inputCV_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_btnAddRule_clicked(); break;
        case 9: _t->on_listWidget_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->on_treeWidget_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 12: _t->DrawProjectChart(); break;
        default: ;
        }
    }
}

const QMetaObject AnalyzeRule::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AnalyzeRule.data,
      qt_meta_data_AnalyzeRule,  qt_static_metacall, 0, 0}
};


const QMetaObject *AnalyzeRule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnalyzeRule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnalyzeRule.stringdata))
        return static_cast<void*>(const_cast< AnalyzeRule*>(this));
    return QDialog::qt_metacast(_clname);
}

int AnalyzeRule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
