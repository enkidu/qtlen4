#ifndef SEARCH_DIALOG_H
#define SEARCH_DIALOG_H
#include <QtGui>
#include "defines.h"
#include "qtlensearchresultbox.hpp"

class QTlenSearchDialog: public QWidget
{
	Q_OBJECT
        public:
		QTlenSearchDialog(QWidget * parent = 0, Qt::WFlags f = 0 );
		~QTlenSearchDialog();
		QHBoxLayout *hLayout;
		QSplitter *splitter;
		QWidget *frame;
		QFormLayout *fLayout;
                QLabel *label;
                QLineEdit *le_first;
                QLabel *label_3;
                QLineEdit *le_last;
                QLineEdit *le_mail;
                QLabel *label_4;
                QLineEdit *le_nick;
                QLabel *label_2;
                QLineEdit *le_school;
                QLabel *label_5;
                QLineEdit *le_city;
                QLabel *label_6;
                QComboBox *comboBox;
                QLabel *label_7;
                QLabel *label_8;
                QSpinBox *sb_ageMin;
                QLabel *label_9;
                QSpinBox *sb_ageMax;
                QPushButton *pb_search;
                QPushButton *pb_clear;
                QCheckBox *cb_onlines;
		QWidget *frame_2;
		QVBoxLayout *vLayout;
		QHBoxLayout *buttonLayout;
                QTlenSearchResultBox *tw_output;
		struct SearchResult
		{
		    QString jid;
		    QTreeWidgetItem* item;
		};
	private:
		bool		searchingAllowed;
		int		itemCount;
		QList<SearchResult> searchResults;
		QString		findJidOf(const QTreeWidgetItem*);
 	public slots:
 		void		beginInfo(bool);
		void		appendItem(const QTlenUserInfo);
		void		sendRequest();
		void		clearForm();
                void            menuActionChat();
                void            menuActionAdd();
 	signals:
 		void		search(QTlenUserInfo);
                void            addContact(QString);
                void            openChat(QString);
};

#endif // SEARCH_DIALOG_H
