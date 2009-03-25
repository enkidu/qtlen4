#include "systrayicon.h"

QTlenTrayIcon::QTlenTrayIcon(QObject * parent):QSystemTrayIcon(parent)
{
	icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/offline.png")),		QIcon::Normal, QIcon::Off);
	icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png")),		QIcon::Normal, QIcon::Off);
	icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png")),		QIcon::Normal, QIcon::Off);
	icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png")),		QIcon::Normal, QIcon::Off);
	icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png")),		QIcon::Normal, QIcon::Off);
	icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png")),		QIcon::Normal, QIcon::Off);
	icon7.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/invisible.png")),	QIcon::Normal, QIcon::Off);
	icon8.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/offline.png")),		QIcon::Normal, QIcon::Off);
	icon9.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/application-exit.png")),	QIcon::Normal, QIcon::Off);
	this -> setIcon(icon1);
	menu = new QMenu();
	menu -> setTitle("QTlen4");
	goOnline	= new QAction(icon2,	QString::fromUtf8("Dostępny"),		this);
	goChatty	= new QAction(icon3,	QString::fromUtf8("Porozmawiajmy"),	this);
	goAway		= new QAction(icon4,	QString::fromUtf8("Zaraz wracam"),	this);
	goXA		= new QAction(icon5,	QString::fromUtf8("Wracam później"),	this);
	goDND		= new QAction(icon6,	QString::fromUtf8("Zajęty"),		this);
	goInvisible	= new QAction(icon7,	QString::fromUtf8("Niewidoczny"),	this);
	goOffline	= new QAction(icon8,	QString::fromUtf8("Niedostępny"),	this);
	exitQTlen	= new QAction(icon9,	QString::fromUtf8("Zakończ"),		this);
	menu -> addAction(goOnline);
	menu -> addAction(goChatty);
	menu -> addAction(goAway);
	menu -> addAction(goXA);
	menu -> addAction(goDND);
	menu -> addAction(goInvisible);
	menu -> addAction(goOffline);
	menu -> addSeparator();
	menu -> addAction(exitQTlen);
	this -> setContextMenu(menu);
	connect(exitQTlen,	SIGNAL(triggered()),	this,	SLOT(exitApp()));
	connect(goOnline,	SIGNAL(triggered()),	this,	SLOT(setOnline()));
	connect(goChatty,	SIGNAL(triggered()),	this,	SLOT(setChatty()));
	connect(goAway,		SIGNAL(triggered()),	this,	SLOT(setAway()));
	connect(goXA,		SIGNAL(triggered()),	this,	SLOT(setXA()));
	connect(goDND,		SIGNAL(triggered()),	this,	SLOT(setDND()));
	connect(goInvisible,	SIGNAL(triggered()),	this,	SLOT(setInvisible()));
	connect(goOffline,	SIGNAL(triggered()),	this,	SLOT(setOffline()));
};
void QTlenTrayIcon::exitApp()
{
	emit appExit();
};

void QTlenTrayIcon::setOnline()
{
	emit setStatus(0);
};

void QTlenTrayIcon::setChatty()
{
	emit setStatus(1);
};

void QTlenTrayIcon::setAway()
{
	emit setStatus(2);
};

void QTlenTrayIcon::setXA()
{
	emit setStatus(3);
};

void QTlenTrayIcon::setDND()
{
	emit setStatus(4);
};

void QTlenTrayIcon::setInvisible()
{
	emit setStatus(5);
};

void QTlenTrayIcon::setOffline()
{
	emit setStatus(6);
};

void QTlenTrayIcon::setStatusIcon(int status)
{
	QIcon icon;
	switch (status)
	{
		case 0:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/online.png")), QIcon::Normal, QIcon::Off);
		break;
		case 1:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/chatty.png")), QIcon::Normal, QIcon::Off);
		break;
		case 2:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/away.png")), QIcon::Normal, QIcon::Off);
		break;
		case 3:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/xa.png")), QIcon::Normal, QIcon::Off);
		break;
		case 4:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/dnd.png")), QIcon::Normal, QIcon::Off);
		break;
		case 5:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/invisible.png")), QIcon::Normal, QIcon::Off);
		break;
		case 6:
			icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/32x32/offline.png")), QIcon::Normal, QIcon::Off);
		break;
	}
	this->setIcon(icon);
}