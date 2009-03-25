#include "qtlenpublicchatswindow.hpp"

QTlenPublicChatsWindow::QTlenPublicChatsWindow(QWidget * parent, Qt::WFlags f):QWidget(parent, f)
{
    resize(550, 400); //TODO: wczytywanie zapamiętanych wartości
    setWindowTitle("Czaty");
    tabWidget  = new QTabWidget(this);
    mainPage = new QTreeWidget(this);
    tabWidget->addTab(mainPage, "Lista pokoi");
    QStringList headers;
    headers << tr("Name", "Chatroom name") << tr("Users", "Users count");
    mainPage->setHeaderLabels(headers);
}
