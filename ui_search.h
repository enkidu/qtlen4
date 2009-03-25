/********************************************************************************
** Form generated from reading ui file 'search.ui'
**
** Created: Sun Feb 15 05:39:34 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SEARCH_H
#define UI_SEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *le_first;
    QLabel *label_3;
    QLineEdit *le_last;
    QLineEdit *le_mail;
    QLabel *label_4;
    QLineEdit *le_nick;
    QLabel *label_2;
    QLineEdit *le_school;
    QLabel *label_5;
    QLineEdit *le_city;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *sb_ageMin;
    QLabel *label_9;
    QSpinBox *sb_ageMax;
    QPushButton *pb_search;
    QPushButton *pb_clear;
    QCheckBox *cb_onlines;
    QTreeWidget *tw_output;
    QFrame *frame_2;

    void setupUi(QWidget *SearchDialog)
    {
    if (SearchDialog->objectName().isEmpty())
        SearchDialog->setObjectName(QString::fromUtf8("SearchDialog"));
    SearchDialog->resize(472, 503);
    verticalLayout_2 = new QVBoxLayout(SearchDialog);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    frame = new QFrame(SearchDialog);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    gridLayout = new QGridLayout(frame);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    le_first = new QLineEdit(frame);
    le_first->setObjectName(QString::fromUtf8("le_first"));

    gridLayout->addWidget(le_first, 0, 1, 1, 1);

    label_3 = new QLabel(frame);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 0, 2, 1, 1);

    le_last = new QLineEdit(frame);
    le_last->setObjectName(QString::fromUtf8("le_last"));

    gridLayout->addWidget(le_last, 0, 3, 1, 1);

    le_mail = new QLineEdit(frame);
    le_mail->setObjectName(QString::fromUtf8("le_mail"));

    gridLayout->addWidget(le_mail, 1, 3, 1, 1);

    label_4 = new QLabel(frame);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout->addWidget(label_4, 1, 2, 1, 1);

    le_nick = new QLineEdit(frame);
    le_nick->setObjectName(QString::fromUtf8("le_nick"));

    gridLayout->addWidget(le_nick, 1, 1, 1, 1);

    label_2 = new QLabel(frame);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    le_school = new QLineEdit(frame);
    le_school->setObjectName(QString::fromUtf8("le_school"));

    gridLayout->addWidget(le_school, 2, 1, 1, 1);

    label_5 = new QLabel(frame);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout->addWidget(label_5, 2, 0, 1, 1);

    le_city = new QLineEdit(frame);
    le_city->setObjectName(QString::fromUtf8("le_city"));

    gridLayout->addWidget(le_city, 2, 3, 1, 1);

    label_6 = new QLabel(frame);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout->addWidget(label_6, 2, 2, 1, 1);

    comboBox = new QComboBox(frame);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));

    gridLayout->addWidget(comboBox, 3, 1, 1, 1);

    label_7 = new QLabel(frame);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout->addWidget(label_7, 3, 0, 1, 1);

    label_8 = new QLabel(frame);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    gridLayout->addWidget(label_8, 4, 0, 1, 1);

    sb_ageMin = new QSpinBox(frame);
    sb_ageMin->setObjectName(QString::fromUtf8("sb_ageMin"));
    sb_ageMin->setMaximum(150);

    gridLayout->addWidget(sb_ageMin, 4, 1, 1, 1);

    label_9 = new QLabel(frame);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    gridLayout->addWidget(label_9, 4, 2, 1, 1);

    sb_ageMax = new QSpinBox(frame);
    sb_ageMax->setObjectName(QString::fromUtf8("sb_ageMax"));
    sb_ageMax->setMaximum(150);

    gridLayout->addWidget(sb_ageMax, 4, 3, 1, 1);

    pb_search = new QPushButton(frame);
    pb_search->setObjectName(QString::fromUtf8("pb_search"));

    gridLayout->addWidget(pb_search, 5, 3, 1, 1);

    pb_clear = new QPushButton(frame);
    pb_clear->setObjectName(QString::fromUtf8("pb_clear"));

    gridLayout->addWidget(pb_clear, 5, 1, 1, 1);

    cb_onlines = new QCheckBox(frame);
    cb_onlines->setObjectName(QString::fromUtf8("cb_onlines"));

    gridLayout->addWidget(cb_onlines, 3, 3, 1, 1);


    verticalLayout_2->addWidget(frame);

    tw_output = new QTreeWidget(SearchDialog);
    tw_output->setObjectName(QString::fromUtf8("tw_output"));
    tw_output->setRootIsDecorated(false);
    tw_output->setItemsExpandable(false);
    tw_output->setAllColumnsShowFocus(true);
    tw_output->setExpandsOnDoubleClick(false);

    verticalLayout_2->addWidget(tw_output);

    frame_2 = new QFrame(SearchDialog);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);

    verticalLayout_2->addWidget(frame_2);


    retranslateUi(SearchDialog);

    QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QWidget *SearchDialog)
    {
    SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "SearchDialog", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SearchDialog", "Imi\304\231", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("SearchDialog", "Nazwisko", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("SearchDialog", "E-mail", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SearchDialog", "Nick", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("SearchDialog", "Szko\305\202a", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("SearchDialog", "Miejscowo\305\233\304\207", 0, QApplication::UnicodeUTF8));
    comboBox->clear();
    comboBox->insertItems(0, QStringList()
     << QApplication::translate("SearchDialog", "-- nieustawione --", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("SearchDialog", "m\304\231\305\274czyzna", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("SearchDialog", "kobieta", 0, QApplication::UnicodeUTF8)
    );
    label_7->setText(QApplication::translate("SearchDialog", "P\305\202e\304\207", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("SearchDialog", "Wiek od", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("SearchDialog", "Do", 0, QApplication::UnicodeUTF8));
    pb_search->setText(QApplication::translate("SearchDialog", "Szukaj", 0, QApplication::UnicodeUTF8));
    pb_clear->setText(QApplication::translate("SearchDialog", "Wyczy\305\233\304\207", 0, QApplication::UnicodeUTF8));
    cb_onlines->setText(QApplication::translate("SearchDialog", "Ludzie online", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(0, QApplication::translate("SearchDialog", "Tlen ID", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(1, QApplication::translate("SearchDialog", "Imi\304\231", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(2, QApplication::translate("SearchDialog", "Nazwisko", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(3, QApplication::translate("SearchDialog", "Nick", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(4, QApplication::translate("SearchDialog", "E-mail", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(5, QApplication::translate("SearchDialog", "Szko\305\202a", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(6, QApplication::translate("SearchDialog", "Miejscowo\305\233\304\207", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(7, QApplication::translate("SearchDialog", "P\305\202e\304\207", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(8, QApplication::translate("SearchDialog", "Wiek", 0, QApplication::UnicodeUTF8));
    tw_output->headerItem()->setText(9, QApplication::translate("SearchDialog", "Status", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SearchDialog);
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_H
