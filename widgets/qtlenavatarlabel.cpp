#include "qtlenavatarlabel.hpp"

QTlenAvatarLabel::QTlenAvatarLabel(QWidget * parent):QLabel(parent)
{
    menu = new QMenu(this);
    actionUpload   = new QAction(tr("Set avatar"), menu);
    actionRemove   = new QAction(tr("Remove avatar"), menu);
    menu->addAction(actionUpload);
    menu->addAction(actionRemove);
}

void QTlenAvatarLabel::contextMenuEvent(QContextMenuEvent *event)
{
    menu -> exec(event->globalPos());
}

void QTlenAvatarLabel::setPixmap(const QPixmap& pixmap, int x, int y)
{
    QPixmap scaled = pixmap.scaled(x,y, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel::setPixmap(scaled);
    setFixedSize(x,y);
}
