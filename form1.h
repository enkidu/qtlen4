#include "qtlen.h"
#include "widgets/systrayicon.h"
#include "widgets/qtlenmainwindow.hpp"
#include "chat_manager.h"
#include "debug.h"
#include "edit_dialog.h"
#include "settings_dialog.h"
#include "info_edit.h"
#include "widgets/qtlensearchdialog.hpp"
#include "historymanager.hpp"
#include "avatarsmanager.hpp"
#include "qtlenpublicchatswindow.hpp"
#include <QMessageBox>
#include <QTextCodec>
#include <QtGui>
#include <QAbstractSocket>
#include <QCloseEvent>


class QTlenManager: public QObject
{
	Q_OBJECT
	public:
                QTlenManager();
                ~QTlenManager() {}
                QTlenMainWindow         *mainWindow;
		QTlen			*tlen;
		QTlenTrayIcon		*sysIcon;
		QSettings		*settings;
		QTlenRosterManager	*roster;
		QTlenDebugWindow	*debug;
		QTlenChatManager	*chats;
		QTlenHistoryManager	*history;
        public slots:
		void		showMessage(QString, QString, QDateTime);
		void		respondForAuthenticated();
		void		respondForDisconnected();
		void		respondForConnecting();
		void		respondForServerConnect();
		void		respondForConnected();
		void		respondForRosterEnd();
		void		setStatus(int);
		void		setStatus();
		void		toggleVisible(QSystemTrayIcon::ActivationReason reason);
		void		appExit();
		void		openChat(QTreeWidgetItem*, int);
		void		menuActionInfo(QTreeWidgetItem*);
		void		menuActionChat(QTreeWidgetItem*);
		void		menuActionHistory(QTreeWidgetItem*);
		void		menuActionEdit(QTreeWidgetItem*);
                void		deleteContact(QTreeWidgetItem*);
		void		openConfigDialog();
		void		menuActionShowOfflines(bool);
		void		menuActionAdd();
                void		menuActionAdd(QString);
		void		myInfoArrived(QTlenUserInfo);
		void		openSearchDialog();
                void            configChanged(QTlenSettingsChange);
		void		openAvatarDialog();
		void		avatarSavingError();
		void		avatarSaved();
	signals:
		void		sendMessage(QString, QString);
                void		setStatus(int, QString);
		void		saveAvatar(QImage);
		
	//private slots:
};

