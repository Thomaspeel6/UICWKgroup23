/****************************************************************************
** Meta object code from reading C++ file 'window.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../window.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS = QtMocHelpers::stringData(
    "waterQualityWindow",
    "uploadRealData",
    "",
    "uploadComplianceData",
    "startProgressBar",
    "message",
    "updateProgressBar",
    "QTimer*",
    "timer",
    "successMessage",
    "displayStats",
    "about"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[19];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[17];
    char stringdata5[8];
    char stringdata6[18];
    char stringdata7[8];
    char stringdata8[6];
    char stringdata9[15];
    char stringdata10[13];
    char stringdata11[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS_t qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "waterQualityWindow"
        QT_MOC_LITERAL(19, 14),  // "uploadRealData"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 20),  // "uploadComplianceData"
        QT_MOC_LITERAL(56, 16),  // "startProgressBar"
        QT_MOC_LITERAL(73, 7),  // "message"
        QT_MOC_LITERAL(81, 17),  // "updateProgressBar"
        QT_MOC_LITERAL(99, 7),  // "QTimer*"
        QT_MOC_LITERAL(107, 5),  // "timer"
        QT_MOC_LITERAL(113, 14),  // "successMessage"
        QT_MOC_LITERAL(128, 12),  // "displayStats"
        QT_MOC_LITERAL(141, 5)   // "about"
    },
    "waterQualityWindow",
    "uploadRealData",
    "",
    "uploadComplianceData",
    "startProgressBar",
    "message",
    "updateProgressBar",
    "QTimer*",
    "timer",
    "successMessage",
    "displayStats",
    "about"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwaterQualityWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    1,   52,    2, 0x08,    3 /* Private */,
       6,    2,   55,    2, 0x08,    5 /* Private */,
      10,    0,   60,    2, 0x08,    8 /* Private */,
      11,    0,   61,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject waterQualityWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwaterQualityWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<waterQualityWindow, std::true_type>,
        // method 'uploadRealData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'uploadComplianceData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startProgressBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateProgressBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTimer *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'displayStats'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'about'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void waterQualityWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<waterQualityWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->uploadRealData(); break;
        case 1: _t->uploadComplianceData(); break;
        case 2: _t->startProgressBar((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->updateProgressBar((*reinterpret_cast< std::add_pointer_t<QTimer*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->displayStats(); break;
        case 5: _t->about(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTimer* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *waterQualityWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *waterQualityWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwaterQualityWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int waterQualityWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
