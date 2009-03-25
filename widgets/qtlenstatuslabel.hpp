#ifndef QTLENSTATUSLABEL_HPP
#define QTLENSTATUSLABEL_HPP
#include <QtGui>
class QTlenStatusLabel : public QLabel
{
    Q_OBJECT
    public:
	QTlenStatusLabel(QWidget * parent = 0);
	~QTlenStatusLabel(){}
    protected:
	void mouseDoubleClickEvent (QMouseEvent*);
    signals:
	void editRequested(QRect);
};
#endif // QTLENSTATUSLABEL_HPP
