#include <QMainWindow>
#include <QDateTime>
#include <QtCore>
#include <QCloseEvent>
#include <QSettings>
#include <QtGui>
#include <QTextDocument>
#include "qtlentextedit.hpp"
#include "defines.h"

class QTlenChatWindow: public QMainWindow
{
	Q_OBJECT
	public:
		QTlenChatWindow(QWidget * parent = 0, Qt::WFlags f = 0 );
		~QTlenChatWindow(){qDebug("chat window closed");}
		void setContactInfo(QString, QString);
		void setMyInfo(QString);
                QAction *actionTyping;
		QAction *actionInfo;
                QWidget *centralwidget;
                QVBoxLayout *verticalLayout;
		QTextBrowser *te_chatWindow;
                QTlenTextEdit *te_chatInput;
		QToolBar    *toolBar;
		QTimer	    *timer;
	private:
		QString 		jid;	//jid rozmówcy
		QString			nick;	//nick rozmówcy
		QString			myNick;
		QSettings		*settings;
		QString			myColor, myBg, chatColor, chatBg;
		QString			formatMessage(QDateTime, QString, QString, QString);
		QScrollBar		*vertScroll;
		QTextDocument		*document;
		QTextCursor		cursor;
	public slots:
		void			showMessage(const QString,const QDateTime);	//body i stamp
		void			sendMessage();
		void			setTyping(bool);
		void			showPreviousMessages(const QList<QTlenMessageStruct>);
		void			showNotify(const QString);
	private slots:
		void			keyPressHandler();
		void			typingStopped();
	signals:
		void			message(QString, QString);
		void			typing(QString, bool);
		void			widgetClosed(QString);
	protected:
		void			closeEvent(QCloseEvent *event);
};

