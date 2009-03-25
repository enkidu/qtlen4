#include "form1.h"
#include "sha1.h"

QTlenManager::QTlenManager():QObject()
{
        QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
        QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));
        mainWindow = new QTlenMainWindow(0, 0);
        mainWindow->show();

	settings = new QSettings(QDir::homePath() + "/.qtlen4/config", QSettings::IniFormat);
	if (settings->value("/avatar/present", false).toBool())
	{
	    mainWindow->lb_avatar->setPixmap(QPixmap(QString(QDir::homePath() + "/.qtlen4/avatar.png")), 32, 32);
	    mainWindow->lb_avatar->setToolTip("<img src=\"" + QDir::homePath() + "/.qtlen4/avatar.png\" />");
	}
	sysIcon = new QTlenTrayIcon(0);
	sysIcon->show();

	roster = new QTlenRosterManager(mainWindow->lv_roster, sysIcon);
        roster->showOfflines(settings->value("/roster/offlines_visible", false).toBool());

	history = new QTlenHistoryManager();

	tlen = new QTlen;
	tlen->setUserParams(settings->value("/connection/username").toString(), settings->value("/connection/password").toString());

	debug = new QTlenDebugWindow();
	if (settings->value("/advanced/xmlconsole", false).toBool())
		debug->show();
	chats = new QTlenChatManager(roster, history);
	chats->setMyInfo(settings->value("/preferences/nick",
					 settings->value("/connection/username").toString()).toString(),
			 settings->value("/connection/username").toString());
	chats->setTrayIcon(sysIcon);

	mainWindow->te_status->setPlainText(settings->value("/status/last", "").toString());
	if (settings->value("/status/last", "").toString().isEmpty())
	    mainWindow->lb_status->setText("Komunikat statusu");
	else
	    mainWindow->lb_status->setText(settings->value("/status/last", "").toString());

	connect(mainWindow->actionXMLConsole,	SIGNAL(toggled(bool)),					debug,		SLOT(setVisible(bool)));
	connect(mainWindow->actionChats,	SIGNAL(activated()),				tlen,		SLOT(chatsGetTopLevelGroups()));
	connect(tlen,			SIGNAL(socketError(QAbstractSocket::SocketError)),	this,	SLOT(displayError(QAbstractSocket::SocketError)));
	connect(mainWindow->actionMyInfo,	SIGNAL(activated()),					tlen,		SLOT(getInfoAboutMyself()));
	connect(mainWindow->cb_status,		SIGNAL(currentIndexChanged(int)),			this,		SLOT(setStatus(int)));
	connect(mainWindow->te_status,		SIGNAL(returnPressed()),				this,		SLOT(setStatus()));
	connect(this,			SIGNAL(setStatus(int, QString)),			tlen,		SLOT(setStatus(int, QString)));

	connect(sysIcon,		SIGNAL(activated(QSystemTrayIcon::ActivationReason)),	this,	SLOT(toggleVisible(QSystemTrayIcon::ActivationReason)));
	connect(sysIcon,		SIGNAL(setStatus(int)),					mainWindow->cb_status,	SLOT(setCurrentIndex(int)));
	connect(sysIcon,		SIGNAL(appExit()),					this,		SLOT(appExit()));
	connect(mainWindow->actionExit,		SIGNAL(triggered()),					this,		SLOT(appExit()));
	connect(mainWindow->lv_roster,		SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),	this,		SLOT(openChat(QTreeWidgetItem*, int)));
	connect(chats,			SIGNAL(sendMessage(QString, QString)),			tlen,		SLOT(sendMessage(QString, QString)));

	connect(debug,			SIGNAL(XMLsend(QString)),	tlen,	SLOT(sendRawXML(QString)));


        //new connections
        //inbound
        connect(tlen,
                SIGNAL(soundAlert(QString)),
                mainWindow,
                SLOT(displayAlert(QString)));
        connect(tlen,
                SIGNAL(autorizationRequest(QString)),
                mainWindow,
                SLOT(subscriptionRequestReceived(QString)));
        connect(tlen,
                SIGNAL(typingStarted(QString)),
                chats,
                SLOT(typingStarted(QString)));
        connect(tlen,
                SIGNAL(typingStopped(QString)),
                chats,
                SLOT(typingStopped(QString)));
        connect(tlen,
                SIGNAL(message(QString, QString, QDateTime)),
                chats,
                SLOT(showMessage(QString, QString, QDateTime)));
        connect(tlen,
                SIGNAL(connecting()),
                this,
                SLOT(respondForConnecting()));
        connect(tlen,
                SIGNAL(serverConnect()),
                this,
                SLOT(respondForServerConnect()));
        connect(tlen,
                SIGNAL(connected()),
                this,
                SLOT(respondForConnected()));
        connect(tlen,
                SIGNAL(rosterInfoEnd()),
                this,
                SLOT(respondForRosterEnd()));
        connect(tlen,
                SIGNAL(myInfoArrived(QTlenUserInfo)),
                this,
                SLOT(myInfoArrived(QTlenUserInfo)));
	connect(tlen,
                SIGNAL(receivedXml(QByteArray)),
                debug,
		SLOT(showXml(QByteArray)));
        connect(tlen,
                SIGNAL(disconnected()),
                this,
                SLOT(respondForDisconnected()));
        connect(tlen,
                SIGNAL(authenticated()),
                this,
                SLOT(respondForAuthenticated()));
        connect(tlen,
                SIGNAL(rosterInfoBegin()),
                roster,
                SLOT(beginRoster()));
        connect(tlen,
                SIGNAL(rosterItem(QString, QString, QString, QString)),
                roster,
                SLOT(addItem(QString, QString, QString, QString)));
        connect(tlen,
		SIGNAL(presenceFrom(QString, QTlenPresence, QString, QString, QString)),
                roster,
		SLOT(presenceFrom(QString, QTlenPresence, QString, QString, QString)));
        connect(tlen,
                SIGNAL(rosterInfoEnd()),
                roster,
                SLOT(showRoster()));
	connect(tlen,
		SIGNAL(receivedMailConfig(QTlenMailConfig)),
		roster,
		SLOT(setMailFetchInfo(QTlenMailConfig)));
	connect(tlen,
		SIGNAL(receivedToken(QString)),
		roster,
		SLOT(setToken(QString)));
	connect(tlen,
		SIGNAL(readyToGetRoster()),
		this,
		SLOT(setStatus()));
	connect(mainWindow,
		SIGNAL(setAvatar()),
		this,
		SLOT(openAvatarDialog()));
	connect(roster,
		SIGNAL(avatarSaved()),
		this,
		SLOT(avatarSaved()));
	connect(roster,
		SIGNAL(savingError()),
		this,
		SLOT(avatarSavingError()));
        //outbound
        connect(mainWindow,
                SIGNAL(subscribed(QString, bool)),
                tlen,
                SLOT(setSubscribed(QString, bool)));
        connect(mainWindow->actionSearch,
                SIGNAL(triggered()),
                this,
                SLOT(openSearchDialog()));
        connect(mainWindow->actionSettings,
                SIGNAL(triggered()),
                this,
                SLOT(openConfigDialog()));
        connect(mainWindow,
                SIGNAL(addContact()),
                this,
                SLOT(menuActionAdd()));
        connect(mainWindow,
                SIGNAL(showOfflines(bool)),
                this,
                SLOT(menuActionShowOfflines(bool)));
	connect(chats,
		SIGNAL(sendTyping(QString,bool)),
		tlen,
		SLOT(writeTyping(QString,bool)));
	connect(this,
		SIGNAL(saveAvatar(QImage)),
		roster,
		SLOT(saveMyAvatar(QImage)));
	connect(mainWindow,
		SIGNAL(chat(QTreeWidgetItem*)),
		this,
		SLOT(menuActionChat(QTreeWidgetItem*)));
	connect(mainWindow,
		SIGNAL(info(QTreeWidgetItem*)),
		this,
		SLOT(menuActionInfo(QTreeWidgetItem*)));
	connect(mainWindow,
		SIGNAL(editUser(QTreeWidgetItem*)),
		this,
		SLOT(menuActionEdit(QTreeWidgetItem*)));
}

