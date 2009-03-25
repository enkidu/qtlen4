#ifndef QTLENAVATARLABEL_HPP
#define QTLENAVATARLABEL_HPP

#include <QLabel>
#include <QPixmap>
#include <QMenu>
#include <QContextMenuEvent>

class QTlenAvatarLabel : public QLabel
{
    Q_OBJECT
public:
    QTlenAvatarLabel(QWidget * parent = 0);
    void setPixmap( const QPixmap & , int, int);
    QMenu *menu;
    QAction *actionUpload;
    QAction *actionRemove;
protected:
    void    contextMenuEvent(QContextMenuEvent *event);
};

#endif // QTLENAVATARLABEL_HPP
