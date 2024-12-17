/****************************************************************************
** Meta object code from reading C++ file 'DashboardPage.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../DashboardPage.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DashboardPage.hpp' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSDashboardPageENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSDashboardPageENDCLASS = QtMocHelpers::stringData(
    "DashboardPage",
    "navigateToPollutantOverview",
    "",
    "navigateToPOPsPage",
    "navigateToLitterIndicatorsPage",
    "navigateToFluorinatedCompoundsPage",
    "navigateToCompliancePage",
    "navigateToHotspotsPage"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSDashboardPageENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[14];
    char stringdata1[28];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[31];
    char stringdata5[35];
    char stringdata6[25];
    char stringdata7[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSDashboardPageENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSDashboardPageENDCLASS_t qt_meta_stringdata_CLASSDashboardPageENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "DashboardPage"
        QT_MOC_LITERAL(14, 27),  // "navigateToPollutantOverview"
        QT_MOC_LITERAL(42, 0),  // ""
        QT_MOC_LITERAL(43, 18),  // "navigateToPOPsPage"
        QT_MOC_LITERAL(62, 30),  // "navigateToLitterIndicatorsPage"
        QT_MOC_LITERAL(93, 34),  // "navigateToFluorinatedCompound..."
        QT_MOC_LITERAL(128, 24),  // "navigateToCompliancePage"
        QT_MOC_LITERAL(153, 22)   // "navigateToHotspotsPage"
    },
    "DashboardPage",
    "navigateToPollutantOverview",
    "",
    "navigateToPOPsPage",
    "navigateToLitterIndicatorsPage",
    "navigateToFluorinatedCompoundsPage",
    "navigateToCompliancePage",
    "navigateToHotspotsPage"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDashboardPageENDCLASS[] = {

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
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject DashboardPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSDashboardPageENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDashboardPageENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSDashboardPageENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DashboardPage, std::true_type>,
        // method 'navigateToPollutantOverview'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigateToPOPsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigateToLitterIndicatorsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigateToFluorinatedCompoundsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigateToCompliancePage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'navigateToHotspotsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void DashboardPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DashboardPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->navigateToPollutantOverview(); break;
        case 1: _t->navigateToPOPsPage(); break;
        case 2: _t->navigateToLitterIndicatorsPage(); break;
        case 3: _t->navigateToFluorinatedCompoundsPage(); break;
        case 4: _t->navigateToCompliancePage(); break;
        case 5: _t->navigateToHotspotsPage(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *DashboardPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDashboardPageENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DashboardPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
