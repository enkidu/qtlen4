#ifndef CHAT_EDIT_H
#define CHAT_EDIT_H

#include <QtCore>
#include <QTextEdit>
#include <QKeyEvent>
class QTlenTextEdit: public QTextEdit
{
	Q_OBJECT
	public:
		QTlenTextEdit(QWidget * parent = 0);
		~QTlenTextEdit(){}
	public slots:
		void show(QRect);
	protected:
		void			keyPressEvent( QKeyEvent * e );
	signals:
		void			returnPressed();
		void			keyPressed();
		void			escapePressed();
};

#endif // CHAT_EDIT_H
