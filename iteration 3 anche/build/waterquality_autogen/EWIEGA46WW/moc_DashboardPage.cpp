/****************************************************************************
** Meta object code from reading C++ file 'DashboardPage.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../DashboardPage.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DashboardPage.hpp' doesn't include <QObject>."
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
struct qt_meta_stringdata_DashboardPage_t {
    uint offsetsAndSizes[24];
    char stringdata0[14];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[14];
    char stringdata5[28];
    char stringdata6[19];
    char stringdata7[31];
    char stringdata8[35];
    char stringdata9[25];
    char stringdata10[23];
    char stringdata11[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_DashboardPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_DashboardPage_t qt_meta_stringdata_DashboardPage = {
    {
        QT_MOC_LITERAL(0, 13),  // "DashboardPage"
        QT_MOC_LITERAL(14, 21),  // "requestLanguageChange"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 12),  // "languageCode"
        QT_MOC_LITERAL(50, 13),  // "retranslateUi"
        QT_MOC_LITERAL(64, 27),  // "navigateToPollutantOverview"
        QT_MOC_LITERAL(92, 18),  // "navigateToPOPsPage"
        QT_MOC_LITERAL(111, 30),  // "navigateToLitterIndicatorsPage"
        QT_MOC_LITERAL(142, 34),  // "navigateToFluorinatedCompound..."
        QT_MOC_LITERAL(177, 24),  // "navigateToCompliancePage"
        QT_MOC_LITERAL(202, 22),  // "navigateToHotspotsPage"
        QT_MOC_LITERAL(225, 16)   // "showLanguageMenu"
    },
    "DashboardPage",
    "requestLanguageChange",
    "",
    "languageCode",
    "retranslateUi",
    "navigateToPollutantOverview",
    "navigateToPOPsPage",
    "navigateToLitterIndicatorsPage",
    "navigateToFluorinatedCompoundsPage",
    "navigateToCompliancePage",
    "navigateToHotspotsPage",
    "showLanguageMenu"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_DashboardPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   71,    2, 0x0a,    3 /* Public */,
       5,    0,   72,    2, 0x08,    4 /* Private */,
       6,    0,   73,    2, 0x08,    5 /* Private */,
       7,    0,   74,    2, 0x08,    6 /* Private */,
       8,    0,   75,    2, 0x08,    7 /* Private */,
       9,    0,   76,    2, 0x08,    8 /* Private */,
      10,    0,   77,    2, 0x08,    9 /* Private */,
      11,    0,   78,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
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

Q_CONSTINIT const QMetaObject DashboardPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DashboardPage.offsetsAndSizes,
    qt_meta_data_DashboardPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_DashboardPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DashboardPage, std::true_type>,
        // method 'requestLanguageChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'retranslateUi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showLanguageMenu'
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
        case 0: _t->requestLanguageChange((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->retranslateUi(); break;
        case 2: _t->navigateToPollutantOverview(); break;
        case 3: _t->navigateToPOPsPage(); break;
        case 4: _t->navigateToLitterIndicatorsPage(); break;
        case 5: _t->navigateToFluorinatedCompoundsPage(); break;
        case 6: _t->navigateToCompliancePage(); break;
        case 7: _t->navigateToHotspotsPage(); break;
        case 8: _t->showLanguageMenu(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DashboardPage::*)(const QString & );
            if (_t _q_method = &DashboardPage::requestLanguageChange; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *DashboardPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DashboardPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DashboardPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DashboardPage::requestLanguageChange(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
