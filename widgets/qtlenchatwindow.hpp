#ifndef QTLENCHATWIDGET_HPP
#define QTLENCHATWIDGET_HPP
#include <QWidget>
#include <QDateTime>
#include <QtCore>
#include <QCloseEvent>
#include <QSettings>
#include <QtGui>
#include <QTextDocument>
#include <QtWebKit/QWebView>
#include "qtlentextedit.hpp"

#include "defines.h"

class QTlenChatWidget: public QWidget
{
	Q_OBJECT
	public:
                QTlenChatWidget(QWidget * parent = 0, Qt::WFlags f = 0 );
                ~QTlenChatWidget(){}
		void setContactInfo(QString, QString);
		void setMyInfo(QString);
                //QAction *actionTyping;
                //QAction *actionInfo;
                //QAction *actionImage;
                //QWidget *centralwidget;
                QVBoxLayout *verticalLayout;
                QWebView *te_chatWindow;
                QTlenTextEdit *te_chatInput;
                //QToolBar    *toolBar;
		QTimer	    *timer;
	private:
		QString 		jid;	//jid rozmówcy
		QString			nick;	//nick rozmówcy
		QString			myNick;
		QSettings		*settings;
		QString			myColor, myBg, chatColor, chatBg;
		QString			formatMessage(QDateTime, QString, QString, QString);
		QTextDocument		*document;
		QTextCursor		cursor;
                QString                 header;
                QString                 footer;
	public slots:
		void			showMessage(const QString,const QDateTime);	//body i stamp
		void			sendMessage();
		void			setTyping(bool);
		void			showPreviousMessages(const QList<QTlenMessageStruct>);
		void			showNotify(const QString);
                        void                    showImage(QPixmap image);
	private slots:
		void			keyPressHandler();
		void			typingStopped();
                void                    requestInfo();
                void                    openImage();
	signals:
		void			message(QString, QString);
		void			typing(QString, bool);
		void			widgetClosed(QString);
                void                    infoRequest(QString);
                void                    sendImage(QString, QString);
	protected:
		void			closeEvent(QCloseEvent *event);
};

#endif
