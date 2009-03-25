#include "qtlenstatuslabel.hpp"

QTlenStatusLabel::QTlenStatusLabel(QWidget * parent) : QLabel(parent)
{
}

void QTlenStatusLabel::mouseDoubleClickEvent(QMouseEvent * event)
{
    this->hide();
    emit editRequested(geometry());
}

