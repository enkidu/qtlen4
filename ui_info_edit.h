/********************************************************************************
** Form generated from reading ui file 'info_edit.ui'
**
** Created: Fri Jul 24 20:20:02 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INFO_EDIT_H
#define UI_INFO_EDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myInfo
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *le_first;
    QLabel *label_2;
    QLineEdit *le_last;
    QLabel *label_3;
    QLineEdit *le_nick;
    QLabel *label_4;
    QLineEdit *le_mail;
    QLabel *label_10;
    QLineEdit *le_city;
    QLabel *label_11;
    QLineEdit *le_school;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *cb_sex;
    QLabel *label_7;
    QComboBox *cb_lookingFor;
    QLabel *label_8;
    QComboBox *cb_job;
    QCheckBox *cb_showMyStatus;
    QPushButton *pb_save;
    QSpinBox *sb_year;

    void setupUi(QWidget *myInfo)
    {
        if (myInfo->objectName().isEmpty())
            myInfo->setObjectName(QString::fromUtf8("myInfo"));
        myInfo->resize(375, 410);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(myInfo->sizePolicy().hasHeightForWidth());
        myInfo->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(myInfo);
        formLayout->setMargin(2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(myInfo);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        le_first = new QLineEdit(myInfo);
        le_first->setObjectName(QString::fromUtf8("le_first"));

        formLayout->setWidget(0, QFormLayout::FieldRole, le_first);

        label_2 = new QLabel(myInfo);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        le_last = new QLineEdit(myInfo);
        le_last->setObjectName(QString::fromUtf8("le_last"));

        formLayout->setWidget(1, QFormLayout::FieldRole, le_last);

        label_3 = new QLabel(myInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        le_nick = new QLineEdit(myInfo);
        le_nick->setObjectName(QString::fromUtf8("le_nick"));

        formLayout->setWidget(2, QFormLayout::FieldRole, le_nick);

        label_4 = new QLabel(myInfo);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        le_mail = new QLineEdit(myInfo);
        le_mail->setObjectName(QString::fromUtf8("le_mail"));

        formLayout->setWidget(3, QFormLayout::FieldRole, le_mail);

        label_10 = new QLabel(myInfo);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_10);

        le_city = new QLineEdit(myInfo);
        le_city->setObjectName(QString::fromUtf8("le_city"));

        formLayout->setWidget(4, QFormLayout::FieldRole, le_city);

        label_11 = new QLabel(myInfo);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_11);

        le_school = new QLineEdit(myInfo);
        le_school->setObjectName(QString::fromUtf8("le_school"));

        formLayout->setWidget(5, QFormLayout::FieldRole, le_school);

        label_5 = new QLabel(myInfo);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(myInfo);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_6);

        cb_sex = new QComboBox(myInfo);
        cb_sex->setObjectName(QString::fromUtf8("cb_sex"));

        formLayout->setWidget(7, QFormLayout::FieldRole, cb_sex);

        label_7 = new QLabel(myInfo);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_7);

        cb_lookingFor = new QComboBox(myInfo);
        cb_lookingFor->setObjectName(QString::fromUtf8("cb_lookingFor"));

        formLayout->setWidget(8, QFormLayout::FieldRole, cb_lookingFor);

        label_8 = new QLabel(myInfo);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_8);

        cb_job = new QComboBox(myInfo);
        cb_job->setObjectName(QString::fromUtf8("cb_job"));

        formLayout->setWidget(9, QFormLayout::FieldRole, cb_job);

        cb_showMyStatus = new QCheckBox(myInfo);
        cb_showMyStatus->setObjectName(QString::fromUtf8("cb_showMyStatus"));

        formLayout->setWidget(10, QFormLayout::FieldRole, cb_showMyStatus);

        pb_save = new QPushButton(myInfo);
        pb_save->setObjectName(QString::fromUtf8("pb_save"));

        formLayout->setWidget(11, QFormLayout::FieldRole, pb_save);

        sb_year = new QSpinBox(myInfo);
        sb_year->setObjectName(QString::fromUtf8("sb_year"));
        sb_year->setAccelerated(true);
        sb_year->setMinimum(0);
        sb_year->setMaximum(2100);
        sb_year->setValue(0);

        formLayout->setWidget(6, QFormLayout::FieldRole, sb_year);

        label->raise();
        le_first->raise();
        label_2->raise();
        le_last->raise();
        label_3->raise();
        le_nick->raise();
        label_4->raise();
        le_mail->raise();
        label_5->raise();
        label_6->raise();
        cb_sex->raise();
        label_7->raise();
        cb_lookingFor->raise();
        label_8->raise();
        cb_job->raise();
        cb_showMyStatus->raise();
        le_city->raise();
        le_school->raise();
        label_10->raise();
        label_11->raise();
        pb_save->raise();
        sb_year->raise();

        retranslateUi(myInfo);

        QMetaObject::connectSlotsByName(myInfo);
    } // setupUi

    void retranslateUi(QWidget *myInfo)
    {
        myInfo->setWindowTitle(QApplication::translate("myInfo", "Moje Dane", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("myInfo", "Imi\304\231", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("myInfo", "Nazwisko", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("myInfo", "Nick", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("myInfo", "E-mail", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("myInfo", "Miejscowo\305\233\304\207", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("myInfo", "Szko\305\202a / uczelnia", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("myInfo", "Rok urodzenia", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("myInfo", "P\305\202e\304\207", 0, QApplication::UnicodeUTF8));
        cb_sex->clear();
        cb_sex->insertItems(0, QStringList()
         << QApplication::translate("myInfo", "-- nieustawione --", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "m\304\231\305\274czyzna", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "kobieta", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("myInfo", "Szukam...", 0, QApplication::UnicodeUTF8));
        cb_lookingFor->clear();
        cb_lookingFor->insertItems(0, QStringList()
         << QApplication::translate("myInfo", "-- nieustawione --", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "kogo\305\233 do rozmowy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "przyja\305\272ni", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "flirtu / romansu", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "mi\305\202o\305\233ci", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "nie szukam", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("myInfo", "Zaw\303\263d", 0, QApplication::UnicodeUTF8));
        cb_job->clear();
        cb_job->insertItems(0, QStringList()
         << QApplication::translate("myInfo", "-- nieustawione --", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "ucze\305\204", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "student", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "rolnik", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "mened\305\274er", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "specjalista/wolny zaw\303\263d", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "urz\304\231dnik/us\305\202ugi/administracja", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "bezrobotny", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "emeryt/rencista", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "gospodyni domowa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "nauczyciel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "lekarz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("myInfo", "inny", 0, QApplication::UnicodeUTF8)
        );
        cb_showMyStatus->setText(QApplication::translate("myInfo", "Pokazuj m\303\263j status w katalogu", 0, QApplication::UnicodeUTF8));
        pb_save->setText(QApplication::translate("myInfo", "Zapisz", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(myInfo);
    } // retranslateUi

};

namespace Ui {
    class myInfo: public Ui_myInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_EDIT_H
