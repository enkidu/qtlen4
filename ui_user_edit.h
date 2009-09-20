/********************************************************************************
** Form generated from reading ui file 'user_edit.ui'
**
** Created: Fri Jul 24 20:20:02 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_USER_EDIT_H
#define UI_USER_EDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userEditWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *le_jid;
    QLabel *label_2;
    QLineEdit *le_nick;
    QLabel *label_3;
    QComboBox *cb_group;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *userEditWindow)
    {
        if (userEditWindow->objectName().isEmpty())
            userEditWindow->setObjectName(QString::fromUtf8("userEditWindow"));
        userEditWindow->resize(400, 140);
        verticalLayout = new QVBoxLayout(userEditWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(userEditWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        le_jid = new QLineEdit(frame);
        le_jid->setObjectName(QString::fromUtf8("le_jid"));

        formLayout->setWidget(0, QFormLayout::FieldRole, le_jid);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        le_nick = new QLineEdit(frame);
        le_nick->setObjectName(QString::fromUtf8("le_nick"));

        formLayout->setWidget(1, QFormLayout::FieldRole, le_nick);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        cb_group = new QComboBox(frame);
        cb_group->setObjectName(QString::fromUtf8("cb_group"));
        cb_group->setEditable(true);
        cb_group->setFrame(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, cb_group);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(userEditWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(userEditWindow);

        QMetaObject::connectSlotsByName(userEditWindow);
    } // setupUi

    void retranslateUi(QWidget *userEditWindow)
    {
        userEditWindow->setWindowTitle(QApplication::translate("userEditWindow", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("userEditWindow", "Identyfikator Tlen.pl", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        le_jid->setToolTip(QApplication::translate("userEditWindow", "Identyfikator u\305\274ytkownika, bez '@tlen.pl'", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("userEditWindow", "Nazwa", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        le_nick->setToolTip(QApplication::translate("userEditWindow", "Nazwa u\305\274ytkownika (imi\304\231, pseudonim)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("userEditWindow", "Grupa", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cb_group->setToolTip(QApplication::translate("userEditWindow", "Grupa", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Q_UNUSED(userEditWindow);
    } // retranslateUi

};

namespace Ui {
    class userEditWindow: public Ui_userEditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_EDIT_H
