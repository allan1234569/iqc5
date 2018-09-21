/****************************************************************************
** Meta object code from reading C++ file 'AnalyzeProject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iqc5/UI/AnalyzeProject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnalyzeProject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AProcess_t {
    QByteArrayData data[1];
    char stringdata[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AProcess_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AProcess_t qt_meta_stringdata_AProcess = {
    {
QT_MOC_LITERAL(0, 0, 8)
    },
    "AProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AProcess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void AProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject AProcess::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AProcess.data,
      qt_meta_data_AProcess,  qt_static_metacall, 0, 0}
};


const QMetaObject *AProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AProcess.stringdata))
        return static_cast<void*>(const_cast< AProcess*>(this));
    return QThread::qt_metacast(_clname);
}

int AProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_AnalyzeProject_t {
    QByteArrayData data[34];
    char stringdata[674];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnalyzeProject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnalyzeProject_t qt_meta_stringdata_AnalyzeProject = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 20),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 27),
QT_MOC_LITERAL(4, 65, 4),
QT_MOC_LITERAL(5, 70, 24),
QT_MOC_LITERAL(6, 95, 21),
QT_MOC_LITERAL(7, 117, 27),
QT_MOC_LITERAL(8, 145, 5),
QT_MOC_LITERAL(9, 151, 20),
QT_MOC_LITERAL(10, 172, 26),
QT_MOC_LITERAL(11, 199, 32),
QT_MOC_LITERAL(12, 232, 16),
QT_MOC_LITERAL(13, 249, 7),
QT_MOC_LITERAL(14, 257, 8),
QT_MOC_LITERAL(15, 266, 27),
QT_MOC_LITERAL(16, 294, 19),
QT_MOC_LITERAL(17, 314, 23),
QT_MOC_LITERAL(18, 338, 27),
QT_MOC_LITERAL(19, 366, 26),
QT_MOC_LITERAL(20, 393, 25),
QT_MOC_LITERAL(21, 419, 4),
QT_MOC_LITERAL(22, 424, 23),
QT_MOC_LITERAL(23, 448, 21),
QT_MOC_LITERAL(24, 470, 7),
QT_MOC_LITERAL(25, 478, 20),
QT_MOC_LITERAL(26, 499, 22),
QT_MOC_LITERAL(27, 522, 18),
QT_MOC_LITERAL(28, 541, 21),
QT_MOC_LITERAL(29, 563, 31),
QT_MOC_LITERAL(30, 595, 16),
QT_MOC_LITERAL(31, 612, 4),
QT_MOC_LITERAL(32, 617, 34),
QT_MOC_LITERAL(33, 652, 21)
    },
    "AnalyzeProject\0on_btnCancel_clicked\0"
    "\0on_inputKeyword_textChanged\0arg1\0"
    "on_checkBox_stateChanged\0on_btnAddRule_clicked\0"
    "on_listWidget_doubleClicked\0index\0"
    "on_btnExport_clicked\0on_btnExportByType_clicked\0"
    "on_treeWidget_currentItemChanged\0"
    "QTreeWidgetItem*\0current\0previous\0"
    "on_tabWidget_currentChanged\0"
    "on_btnPrint_clicked\0on_btnDataTable_clicked\0"
    "on_inputCustAvg_textChanged\0"
    "on_inputCustSD_textChanged\0"
    "on_inputStartDate_Changed\0date\0"
    "on_inputEndDate_Changed\0on_IfCaculate_toggled\0"
    "checked\0on_btnImport_clicked\0"
    "on_btnCaculate_clicked\0on_btnInit_clicked\0"
    "on_cbkShowAll_toggled\0"
    "on_listWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0"
    "on_listWidget_itemSelectionChanged\0"
    "on_dataImport_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnalyzeProject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  129,    2, 0x08 /* Private */,
       3,    1,  130,    2, 0x08 /* Private */,
       5,    0,  133,    2, 0x08 /* Private */,
       6,    0,  134,    2, 0x08 /* Private */,
       7,    1,  135,    2, 0x08 /* Private */,
       9,    0,  138,    2, 0x08 /* Private */,
      10,    0,  139,    2, 0x08 /* Private */,
      11,    2,  140,    2, 0x08 /* Private */,
      15,    1,  145,    2, 0x08 /* Private */,
      16,    0,  148,    2, 0x08 /* Private */,
      17,    0,  149,    2, 0x08 /* Private */,
      18,    1,  150,    2, 0x08 /* Private */,
      19,    1,  153,    2, 0x08 /* Private */,
      20,    1,  156,    2, 0x08 /* Private */,
      22,    1,  159,    2, 0x08 /* Private */,
      23,    1,  162,    2, 0x08 /* Private */,
      25,    0,  165,    2, 0x08 /* Private */,
      26,    0,  166,    2, 0x08 /* Private */,
      27,    0,  167,    2, 0x08 /* Private */,
      28,    1,  168,    2, 0x08 /* Private */,
      29,    1,  171,    2, 0x08 /* Private */,
      32,    0,  174,    2, 0x08 /* Private */,
      33,    0,  175,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12,   13,   14,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QDate,   21,
    QMetaType::Void, QMetaType::QDate,   21,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AnalyzeProject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnalyzeProject *_t = static_cast<AnalyzeProject *>(_o);
        switch (_id) {
        case 0: _t->on_btnCancel_clicked(); break;
        case 1: _t->on_inputKeyword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_checkBox_stateChanged(); break;
        case 3: _t->on_btnAddRule_clicked(); break;
        case 4: _t->on_listWidget_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_btnExport_clicked(); break;
        case 6: _t->on_btnExportByType_clicked(); break;
        case 7: _t->on_treeWidget_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 8: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_btnPrint_clicked(); break;
        case 10: _t->on_btnDataTable_clicked(); break;
        case 11: _t->on_inputCustAvg_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_inputCustSD_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_inputStartDate_Changed((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 14: _t->on_inputEndDate_Changed((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 15: _t->on_IfCaculate_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_btnImport_clicked(); break;
        case 17: _t->on_btnCaculate_clicked(); break;
        case 18: _t->on_btnInit_clicked(); break;
        case 19: _t->on_cbkShowAll_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 21: _t->on_listWidget_itemSelectionChanged(); break;
        case 22: _t->on_dataImport_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject AnalyzeProject::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AnalyzeProject.data,
      qt_meta_data_AnalyzeProject,  qt_static_metacall, 0, 0}
};


const QMetaObject *AnalyzeProject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnalyzeProject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnalyzeProject.stringdata))
        return static_cast<void*>(const_cast< AnalyzeProject*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AnalyzeProject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
