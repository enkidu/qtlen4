#ifndef SYSTRAYICON_H
#define SYSTRAYICON_H
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class QTlenTrayIcon: public QSystemTrayIcon
{
	Q_OBJECT
	public:
		QTlenTrayIcon(QObject *parent = 0);
		~QTlenTrayIcon(){};
		void		setStatusIcon(int);
	private:
		QMenu		*menu;
		QAction		*goOnline;
		QAction		*goChatty;
		QAction		*goAway;
		QAction		*goXA;
		QAction		*goDND;
		QAction		*goInvisible;
		QAction		*goOffline;
		QAction		*exitQTlen;
		QIcon		icon1;
		QIcon		icon2;
		QIcon		icon3;
		QIcon		icon4;
		QIcon		icon5;
		QIcon		icon6;
		QIcon		icon7;
		QIcon		icon8;
		QIcon		icon9;
	private slots:
		void		exitApp();
		void		setOnline();
		void		setChatty();
		void		setAway();
		void		setXA();
		void		setDND();
		void		setInvisible();
		void		setOffline();
	signals:
		void		setStatus(int);
		void		appExit();
};
#endif
