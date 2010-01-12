#include "qtlenpublicchatswindow.hpp"

QTlenPublicChatsWindow::QTlenPublicChatsWindow(QWidget * parent, Qt::WFlags f):QWidget(parent, f)
{
    resize(550, 400); //TODO: wczytywanie zapamiętanych wartości
    setWindowTitle("Czaty");
    QHBoxLayout* layout = new QHBoxLayout(this);
    tabWidget  = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    layout->addWidget(tabWidget);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
    mainPage = new QTreeWidget(this);
    tabWidget->addTab(mainPage, "Lista pokoi");
    QStringList headers;
    headers << tr("Name", "Chatroom name") << tr("Users", "Users count");
    mainPage->setHeaderLabels(headers);
}

void QTlenPublicChatsWindow::openPublicChats(QString id)
{
    QString nick = QInputDialog::getText(this,
                                         tr("Enter nickname"),
                                         tr("nickname"));
    emit chatRoomRequest(id, nick);
}

void QTlenPublicChatsWindow::spawnChat(QTlenPublicChatWidget* w, QString name)
{
    this->tabWidget->addTab(w, name);
}

void QTlenPublicChatsWindow::closeEvent(QCloseEvent* event)
{
    this->hide();
    event->ignore();
}
