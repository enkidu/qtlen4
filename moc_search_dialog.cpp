/****************************************************************************
** Meta object code from reading C++ file 'search_dialog.h'
**
** Created: Mon Feb 16 01:50:08 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "search_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTlenSearchDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   18,   18,   18, 0x0a,
      57,   18,   18,   18, 0x0a,
      83,   18,   18,   18, 0x0a,
      97,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QTlenSearchDialog[] = {
    "QTlenSearchDialog\0\0search(QTlenUserInfo)\0"
    "beginInfo(bool)\0appendItem(QTlenUserInfo)\0"
    "sendRequest()\0clearForm()\0"
};

const QMetaObject QTlenSearchDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QTlenSearchDialog,
      qt_meta_data_QTlenSearchDialog, 0 }
};

const QMetaObject *QTlenSearchDialog::metaObject() const
{
    return &staticMetaObject;
}

void *QTlenSearchDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTlenSearchDialog))
        return static_cast<void*>(const_cast< QTlenSearchDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int QTlenSearchDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: search((*reinterpret_cast< QTlenUserInfo(*)>(_a[1]))); break;
        case 1: beginInfo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: appendItem((*reinterpret_cast< QTlenUserInfo(*)>(_a[1]))); break;
        case 3: sendRequest(); break;
        case 4: clearForm(); break;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QTlenSearchDialog::search(QTlenUserInfo _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