void QTlenManager::openConfigDialog()
{
	QTlenConfigDialog *config = new QTlenConfigDialog();
	config->show();
        connect(config,
                SIGNAL(configChanged(QTlenSettingsChange)),
                this,
                SLOT(configChanged(QTlenSettingsChange)));
}

void QTlenManager::configChanged(QTlenSettingsChange change)
{
    if(change.roster)
        roster->showRoster();
    if(change.user)
	tlen->setUserParams(settings->value("/connection/username").toString(),
			    settings->value("/connection/password").toString());
}

void QTlenManager::openSearchDialog()
{
    if (tlen->is_connected())
    {
	QTlenSearchDialog *searchDialog = new QTlenSearchDialog();
	searchDialog->show();
        connect(tlen,
                SIGNAL(searchItem(QTlenUserInfo)),
                searchDialog,
                SLOT(appendItem(QTlenUserInfo)));
        connect(tlen,
                SIGNAL(searchResultBegin(bool)),
                searchDialog,
                SLOT(beginInfo(bool)));
        connect(searchDialog,
                SIGNAL(search(QTlenUserInfo)),
                tlen,
                SLOT(searchUsers(QTlenUserInfo)));
        connect(searchDialog,
                SIGNAL(openChat(QString)),
                chats,
                SLOT(openChat(QString)));
        connect(searchDialog,
                SIGNAL(addContact(QString)),
                this,
                SLOT(menuActionAdd(QString)));
    }
}

