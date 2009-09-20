/********************************************************************************
** Form generated from reading ui file 'debug.ui'
**
** Created: Fri Jul 24 20:20:02 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DEBUG_H
#define UI_DEBUG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_debugWindow
{
public:
    QGridLayout *gridLayout;
    QTextEdit *debug_console;
    QPlainTextEdit *textInput;
    QPushButton *ps_sendXML;

    void setupUi(QWidget *debugWindow)
    {
        if (debugWindow->objectName().isEmpty())
            debugWindow->setObjectName(QString::fromUtf8("debugWindow"));
        debugWindow->resize(338, 295);
        gridLayout = new QGridLayout(debugWindow);
        gridLayout->setSpacing(0);
        gridLayout->setMargin(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        debug_console = new QTextEdit(debugWindow);
        debug_console->setObjectName(QString::fromUtf8("debug_console"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(4);
        sizePolicy.setHeightForWidth(debug_console->sizePolicy().hasHeightForWidth());
        debug_console->setSizePolicy(sizePolicy);
        debug_console->setStyleSheet(QString::fromUtf8("div.parsed\n"
"{\n"
"	font-weight: bold;\n"
"	color: #00f;\n"
"}\n"
"div.sent\n"
"{\n"
"	font-weight: bold;\n"
"	color: #0e0;\n"
"}\n"
"div.unparsed\n"
"{\n"
"	font-weight:bold;\n"
"	color: #d00;\n"
"}"));
        debug_console->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(debug_console, 0, 0, 1, 1);

        textInput = new QPlainTextEdit(debugWindow);
        textInput->setObjectName(QString::fromUtf8("textInput"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(textInput->sizePolicy().hasHeightForWidth());
        textInput->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(textInput, 1, 0, 1, 1);

        ps_sendXML = new QPushButton(debugWindow);
        ps_sendXML->setObjectName(QString::fromUtf8("ps_sendXML"));

        gridLayout->addWidget(ps_sendXML, 2, 0, 1, 1);


        retranslateUi(debugWindow);

        QMetaObject::connectSlotsByName(debugWindow);
    } // setupUi

    void retranslateUi(QWidget *debugWindow)
    {
        debugWindow->setWindowTitle(QApplication::translate("debugWindow", "XML", 0, QApplication::UnicodeUTF8));
        debug_console->setHtml(QApplication::translate("debugWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        ps_sendXML->setText(QApplication::translate("debugWindow", "wy\305\233lij XML", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(debugWindow);
    } // retranslateUi

};

namespace Ui {
    class debugWindow: public Ui_debugWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUG_H
