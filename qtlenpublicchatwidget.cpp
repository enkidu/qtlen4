#include "qtlenpublicchatwidget.h"

QTlenPublicChatWidget::QTlenPublicChatWidget(QWidget * parent): QWidget(parent)
{
    list = new QListWidget(this);
    list->setSortingEnabled(true);
    browser = new QTextBrowser(this);
    input = new QTlenTextEdit(this);
    QSplitter *vsplitter = new QSplitter(this);
    vsplitter->setOrientation(Qt::Vertical);
    QSplitter *hsplitter = new QSplitter(this);
    hsplitter->setOrientation(Qt::Horizontal);
    vsplitter->addWidget(browser);
    vsplitter->addWidget(input);
    hsplitter->addWidget(vsplitter);
    hsplitter->addWidget(list);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(hsplitter);
    this->setLayout(layout);
    connect(input,
            SIGNAL(returnPressed()),
            this,
            SLOT(sendMessage()));
    connect(list,
            SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,
            SLOT(itemDoubleClicked(QListWidgetItem*)));
}

void QTlenPublicChatWidget::appendMessage(QString nick, QString body)
{
    browser->append("<" + nick + "> " + body);
}

void QTlenPublicChatWidget::presence(QString nick, int a, bool ok)
{
    QList<QListWidgetItem*> l = list->findItems(nick, Qt::MatchExactly);
    if (l.isEmpty() && ok)
    {
        QIcon icon;
        switch (a)
        {
            case 0:
                icon.addPixmap(QPixmap(":/icons/icons/16x16/user.png"));
                break;
            case 1:
                icon.addPixmap(QPixmap(":/icons/icons/16x16/owner.png"));
                break;
            case 2:
                icon.addPixmap(QPixmap(":/icons/icons/16x16/admin.png"));
                break;
            case 4:
                icon.addPixmap(QPixmap(":/icons/icons/16x16/banned.png"));
                break;
            case 5:
                icon.addPixmap(QPixmap(":/icons/icons/16x16/superuser.png"));
                break;
        }
        QListWidgetItem* i = new QListWidgetItem;
        i->setIcon(icon);
        i->setText(nick);
        list->addItem(i);
    }
    else
    {
        QListWidgetItem* i = list->takeItem(list->row(l.at(0)));
        if (i != 0)
            delete i;
    }
}

void QTlenPublicChatWidget::sendMessage()
{
    emit message(roomId, input->toPlainText());
    input->clear();
}

void QTlenPublicChatWidget::setRoomId(QString id)
{
    this->roomId = id;
}

void QTlenPublicChatWidget::itemDoubleClicked(QListWidgetItem *item)
{
    emit startPriv(roomId + "/" + item->text());
    qDebug("starting priv");
}