void QTlenManager::showMessage(QString from, QString body, QDateTime timestamp)
{
	sysIcon->showMessage("Message from " + from, body);
}

void QTlenManager::respondForAuthenticated()
{
	mainWindow->pbar_connecting->setFormat(tr("Retrieving roster..."));
	mainWindow->pbar_connecting->setValue(3);
}

void QTlenManager::setStatus(int code)
{
	QByteArray status[] = 
	{
		"online",
		"chatty",
		"away",
		"extended away",
		"do not disturb",
		"invisible",
		"offline"
	};
	emit setStatus(code, mainWindow->te_status->toPlainText());
	sysIcon->setStatusIcon(mainWindow->cb_status->currentIndex());
	sysIcon->setToolTip("<b>You are now " + status[code] + "</b><br>" + mainWindow->te_status->toPlainText().toLocal8Bit());
}

void QTlenManager::setStatus()
{	
	QByteArray status[] = 
	{
		"online",
		"chatty",
		"away",
		"extended away",
		"do not disturb",
		"invisible",
		"offline"
	};
	emit setStatus(mainWindow->cb_status->currentIndex(), mainWindow->te_status->toPlainText());
	settings->setValue("/status/last", mainWindow->te_status->toPlainText());
	if (mainWindow->te_status->toPlainText().isEmpty())
	    mainWindow->lb_status->setText("Komunikat statusu");
	else
	    mainWindow->lb_status->setText(mainWindow->te_status->toPlainText());
	sysIcon->setToolTip("<b>You are now " + status[mainWindow->cb_status->currentIndex()] + "</b><br>" + mainWindow->te_status->toPlainText().toLocal8Bit());
}

void QTlenManager::respondForDisconnected()
{
	mainWindow->lv_roster->clear();
	sysIcon->showMessage("QTlenCore Message", "You are now disconnected");
}

void QTlenManager::toggleVisible(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger)
	{
		if (mainWindow->isVisible())
			mainWindow->hide();
		else
			mainWindow->show();
	}
}

void QTlenManager::appExit()
{
	emit setStatus(0, mainWindow->te_status->toPlainText());
	exit(0);
}

void QTlenManager::openChat(QTreeWidgetItem* item, int unused)
{
	chats->openChat(roster->getJidOf(item));
}

