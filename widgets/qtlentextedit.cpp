#include "qtlentextedit.hpp"

QTlenTextEdit::QTlenTextEdit(QWidget * parent): QTextEdit(parent)
{
}

void QTlenTextEdit::keyPressEvent( QKeyEvent * e )
{
	if(( e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter ) && e->modifiers() != Qt::ShiftModifier)
		emit returnPressed();
	else if(e->key() == Qt::Key_Escape)
		emit escapePressed();
	else
	{
	    QTextEdit::keyPressEvent(e);
	    emit keyPressed();
	}
}

void QTlenTextEdit::show(QRect rect)
{
    this->setGeometry(rect);
    this->setVisible(true);
}
