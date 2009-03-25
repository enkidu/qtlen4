#ifndef QTLENSEARCHRESULTBOX_HPP
#define QTLENSEARCHRESULTBOX_HPP

#include <QtGui>
#include <QtCore>

#include "defines.h"

class QTlenSearchResultBox: public QTreeWidget
{
        Q_OBJECT
        public:
		QTlenSearchResultBox(QWidget * parent = 0, QWidget * realParent = 0);
                ~QTlenSearchResultBox(){}
		QTreeWidgetItem* appendItem(const QTlenUserInfo info);
	private:
		QWidget* realParent;
        protected:
                void		contextMenuEvent(QContextMenuEvent *event);
};

#endif // QTLENSEARCHRESULTBOX_HPP
