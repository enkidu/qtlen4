#ifndef QTLENROSTERITEM_HPP
#define QTLENROSTERITEM_HPP
#include "defines.h"
#include <QtGui>
class QTlenRosterItem
{
public:
    QTlenRosterItem(QString name = "", QTlenPresence type = Offline, QString desc="", QString jid="", QPixmap pxAvatar=QPixmap());
    int paint(QPainter *painter, const QRect &rect,
                const QPalette &palette, bool checked) const;
    QSize sizeHint(const QStyleOptionViewItem &option, QWidget*) const;
    int height;
    void setHeight(int);
private:
    QString name;
    QPixmap presence;
    QString desc;
    QString jid;
    QPixmap avatar;
};
Q_DECLARE_METATYPE(QTlenRosterItem)
#endif // QTLENROSTERITEM_HPP