void QTlenManager::respondForConnecting()
{
	mainWindow->pbar_connecting->show();
	mainWindow->pbar_connecting->setFormat(tr("Looking for server address"));
	mainWindow->pbar_connecting->setValue(0);
}
void QTlenManager::respondForServerConnect()
{
	mainWindow->pbar_connecting->setFormat(tr("Connecting to server"));
	mainWindow->pbar_connecting->setValue(1);
}
void QTlenManager::respondForConnected()
{
	mainWindow->pbar_connecting->setFormat(tr("Authorization"));
	mainWindow->pbar_connecting->setValue(2);
}
void QTlenManager::respondForRosterEnd()
{
	mainWindow->pbar_connecting->setValue(4);
	mainWindow->pbar_connecting->hide();
}

void QTlenManager::menuActionInfo(QTreeWidgetItem *item)
{
	tlen->getInfoAbout(roster->getJidOf(item));
}

void QTlenManager::menuActionChat(QTreeWidgetItem *item)
{
	chats->openChat(roster->getJidOf(item));
}

void QTlenManager::menuActionHistory(QTreeWidgetItem *item)
{
	//history->showChatsWith(roster->getJidOf(item));
}

void QTlenManager::menuActionEdit(QTreeWidgetItem *item)
{
	QString jid = roster->getJidOf(item);
        QTlenUserEdit *edit = new QTlenUserEdit(0, jid , roster->getNameOf(jid), roster->getGroupOf(jid), roster->getGroupsList());
        connect(edit,
                SIGNAL(saveItem(QString, QString, QString)),
                tlen,
                SLOT(saveRosterItem(QString, QString, QString)));
	edit->show();
}

void QTlenManager::deleteContact(QTreeWidgetItem* item)
{	
        tlen    ->deleteUser(roster->getJidOf(item));
        roster  ->deleteItem(item);
}

void QTlenManager::menuActionShowOfflines(bool yesno)
{
	roster->showOfflines(yesno);
}

void QTlenManager::menuActionAdd()
{
        QTlenUserEdit *edit = new QTlenUserEdit(0, "" , "", "", roster->getGroupsList());
        connect(edit,
                SIGNAL(saveItem(QString, QString, QString)),
                tlen,
                SLOT(saveRosterItem(QString, QString, QString)));
	edit->show();
}

void QTlenManager::menuActionAdd(QString jid)
{
        QTlenUserEdit *edit = new QTlenUserEdit(0, jid , "", "", roster->getGroupsList());
                connect(edit,
                SIGNAL(saveItem(QString, QString, QString)),
                tlen,
                SLOT(saveRosterItem(QString, QString, QString)));
        edit->show();
}

void QTlenManager::myInfoArrived(QTlenUserInfo info)
{
	QTlenPubdirEdit *infoWindow = new QTlenPubdirEdit(0);
	infoWindow->setInfo(info);
	infoWindow->show();
        connect(infoWindow,
                SIGNAL(saveInfo(QTlenUserInfo)),
                tlen,
                SLOT(saveMyInfo(QTlenUserInfo)));
}

void QTlenManager::openAvatarDialog()
{
     QString fileName = QFileDialog::getOpenFileName(0, tr("Choose file"),
						 QDir::homePath(),
						 tr("Images (*.png *.xpm *.jpg)"));
     if(!fileName.isNull())
     {
	QImage image;
	if(image.load(fileName))
	{
	    if((image.width() == 64) && (image.height() == 64))
		emit saveAvatar(image);
	    else
		QMessageBox::warning(mainWindow,
				     tr("Error"),
				     tr("Image don't match allowed size 64x64px"));
	}
	else
	    QMessageBox::warning(mainWindow,
				 tr("Error"),
				 tr("Wrong image format or no rights to open file"));
    }
}

void QTlenManager::avatarSavingError()
{
    QMessageBox::warning(mainWindow,
			 tr("Error"),
			 tr("Couldn't save avatar. Try again later"));
    settings->setValue("/avatar/present", false);
    mainWindow->lb_avatar->setToolTip("");
}

void QTlenManager::avatarSaved()
{
    settings->setValue("/avatar/present", true);
    mainWindow->lb_avatar->setPixmap(QPixmap(QString(QDir::homePath() + "/.qtlen4/avatar.png")), 32, 32);
    mainWindow->lb_avatar->setToolTip("<img src=\"" + QDir::homePath() + "/.qtlen4/avatar.png\" />");
}
