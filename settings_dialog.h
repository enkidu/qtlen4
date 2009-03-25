#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include "defines.h"
#include <QtGui>
#include <QSettings>
#include <QCloseEvent>
#include <QtCore>
#include <QColorDialog>

class QTlenConfigDialog: public QWidget
{
	Q_OBJECT
	public:
		QTlenConfigDialog(QWidget * parent = 0);
                ~QTlenConfigDialog(){}

	private slots:
		void		setMyColor();
		void		setMyBg();
		void		setChatColor();
		void		setChatBg();
	private:
		QSettings		*settings;
                QTlenSettingsChange	changed;
		//widgets
		QHBoxLayout		*horizontalLayout_2;
		QListWidget		*listWidget;
		QStackedWidget		*stackedWidget;
		QWidget			*connection_page;
		QWidget			*roster_page;
		QWidget			*chats_page;
		QFormLayout *formLayout;
		QLabel *label;
		QLineEdit *le_login;
		QLabel *label_2;
		QLineEdit *le_password;
		QCheckBox *cb_autoConnect;
		QLabel *label_3;
		QComboBox *cb_defaultState;

		QVBoxLayout *verticalLayout;
		QCheckBox *cb_showOfflines;
		QCheckBox *cb_showExtendedInfo;
		QCheckBox *cb_showAvatars;
		QCheckBox *cb_showDescriptions;
		QCheckBox *cb_showJidInRoster;
		QGroupBox *gb_expandPolicy;
		QVBoxLayout *verticalLayout_2;
		QRadioButton *rb_expandedState;
		QRadioButton *rb_collapsedState;
		QRadioButton *rb_previousState;

		QVBoxLayout *verticalLayout_4;
		QScrollArea *scrollArea;
		QWidget *scrollAreaWidgetContents;
		QVBoxLayout *verticalLayout_3;
		QGroupBox *groupBox;
		QFormLayout *formLayout_4;
		QLabel *label_5;
		QLineEdit *le_nick;
		QLabel *label_7;
		QLabel *label_6;
		QPushButton *pb_myColor;
		QPushButton *pb_myBg;
		QGroupBox *groupBox_2;
		QFormLayout *formLayout_5;
		QLabel *label_8;
		QCheckBox *cb_useJID;
		QPushButton *pb_chatColor;
		QPushButton *pb_chatBg;
		QLabel *label_9;
		QWidget *network_page;
	protected:
		void			closeEvent(QCloseEvent *event);
	signals:
                void			configChanged(QTlenSettingsChange);
};

#endif
