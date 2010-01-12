#include "debug.h"

QTlenDebugWindow::QTlenDebugWindow(QWidget * parent, Qt::WFlags f):QWidget(parent, f)
{
	ui.setupUi(this);
	ui.debug_console->setReadOnly(true);
        //connect(ui.textInput, SIGNAL(returnPressed()), this, SLOT(sendXML()));
        connect(ui.ps_sendXML, SIGNAL(clicked()), this, SLOT(sendXML()));
}

void QTlenDebugWindow::showXml(QByteArray xml)
{
	ui.debug_console->moveCursor(QTextCursor::End);
	ui.debug_console->insertPlainText(xml+"\n\n");
}

void QTlenDebugWindow::closeEvent(QCloseEvent *event)
{
	event->ignore();
	this->hide();
}

void QTlenDebugWindow::sendXML()
{
	emit XMLsend(ui.textInput->toPlainText());
	ui.textInput->clear();
}
