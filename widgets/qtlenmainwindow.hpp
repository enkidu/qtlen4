#ifndef QTLEN_MAIN_WINDOW_HPP
#define QTLEN_MAIN_WINDOW_HPP

//QT includes
#include <QtGui>

//QTlen includes
#include "qtlenrosterbox.hpp"
#include "qtlenstatuslabel.hpp"
#include "qtlentextedit.hpp"
#include "qtlenavatarlabel.hpp"

class QTlenMainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        QTlenMainWindow(QWidget * parent = 0, Qt::WFlags f = 0 );
        ~QTlenMainWindow(){}
        QAction *actionSettings;
        QAction *actionMyInfo;
        QAction *actionExit;
        QAction *actionAboutQTlen;
        QAction *actionAboutQt;
        QAction *actionShowOfflines;
        QAction *actionXMLConsole;
        QAction *actionChats;
        QAction *actionPrivacy;
        QAction *actionSearch;
        QWidget *centralwidget;

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

        QVBoxLayout *verticalLayout;
	QHBoxLayout *presenceLayout;
        QTlenRosterBox *lv_roster;
	QTlenStatusLabel *lb_status;
	QTlenTextEdit *te_status;
        QComboBox *cb_status;
	QTlenAvatarLabel *lb_avatar;
        QProgressBar *pbar_connecting;
        QMenuBar *menuBar;
        QMenu *menuMenu;
        QMenu *menuHelp;
    protected:
        void		closeEvent(QCloseEvent *event);
    public slots:
        void            displayAlert(QString jid);
        void		subscriptionRequestReceived(QString);
    private slots:
        void            menuActionDelete();
        void            menuActionAdd();
        void            menuActionShowOfflines(bool);
        void            menuActionInfo();
        void            menuActionChat();
        void            menuActionHistory();
        void            menuActionEdit();
        void            setStatus(int);
    signals:
        void		subscribed(QString, bool);
        void            deleteUser(QTreeWidgetItem*);
	void		editUser(QTreeWidgetItem*);
	void		history(QTreeWidgetItem*);
	void		chat(QTreeWidgetItem*);
	void		info(QTreeWidgetItem*);
        void            showOfflines(bool);
        void            addContact();
	void		setAvatar();
};

#endif //QTLEN_MAIN_WINDOW_HPP
