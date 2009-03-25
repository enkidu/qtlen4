#ifndef ROSTER_BOX_H
#define ROSTER_BOX_H

#include <QtGui>
#include <QSettings>
#include <QtCore>

#include "defines.h"

class QTlenRosterBox: public QTreeWidget
{
	Q_OBJECT
	public:
		QTlenRosterBox(QWidget * parent = 0);
                ~QTlenRosterBox(){}
	public slots:
		void			setOfflinesVisible(bool yesno);
		QTreeWidgetItem*	addRosterItem(QString, QTlenPresence, QString, QString, QPixmap, QTreeWidgetItem*);
		QTreeWidgetItem*	addRosterNode(QString);
	private:
		bool		offlinesVisible;
		QSettings	*settings;
	protected:
		void		contextMenuEvent(QContextMenuEvent *event);
};
#endif
