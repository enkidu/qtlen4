/********************************************************************************
** Form generated from reading ui file 'config.ui'
**
** Created: Fri Jul 24 20:20:02 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *connection_page;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *le_login;
    QLabel *label_2;
    QLineEdit *le_password;
    QCheckBox *cb_autoConnect;
    QLabel *label_3;
    QComboBox *cb_defaultState;
    QWidget *roster_page;
    QVBoxLayout *verticalLayout;
    QCheckBox *cb_showOfflines;
    QCheckBox *cb_showExtendedInfo;
    QCheckBox *cb_showAvatars;
    QCheckBox *cb_showDescriptions;
    QCheckBox *cb_showJidInRoster;
    QGroupBox *gb_expandPolicy;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rb_expandedState;
    QRadioButton *rb_collapsedState;
    QRadioButton *rb_previousState;
    QWidget *chats_page;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QFormLayout *formLayout_4;
    QLabel *label_5;
    QLineEdit *le_nick;
    QLabel *label_7;
    QLabel *label_6;
    QPushButton *pb_myColor;
    QPushButton *pb_myBg;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_5;
    QLabel *label_8;
    QCheckBox *cb_useJID;
    QPushButton *pb_chatColor;
    QPushButton *pb_chatBg;
    QLabel *label_9;
    QWidget *network_page;

    void setupUi(QWidget *configDialog)
    {
        if (configDialog->objectName().isEmpty())
            configDialog->setObjectName(QString::fromUtf8("configDialog"));
        configDialog->resize(480, 264);
        horizontalLayout_2 = new QHBoxLayout(configDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listWidget = new QListWidget(configDialog);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(150, 0));
        listWidget->setMaximumSize(QSize(150, 16777215));
        listWidget->setBaseSize(QSize(150, 0));

        horizontalLayout_2->addWidget(listWidget);

        stackedWidget = new QStackedWidget(configDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        connection_page = new QWidget();
        connection_page->setObjectName(QString::fromUtf8("connection_page"));
        formLayout = new QFormLayout(connection_page);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(connection_page);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        le_login = new QLineEdit(connection_page);
        le_login->setObjectName(QString::fromUtf8("le_login"));

        formLayout->setWidget(0, QFormLayout::FieldRole, le_login);

        label_2 = new QLabel(connection_page);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        le_password = new QLineEdit(connection_page);
        le_password->setObjectName(QString::fromUtf8("le_password"));
        le_password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, le_password);

        cb_autoConnect = new QCheckBox(connection_page);
        cb_autoConnect->setObjectName(QString::fromUtf8("cb_autoConnect"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cb_autoConnect);

        label_3 = new QLabel(connection_page);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        cb_defaultState = new QComboBox(connection_page);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/16x16/online.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_defaultState->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/16x16/chatty.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_defaultState->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/16x16/away.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_defaultState->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/16x16/xa.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_defaultState->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/16x16/dnd.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_defaultState->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/16x16/invisible.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_defaultState->addItem(icon5, QString());
        cb_defaultState->addItem(QString());
        cb_defaultState->setObjectName(QString::fromUtf8("cb_defaultState"));
        cb_defaultState->setEnabled(false);

        formLayout->setWidget(3, QFormLayout::FieldRole, cb_defaultState);

        stackedWidget->addWidget(connection_page);
        roster_page = new QWidget();
        roster_page->setObjectName(QString::fromUtf8("roster_page"));
        verticalLayout = new QVBoxLayout(roster_page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cb_showOfflines = new QCheckBox(roster_page);
        cb_showOfflines->setObjectName(QString::fromUtf8("cb_showOfflines"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/view-user-offline-kopete.png"), QSize(), QIcon::Normal, QIcon::Off);
        cb_showOfflines->setIcon(icon6);

        verticalLayout->addWidget(cb_showOfflines);

        cb_showExtendedInfo = new QCheckBox(roster_page);
        cb_showExtendedInfo->setObjectName(QString::fromUtf8("cb_showExtendedInfo"));

        verticalLayout->addWidget(cb_showExtendedInfo);

        cb_showAvatars = new QCheckBox(roster_page);
        cb_showAvatars->setObjectName(QString::fromUtf8("cb_showAvatars"));

        verticalLayout->addWidget(cb_showAvatars);

        cb_showDescriptions = new QCheckBox(roster_page);
        cb_showDescriptions->setObjectName(QString::fromUtf8("cb_showDescriptions"));

        verticalLayout->addWidget(cb_showDescriptions);

        cb_showJidInRoster = new QCheckBox(roster_page);
        cb_showJidInRoster->setObjectName(QString::fromUtf8("cb_showJidInRoster"));

        verticalLayout->addWidget(cb_showJidInRoster);

        gb_expandPolicy = new QGroupBox(roster_page);
        gb_expandPolicy->setObjectName(QString::fromUtf8("gb_expandPolicy"));
        verticalLayout_2 = new QVBoxLayout(gb_expandPolicy);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rb_expandedState = new QRadioButton(gb_expandPolicy);
        rb_expandedState->setObjectName(QString::fromUtf8("rb_expandedState"));

        verticalLayout_2->addWidget(rb_expandedState);

        rb_collapsedState = new QRadioButton(gb_expandPolicy);
        rb_collapsedState->setObjectName(QString::fromUtf8("rb_collapsedState"));

        verticalLayout_2->addWidget(rb_collapsedState);

        rb_previousState = new QRadioButton(gb_expandPolicy);
        rb_previousState->setObjectName(QString::fromUtf8("rb_previousState"));

        verticalLayout_2->addWidget(rb_previousState);


        verticalLayout->addWidget(gb_expandPolicy);

        stackedWidget->addWidget(roster_page);
        chats_page = new QWidget();
        chats_page->setObjectName(QString::fromUtf8("chats_page"));
        verticalLayout_4 = new QVBoxLayout(chats_page);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea = new QScrollArea(chats_page);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 330, 261));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setMargin(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_4 = new QFormLayout(groupBox);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_5);

        le_nick = new QLineEdit(groupBox);
        le_nick->setObjectName(QString::fromUtf8("le_nick"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, le_nick);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_4->setWidget(4, QFormLayout::LabelRole, label_7);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_6);

        pb_myColor = new QPushButton(groupBox);
        pb_myColor->setObjectName(QString::fromUtf8("pb_myColor"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, pb_myColor);

        pb_myBg = new QPushButton(groupBox);
        pb_myBg->setObjectName(QString::fromUtf8("pb_myBg"));

        formLayout_4->setWidget(4, QFormLayout::FieldRole, pb_myBg);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_5 = new QFormLayout(groupBox_2);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_8);

        cb_useJID = new QCheckBox(groupBox_2);
        cb_useJID->setObjectName(QString::fromUtf8("cb_useJID"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, cb_useJID);

        pb_chatColor = new QPushButton(groupBox_2);
        pb_chatColor->setObjectName(QString::fromUtf8("pb_chatColor"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, pb_chatColor);

        pb_chatBg = new QPushButton(groupBox_2);
        pb_chatBg->setObjectName(QString::fromUtf8("pb_chatBg"));

        formLayout_5->setWidget(2, QFormLayout::FieldRole, pb_chatBg);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_9);


        verticalLayout_3->addWidget(groupBox_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);

        stackedWidget->addWidget(chats_page);
        network_page = new QWidget();
        network_page->setObjectName(QString::fromUtf8("network_page"));
        stackedWidget->addWidget(network_page);

        horizontalLayout_2->addWidget(stackedWidget);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(le_login);
        label_2->setBuddy(le_password);
#endif // QT_NO_SHORTCUT

        retranslateUi(configDialog);
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));

        QMetaObject::connectSlotsByName(configDialog);
    } // setupUi

    void retranslateUi(QWidget *configDialog)
    {
        configDialog->setWindowTitle(QApplication::translate("configDialog", "Form", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("configDialog", "Po\305\202\304\205czenie", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("configDialog", "Lista kontakt\303\263w", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("configDialog", "Wygl\304\205d", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("configDialog", "Sie\304\207", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("configDialog", "Login", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("configDialog", "Has\305\202o", 0, QApplication::UnicodeUTF8));
        cb_autoConnect->setText(QApplication::translate("configDialog", "Po\305\202\304\205cz po uruchomieniu", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("configDialog", "Domy\305\233lny status", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(0, QApplication::translate("configDialog", "Dost\304\231pny", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(1, QApplication::translate("configDialog", "Porozmawiajmy", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(2, QApplication::translate("configDialog", "Zaraz wracam", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(3, QApplication::translate("configDialog", "Wracam p\303\263\305\272niej", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(4, QApplication::translate("configDialog", "Zaj\304\231ty", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(5, QApplication::translate("configDialog", "Niewidoczny", 0, QApplication::UnicodeUTF8));
        cb_defaultState->setItemText(6, QApplication::translate("configDialog", "--Poprzedni", 0, QApplication::UnicodeUTF8));

        cb_showOfflines->setText(QApplication::translate("configDialog", "Pokazuj nieobecnych", 0, QApplication::UnicodeUTF8));
        cb_showExtendedInfo->setText(QApplication::translate("configDialog", "Pokazuj rozszerzone informacje o kontaktach", 0, QApplication::UnicodeUTF8));
        cb_showAvatars->setText(QApplication::translate("configDialog", "Pokazuj avatary u\305\274ytkownik\303\263w", 0, QApplication::UnicodeUTF8));
        cb_showDescriptions->setText(QApplication::translate("configDialog", "Pokazuj opisy", 0, QApplication::UnicodeUTF8));
        cb_showJidInRoster->setText(QApplication::translate("configDialog", "Pokazuj login u\305\274ytkownika na li\305\233cie kontakt\303\263w", 0, QApplication::UnicodeUTF8));
        gb_expandPolicy->setTitle(QApplication::translate("configDialog", "Rozwijanie grup", 0, QApplication::UnicodeUTF8));
        rb_expandedState->setText(QApplication::translate("configDialog", "Domy\305\233lnie rozwini\304\231te", 0, QApplication::UnicodeUTF8));
        rb_collapsedState->setText(QApplication::translate("configDialog", "Domy\305\233lnie zwini\304\231te", 0, QApplication::UnicodeUTF8));
        rb_previousState->setText(QApplication::translate("configDialog", "Pami\304\231taj status", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("configDialog", "Wys\305\202ane", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("configDialog", "Nick", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("configDialog", "Kolor t\305\202a", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("configDialog", "Kolor tekstu", 0, QApplication::UnicodeUTF8));
        pb_myColor->setText(QApplication::translate("configDialog", "Wybierz", 0, QApplication::UnicodeUTF8));
        pb_myBg->setText(QApplication::translate("configDialog", "Wybierz", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("configDialog", "Odebrane", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("configDialog", "Kolor tekstu", 0, QApplication::UnicodeUTF8));
        cb_useJID->setText(QApplication::translate("configDialog", "U\305\274ywaj ID zamiast nazwy kontaktu", 0, QApplication::UnicodeUTF8));
        pb_chatColor->setText(QApplication::translate("configDialog", "Wybierz", 0, QApplication::UnicodeUTF8));
        pb_chatBg->setText(QApplication::translate("configDialog", "Wybierz", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("configDialog", "Kolor t\305\202a", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(configDialog);
    } // retranslateUi

};

namespace Ui {
    class configDialog: public Ui_configDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
