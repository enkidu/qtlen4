#include "qtlenchatcontainer.hpp"

QTlenChatContainer::QTlenChatContainer(QWidget * parent, Qt::WFlags f):QMainWindow(parent, f)
{
        settings        = new QSettings(QDir::homePath() + "/.qtlen4/config", QSettings::IniFormat);
        resize(settings->value("/preferences/chatWindow/width", 343).toInt(),
               settings->value("/preferences/chatWindow/height", 449).toInt());
        QWidget *centralwidget = new QWidget(this);
        stack = new QStackedWidget(0);
        tabbar = new QTabBar(0);
        tabbar->setTabsClosable(true);
        connect(tabbar,
                SIGNAL(tabCloseRequested(int)),
                this,
                SLOT(closeAndRemove(int)));
        connect(tabbar,
                SIGNAL(currentChanged(int)),
                this,
                SLOT(tabChanged(int)));

        QVBoxLayout *layout = new QVBoxLayout(centralwidget);
        layout->setSpacing(0);
        layout->setMargin(0);
        layout->addWidget(tabbar);
        layout->addWidget(stack);
        this->setCentralWidget(centralwidget);
        blinkTimer = new QTimer(this);
        blinkTimer->setInterval(500);
        connect(blinkTimer,
                SIGNAL(timeout()),
                this,
                SLOT(swapTitle()));
}

QTlenChatWidget * QTlenChatContainer::addChat()
{
    qDebug("calling QTlenChatContainer::addChat()");
        QTlenChatWidget * widget = new QTlenChatWidget;
        stack->addWidget(widget);
        tabbar->addTab("");
        return widget;
}

void QTlenChatContainer::setTabText(QTlenChatWidget * widget, QString name)
{
    qDebug("calling QTlenChatContainer::setTabText()");
    int index = stack->indexOf(widget);
    if (index != -1)
        tabbar->setTabText(index, name);
    if (tabbar->count() == 1)
        this->setWindowTitle(name);
}

void QTlenChatContainer::setTabColour(QTlenChatWidget * widget, QColor color)
{
    int index = stack->indexOf(widget);
    if (index != -1)
        tabbar->setTabTextColor(index, color);
}

void QTlenChatContainer::closeAndRemove(int tab)
{
    QWidget *widget = stack->widget(tab);
    if (widget != 0)
    {
        stack->removeWidget(widget);
        widget->close();
    }
    tabbar->removeTab(tab);
}

void QTlenChatContainer::tabChanged(int tab)
{
    stack->setCurrentIndex(tab);
    blinkTimer->stop();
    if (tabbar->tabTextColor(tab) == QColor("#f00"))
        tabbar->setTabTextColor(tab, QColor("#000"));
    this->setWindowTitle(tabbar->tabText(tab));
}

void QTlenChatContainer::showEvent(QShowEvent *event)
{
    if (event->spontaneous())
    {
        blinkTimer->stop();
        if (windowTitle() == "")\
             setWindowTitle(title);
    }
    event->accept();
}

void QTlenChatContainer::startBlinking()
{
    blinkTimer->start();
}

void QTlenChatContainer::closeEvent(QCloseEvent *event)
{
    while (stack->count() != 0)
    {
        qDebug(QByteArray::number(stack->count()));
        closeAndRemove(0);

    }
        settings->setValue("/preferences/chatWindow/width", width());
        settings->setValue("/preferences/chatWindow/height", height());
        event->accept();
}

void QTlenChatContainer::swapTitle()
{
    if (windowTitle() != "")
    {
        title = windowTitle();
        setWindowTitle("");

    }
    else
    {
        setWindowTitle(title);
    }
    if (isActiveWindow())
    {
        blinkTimer->stop();
        setWindowTitle(title);
    }
}
