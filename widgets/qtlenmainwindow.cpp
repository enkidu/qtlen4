#include "qtlenmainwindow.hpp"

QTlenMainWindow::QTlenMainWindow(QWidget * parent, Qt::WFlags f):QMainWindow(parent, f)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(328, 388); //TODO: wczytywanie zapamiętanych wartości
    setWindowTitle("QTlen4");

    QIcon icon1;
    QIcon icon2;
    QIcon icon3;
    QIcon icon4;
    QIcon icon5;
    QIcon icon6;
    QIcon icon7;
    QIcon icon8;
    QIcon icon9;
    QIcon icon10;
    QIcon icon11;

    icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/configure.png")), QIcon::Normal, QIcon::Off);
    icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/user-properties.png")), QIcon::Normal, QIcon::Off);
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/application-exit.png")), QIcon::Normal, QIcon::Off);
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/preferences-plugin-script.png")), QIcon::Normal, QIcon::Off);
    icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png")), QIcon::Normal, QIcon::Off);
    icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png")), QIcon::Normal, QIcon::Off);
    icon7.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png")), QIcon::Normal, QIcon::Off);
    icon8.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png")), QIcon::Normal, QIcon::Off);
    icon9.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png")), QIcon::Normal, QIcon::Off);
    icon10.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/invisible.png")), QIcon::Normal, QIcon::Off);
    icon11.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/offline.png")), QIcon::Normal, QIcon::Off);

    centralwidget   = new QWidget(this);

    menuBar         = new QMenuBar(this);
    menuBar         ->setGeometry(QRect(0, 0, 328, 25));

    setMenuBar(menuBar);

    lv_roster       = new QTlenRosterBox(centralwidget);
    te_status       = new QTlenTextEdit(centralwidget);
    lb_status	    = new QTlenStatusLabel(centralwidget);
    cb_status       = new QComboBox(centralwidget);
    lb_avatar	    = new QTlenAvatarLabel(centralwidget);
    pbar_connecting = new QProgressBar(centralwidget);

    verticalLayout  = new QVBoxLayout(centralwidget);
    verticalLayout  ->setSpacing(0);
    verticalLayout  ->setMargin(0);

    presenceLayout  = new QHBoxLayout();
    presenceLayout  ->setSpacing(2);
    presenceLayout  ->setMargin(0);

    lb_status	    ->setWordWrap(true);
    lb_status	    ->setFrameShape(QFrame::StyledPanel);
    lb_status	    ->setFrameShadow(QFrame::Sunken);
    te_status	    ->hide();

    connect(lb_status,
	    SIGNAL(editRequested(QRect)),
	    te_status,
	    SLOT(show(QRect)));
    connect(te_status,
	    SIGNAL(returnPressed()),
	    te_status,
	    SLOT(hide()));
    connect(te_status,
	    SIGNAL(returnPressed()),
	    lb_status,
	    SLOT(show()));
    connect(te_status,
	    SIGNAL(escapePressed()),
	    te_status,
	    SLOT(hide()));
    connect(te_status,
	    SIGNAL(escapePressed()),
	    lb_status,
	    SLOT(show()));

    lb_avatar	    ->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/64x64/default_av.png")), 32, 32);
    connect(lb_avatar->actionUpload,
	    SIGNAL(triggered()),
	    this,
	    SIGNAL(setAvatar()));
    cb_status       ->addItem(icon5, tr("Online"));
    cb_status       ->addItem(icon6, tr("Chatty"));
    cb_status       ->addItem(icon7, tr("Away"));
    cb_status       ->addItem(icon8, tr("Extended away"));
    cb_status       ->addItem(icon9, tr("Busy"));
    cb_status       ->addItem(icon10, tr("Invisible"));
    cb_status       ->addItem(icon11, tr("Offline"));
    cb_status       ->setCurrentIndex(6);
    pbar_connecting ->setMaximum(4);
    pbar_connecting ->setValue(0);
    pbar_connecting ->hide();

    verticalLayout  ->addWidget(lv_roster);
    verticalLayout  ->addWidget(lb_status);
    verticalLayout  ->addWidget(te_status);
    verticalLayout  ->addLayout(presenceLayout);
    presenceLayout  ->addWidget(cb_status);
    presenceLayout  ->addWidget(lb_avatar);
    verticalLayout  ->addWidget(pbar_connecting);

    setCentralWidget(centralwidget);

    menuMenu        = menuBar->addMenu(tr("Menu"));
    menuHelp        = menuBar->addMenu(tr("Help"));

    actionSettings      = new QAction(icon1, tr("Settings"), menuMenu);
    actionMyInfo        = new QAction(icon2, tr("My info"), menuMenu);
    actionExit          = new QAction(icon3, tr("Exit"), menuMenu);
    actionXMLConsole    = new QAction(icon4, tr("XML console"), menuMenu);
    actionXMLConsole    ->setCheckable(true);
    actionChats         = new QAction(tr("Tlen.pl chats"), menuMenu);
    actionSearch        = new QAction(tr("Search for contacts"), menuMenu);
    actionAboutQTlen    = new QAction(tr("About..."), menuHelp);
    actionAboutQt       = new QAction(tr("About Qt4"), menuHelp);

    menuBar->addAction(menuMenu->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuMenu->addAction(actionSettings);
    menuMenu->addAction(actionMyInfo);
    menuMenu->addAction(actionSearch);
    menuMenu->addAction(actionChats);
    menuMenu->addSeparator();
    menuMenu->addAction(actionXMLConsole);
    menuMenu->addSeparator();
    menuMenu->addAction(actionExit);
    menuHelp->addAction(actionAboutQTlen);
    menuHelp->addAction(actionAboutQt);
    connect(actionAboutQt,
	    SIGNAL(triggered()),
	    qApp,
	    SLOT(aboutQt()));
}

void QTlenMainWindow::closeEvent(QCloseEvent *event)
{
        event->ignore();
        this->hide();
}

void QTlenMainWindow::displayAlert(QString jid)
{
        QMessageBox::information(this,
				 "QTlen4",
                                 "User " + jid + " wants you to be online");
}

void QTlenMainWindow::subscriptionRequestReceived(QString jid)
{
        int msg = QMessageBox::question(this,
                                        tr("Autorization request"),
                                        "Użytkownik " + jid + " chce dodać Cię do swojej listy kontaktów",
                                        QMessageBox::Yes,
                                        QMessageBox::No);
        if( msg == QMessageBox::Yes )
        {
                emit subscribed(jid, true);
        }
        else
        {
                emit subscribed(jid, false);
        }
}

void QTlenMainWindow::menuActionDelete()
{
        int msg = QMessageBox::question(this,
					tr("Confirmation"),
					tr("Are you sure to remove selected contact?"),
                                        QMessageBox::Yes,
                                        QMessageBox::No);
        if( msg == QMessageBox::Yes )
            emit deleteUser(lv_roster->currentItem());
}

void QTlenMainWindow::menuActionShowOfflines(bool yesno)
{
        emit showOfflines(yesno);
}

void QTlenMainWindow::menuActionAdd()
{
        emit addContact();
}
//napisać...
void QTlenMainWindow::menuActionInfo()
{
    emit info(lv_roster->currentItem());
}

void QTlenMainWindow::menuActionHistory()
{
emit history(lv_roster->currentItem());
}

void QTlenMainWindow::menuActionChat()
{
    emit chat(lv_roster->currentItem());
}

void QTlenMainWindow::menuActionEdit()
{
    emit editUser(lv_roster->currentItem());
}
