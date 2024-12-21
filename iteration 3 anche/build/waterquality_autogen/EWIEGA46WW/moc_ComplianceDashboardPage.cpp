/****************************************************************************
** Meta object code from reading C++ file 'ComplianceDashboardPage.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ComplianceDashboardPage.hpp"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComplianceDashboardPage.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ComplianceDashboardPage_t {
    uint offsetsAndSizes[10];
    char stringdata0[24];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ComplianceDashboardPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ComplianceDashboardPage_t qt_meta_stringdata_ComplianceDashboardPage = {
    {
        QT_MOC_LITERAL(0, 23),  // "ComplianceDashboardPage"
        QT_MOC_LITERAL(24, 14),  // "onApplyFilters"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 10),  // "onNextPage"
        QT_MOC_LITERAL(51, 14)   // "onPreviousPage"
    },
    "ComplianceDashboardPage",
    "onApplyFilters",
    "",
    "onNextPage",
    "onPreviousPage"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ComplianceDashboardPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x08,    1 /* Private */,
       3,    0,   33,    2, 0x08,    2 /* Private */,
       4,    0,   34,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ComplianceDashboardPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ComplianceDashboardPage.offsetsAndSizes,
    qt_meta_data_ComplianceDashboardPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ComplianceDashboardPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ComplianceDashboardPage, std::true_type>,
        // method 'onApplyFilters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNextPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPreviousPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ComplianceDashboardPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ComplianceDashboardPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onApplyFilters(); break;
        case 1: _t->onNextPage(); break;
        case 2: _t->onPreviousPage(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ComplianceDashboardPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComplianceDashboardPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComplianceDashboardPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ComplianceDashboardPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
